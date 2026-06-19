// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CatchGameMode.generated.h"

class ACatchGameState;

/**
 * 
 */
UCLASS()
class CATCH_API ACatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACatchGameMode();

	// Called actively by the Collectables Manager
	void OnItemCollected();
	
protected:
	virtual void BeginPlay() override;

	// The initial stage time duration in seconds (exposed to Blueprints to tweak per level)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Catch|Rules", meta = (ClampMin = "2.0", ClampMax = "5.0"))
	float LevelDuration;

	// Target amount of items needed to complete this level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Catch|Rules", meta = (ClampMin = "1"))
	int32 TargetItemsForLevelCompletion;

private:
	//Decrements the stage timer by 1 second. Called by TimerManager.
	void UpdateStageTimer();

	// Triggers Game Over sequence.
	void HandleGameOver();

	// Triggers Next Stage sequence.
	void HandleVictory();

	// Cached pointer to avoid expensive casting during runtime.
	UPROPERTY()
	TObjectPtr<ACatchGameState> CatchGameState;

	// Timer handle for the 1-second interval update loop
	FTimerHandle TimerHandle_StageCountdown;
};
