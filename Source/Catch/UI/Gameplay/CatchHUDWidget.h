// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CatchHUDWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class CATCH_API UCatchHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Catch|HUD")
	void UpdateTimeRemaining(float NewTime);

	UFUNCTION(BlueprintCallable, Category = "Catch|HUD")
	void UpdateItemCounters(int32 Collected, int32 Remaining);

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	TObjectPtr<UTextBlock> CollectedItemsTextValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	TObjectPtr<UTextBlock> RemainingItemsTextValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	TObjectPtr<UTextBlock> TimeRemainingTextValue;
};
