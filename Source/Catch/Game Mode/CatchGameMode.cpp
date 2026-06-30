// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchGameMode.h"
#include "../Game State/CatchGameState.h"
#include "../Gameplay/Collectables/UCollectablesManagerSubsystem.h"

ACatchGameMode::ACatchGameMode()
	: CatchGameState(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GameStateClass = ACatchGameState::StaticClass();

	SubscribeToEvents();
}

void ACatchGameMode::SubscribeToEvents()
{
	UWorld* World = GetWorld();

	if (!World) return;

	// Get the subsystem instance for this world lifecycle
	UCollectablesManagerSubsystem* CollectablesSubsystem = World->GetSubsystem<UCollectablesManagerSubsystem>();

	if (CollectablesSubsystem)
	{
		// Bind to the subsystem event
		OnItemCollectedHandle = CollectablesSubsystem->OnItemCollected.AddUObject(this, &ACatchGameMode::OnItemCollected);
		OnItemRegisteredHandle = CollectablesSubsystem->OnCollectableCountChanged.AddUObject(this, &ACatchGameMode::OnItemRegistered);
	}
}

void ACatchGameMode::UnsubscribeToEvents()
{
	UWorld* World = GetWorld();

	if (!World) return;

	// Get the subsystem instance for this world lifecycle
	UCollectablesManagerSubsystem* CollectablesSubsystem = World->GetSubsystem<UCollectablesManagerSubsystem>();

	if (CollectablesSubsystem)
	{
		// Bind to the subsystem event
		CollectablesSubsystem->OnCollectableCountChanged.Remove(OnItemRegisteredHandle);
		CollectablesSubsystem->OnItemCollected.Remove(OnItemCollectedHandle);
	}
}

void ACatchGameMode::StartPlay()
{
	CatchGameState = GetGameState<ACatchGameState>();
	
	Super::StartPlay();
}

void ACatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (CatchGameState)
	{
		CatchGameState->SetTimeRemaining(LevelDuration);

		GetWorldTimerManager().SetTimer(
			TimerHandle_StageCountdown,
			this,
			&ACatchGameMode::UpdateStageTimer,
			1.0f, // Timer tick interval (1 second)
			true   // Loop the timer
		);
	}
}

void ACatchGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UnsubscribeToEvents();
}

void ACatchGameMode::UpdateStageTimer()
{
	if (!CatchGameState) return;

	float CurrentTimeLeft = CatchGameState->GetTimeRemaining() - 1.0f;
	CatchGameState->SetTimeRemaining(CurrentTimeLeft);

	if (CurrentTimeLeft <= 0.0f)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_StageCountdown);
		HandleGameOver();
	}
}

void ACatchGameMode::OnItemCollected()
{
	if (!CatchGameState) return;

	CatchGameState->IncrementItemsCollected();

	if (CatchGameState->GetItemsCollected() >= TargetItemsForLevelCompletion)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_StageCountdown);
		HandleVictory();
	}
}

void ACatchGameMode::OnItemRegistered(int32 Count)
{
	if (!CatchGameState) return;

	TargetItemsForLevelCompletion = Count;

	CatchGameState->SetTotalItems(TargetItemsForLevelCompletion);
}

void ACatchGameMode::HandleGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
}

void ACatchGameMode::HandleVictory()
{
	UE_LOG(LogTemp, Warning, TEXT("Victory!"));
}
