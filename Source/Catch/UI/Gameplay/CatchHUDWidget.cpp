// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchHUDWidget.h"
#include "../../Game State/CatchGameState.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UCatchHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACatchGameState* GameState = Cast<ACatchGameState>(UGameplayStatics::GetGameState(GetWorld()));

	if (GameState)
	{
		GameState->OnTimeUpdated.AddUObject(this, &UCatchHUDWidget::UpdateTimeRemaining);
		GameState->OnCollectableItemsUpdated.AddUObject(this, &UCatchHUDWidget::UpdateItemCounters);
		UpdateTimeRemaining(GameState->GetTimeRemaining());
		UpdateItemCounters(GameState->GetItemsCollected(), GameState->GetTotalItems());
	}
}

void UCatchHUDWidget::UpdateTimeRemaining(float NewTime)
{
	if (!TimeRemainingTextValue) return;

	const int32 TotalSeconds = FMath::FloorToInt(NewTime);
	const int32 Minutes = TotalSeconds / 60;
	const int32 Seconds = TotalSeconds % 60;

	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	TimeRemainingTextValue->SetText(FText::FromString(TimeString));
}

void UCatchHUDWidget::UpdateItemCounters(int32 Collected, int32 Remaining)
{
	if (CollectedItemsTextValue)
	{
		CollectedItemsTextValue->SetText(FText::AsNumber(Collected));
	}
	
	if (RemainingItemsTextValue)
	{
		RemainingItemsTextValue->SetText(FText::AsNumber(Remaining));
	}
}
