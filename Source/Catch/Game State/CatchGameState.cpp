// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchGameState.h"

ACatchGameState::ACatchGameState()
	: TimeRemaining(0.0f)
	, ItemsCollected(0)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ACatchGameState::SetTimeRemaining(float NewTime)
{
	TimeRemaining = NewTime;
}

void ACatchGameState::IncrementItemsCollected()
{
	ItemsCollected++;
}