// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchGameMode.h"
#include "../Game State/CatchGameState.h"

ACatchGameMode::ACatchGameMode()
	: LevelDuration(60.0f)
	, TargetItemsForLevelCompletion(10)
	, CatchGameState(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GameStateClass = ACatchGameState::StaticClass();
}

void ACatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	CatchGameState = GetGameState<ACatchGameState>();

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

void ACatchGameMode::HandleGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
}

void ACatchGameMode::HandleVictory()
{
	UE_LOG(LogTemp, Warning, TEXT("Victory!"));
}
