// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchIngameHUD.h"
#include "CatchHUDWidget.h"
#include "Blueprint/UserWidget.h"

ACatchIngameHUD::ACatchIngameHUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACatchIngameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UCatchHUDWidget>(GetWorld(), HUDWidgetClass);

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
