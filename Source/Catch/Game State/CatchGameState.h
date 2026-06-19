// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CatchGameState.generated.h"

/**
 *
 */
UCLASS()
class CATCH_API ACatchGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACatchGameState();

	// Updates the current countdown timer
	void SetTimeRemaining(float NewTime);

	// Increments the count of items collected by the player
	void IncrementItemsCollected();

	// Technical Blueprint Getters for UI binding without performance overhead
	UFUNCTION(BlueprintPure, Category = "Catch|State")
	FORCEINLINE float GetTimeRemaining() const { return TimeRemaining; }

	UFUNCTION(BlueprintPure, Category = "Catc|State")
	FORCEINLINE int32 GetItemsCollected() const { return ItemsCollected; }

private:
	// Current time left in seconds for the stage
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Catch|State", meta = (AllowPrivateAccess = "true"))
	float TimeRemaining;

	// How many target items the player has collected so far
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Catch|State", meta = (AllowPrivateAccess = "true"))
	int32 ItemsCollected;
};
