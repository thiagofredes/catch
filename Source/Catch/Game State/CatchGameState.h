// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CatchGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeUpdated, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCollectableItemsUpdated, int32, int32);


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

	// Sets the total number of items in the world
	void SetTotalItems(int32 Count);

	// Technical Blueprint Getters for UI binding without performance overhead
	UFUNCTION(BlueprintPure, Category = "Catch|State")
	FORCEINLINE float GetTimeRemaining() const { return TimeRemaining; }

	UFUNCTION(BlueprintPure, Category = "Catc|State")
	FORCEINLINE int32 GetItemsCollected() const { return ItemsCollected; }

	FORCEINLINE int32 GetTotalItems() const { return TotalItems; }

	FOnTimeUpdated OnTimeUpdated;
	FOnCollectableItemsUpdated OnCollectableItemsUpdated;

private:
	// Current time left in seconds for the stage
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Catch|State", meta = (AllowPrivateAccess = "true"))
	float TimeRemaining;

	// How many target items the player has collected so far
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Catch|State", meta = (AllowPrivateAccess = "true"))
	int32 ItemsCollected;

	// How many target items are in this world
	int32 TotalItems;
};
