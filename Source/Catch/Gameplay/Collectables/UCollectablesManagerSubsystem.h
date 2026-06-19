// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UCollectablesManagerSubsystem.generated.h"

class ACollectable;

/**
 * 
 */
UCLASS()
class CATCH_API UCollectablesManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	// Automatically called when the world for this subsystem is initialized.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Automatically called when the world is being torn down (Level change/Exit)
	virtual void Deinitialize() override;

	// Registers a collectable when it spawns or activates in the level.
	void RegisterCollectable(ACollectable* Collectable);

	// Unregisters a collectable, safely updating the remaining count.
	void UnregisterCollectable(ACollectable* Collectable);

	// Event called when a collectable is successfully gotten by the player.
	void OnCollectableGot(ACollectable* Collectable);

private:

	// tracked collection using weak pointers to prevent garbage collection blocking or memory leaks
	UPROPERTY()
	TArray<TWeakObjectPtr<ACollectable>> ActiveCollectables;

	int32 TotalCollectables = 0;
	int32 RemainingCollectables = 0;
};
