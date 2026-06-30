// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchGameState.h"

ACatchGameState::ACatchGameState()
	: TimeRemaining(0.0f)
	, ItemsCollected(0)
	, TotalItems(0)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ACatchGameState::SetTimeRemaining(float NewTime)
{
	TimeRemaining = NewTime;

	UE_LOG(LogTemp, Warning, TEXT("Time Remaining: %f"), TimeRemaining);
}

void ACatchGameState::IncrementItemsCollected()
{
	ItemsCollected++;

	UE_LOG(LogTemp, Warning, TEXT("Items Collected: %d / %d"), ItemsCollected, TotalItems);
}

void ACatchGameState::SetTotalItems(int32 Count)
{
	TotalItems = Count;

	UE_LOG(LogTemp, Warning, TEXT("Total Items: %d"), TotalItems);
}
