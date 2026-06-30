// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchPlayerController.h"

#include "../../Game Mode/CatchGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


ACatchPlayerController::ACatchPlayerController()
{
}

void ACatchPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ACatchGameMode* GameMode = Cast<ACatchGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GameMode->OnGameOver.AddUObject(this, &ACatchPlayerController::HandleGameOver);
	}

	Character = Cast<APlayerCharacter>(GetCharacter());
}

void ACatchPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ACatchPlayerController::HandleGameOver()
{
	// Disable player input when the game is over
	DisableInput(this);

	if (Character) {
		Character->StopMovement();
		Character->StopAllAnimations();
	}

	SetIgnoreLookInput(true);
}