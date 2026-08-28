// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CatchGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGameOver);

class ACatchGameState;
class USoundBase;

/**
 * 
 */
UCLASS()
class CATCH_API ACatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACatchGameMode();

	// Called actively by the Collectables Manager whenever the player gets a collectable item.
	void OnItemCollected();

	// Called actively by the Collectables Manager whenever a collectable item is registered.
	void OnItemRegistered(int32 Count);

	// Event triggered when the level ends
	FOnGameOver OnGameOver;
	
protected:
	virtual void StartPlay() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// The initial stage time duration in seconds (exposed to Blueprints to tweak per level)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Catch|Rules", meta = (ClampMin = "5.0"))
	float LevelDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Catch|Audio")
	TObjectPtr<USoundBase> BGMToPlay;

	// Target amount of items needed to complete this level
	int32 TargetItemsForLevelCompletion;

private:
	//Decrements the stage timer by 1 second. Called by TimerManager.
	void UpdateStageTimer();

	// Triggers Game Over sequence.
	void HandleGameOver();

	// Triggers Next Stage sequence.
	void HandleVictory();

	// Subscribe to important events
	void SubscribeToEvents();

	// Unsubscribe to important events
	void UnsubscribeToEvents();

	// Ends the level
	void EndGame();

	// Cached pointer to avoid expensive casting during runtime.
	UPROPERTY()
	TObjectPtr<ACatchGameState> CatchGameState;

	// Timer handle for the 1-second interval update loop
	FTimerHandle TimerHandle_StageCountdown;

	FDelegateHandle OnItemCollectedHandle;
	
	FDelegateHandle OnItemRegisteredHandle;
};
