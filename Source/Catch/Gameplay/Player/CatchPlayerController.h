// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CatchPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class CATCH_API ACatchPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACatchPlayerController();

protected:
	void BeginPlay() override;
	void SetupInputComponent() override;
};
