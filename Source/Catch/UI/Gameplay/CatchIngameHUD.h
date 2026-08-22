// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CatchIngameHUD.generated.h"

class UCatchHUDWidget;

/**
 * 
 */
UCLASS()
class CATCH_API ACatchIngameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACatchIngameHUD();

	UPROPERTY(EditDefaultsOnly, Category = "Catch | UI")
	TSubclassOf<UCatchHUDWidget> HUDWidgetClass;

	FORCEINLINE UCatchHUDWidget* GetHUDWidget() const { return HUDWidget; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UCatchHUDWidget> HUDWidget;
};
