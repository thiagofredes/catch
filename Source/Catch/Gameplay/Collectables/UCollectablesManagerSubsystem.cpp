// Fill out your copyright notice in the Description page of Project Settings.


#include "UCollectablesManagerSubsystem.h"

#include "Collectable.h"

void UCollectablesManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	TotalCollectables = 0;
	RemainingCollectables = 0;
}

void UCollectablesManagerSubsystem::Deinitialize()
{
	ActiveCollectables.Empty();
	Super::Deinitialize(); //called last
}

void UCollectablesManagerSubsystem::RegisterCollectable(ACollectable* Collectable)
{
	if (!Collectable) return;

	// ensures no duplicate registration
	if (!ActiveCollectables.Contains(Collectable))
	{
		ActiveCollectables.Add(Collectable);
		
		// increases both counters manually as there may be a situation when collectables are added mid-game
		TotalCollectables++;
		RemainingCollectables++;

		OnCollectableCountChanged.Broadcast(TotalCollectables);
	}
}

void UCollectablesManagerSubsystem::UnregisterCollectable(ACollectable* Collectable)
{
	if (!Collectable) return;

	// find and remove using the weak pointer matching system
	int32 RemovedCount = ActiveCollectables.RemoveAll([Collectable](const TWeakObjectPtr<ACollectable>& WeakPtr) {
		return !WeakPtr.IsValid() || WeakPtr.Get() == Collectable;
	});

	if (RemovedCount > 0)
	{
		RemainingCollectables = FMath::Max(0, RemainingCollectables - 1);
	}
}

void UCollectablesManagerSubsystem::OnCollectableGot(ACollectable* Collectable)
{
	if (!Collectable) return;

	OnItemCollected.Broadcast();
	
	//trigger gameplay effects or notify other systems here before destroying
	UnregisterCollectable(Collectable);
}
