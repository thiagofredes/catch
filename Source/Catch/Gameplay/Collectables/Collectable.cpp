// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"

#include "Components/SphereComponent.h"
#include "UCollectablesManagerSubsystem.h"
#include "../Player/PlayerCharacter.h"

// Sets default values
ACollectable::ACollectable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	RootComponent = SphereCollider;

	SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->SetCollisionProfileName(TEXT("Trigger"));
	SphereCollider->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);

	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	CollectableMesh->SetupAttachment(SphereCollider);
	CollectableMesh->SetGenerateOverlapEvents(false);
	CollectableMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);

	// fetch the subsystem directly from the World and actively register this collectable
	if (UWorld* World = GetWorld()) {
		if (UCollectablesManagerSubsystem* Manager = World->GetSubsystem<UCollectablesManagerSubsystem>())
		{
			Manager->RegisterCollectable(this);
		}
	}
}

void ACollectable::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// clean up registration on destruction, level transition, or editor exit
	if (UWorld* World = GetWorld())
	{
		if (UCollectablesManagerSubsystem* Manager = World->GetSubsystem<UCollectablesManagerSubsystem>())
		{
			Manager->UnregisterCollectable(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			if (UWorld* World = GetWorld())
			{
				if (UCollectablesManagerSubsystem* Manager = World->GetSubsystem<UCollectablesManagerSubsystem>())
				{
					Manager->OnCollectableGot(this);
				}
			}

			// effectively deletes the object from the simulation safely
			Destroy();
		}
	}
}
