// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchPlayerAnimationInstance.h"

#include "../PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCatchPlayerAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (PlayerPawn) {
		PlayerCharacter = PlayerPawn;
		PlayerCharacter->OnPlayerJumped.AddUObject(this, &UCatchPlayerAnimationInstance::PlayerJumped);
		PlayerCharacter->OnPlayerLanded.AddUObject(this, &UCatchPlayerAnimationInstance::PlayerLanded);
		PlayerCharacter->OnPlayerFalling.AddUObject(this, &UCatchPlayerAnimationInstance::PlayerFalling);

		PlayerCharacterMovementComponent = PlayerCharacter->GetCharacterMovement();
	}

	IsPlayerJumping = false;
	IsPlayerLanded = true;
	IsPlayerFalling = false;
}

void UCatchPlayerAnimationInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!PlayerCharacter || !PlayerCharacterMovementComponent) return;

	PlayerVelocity = PlayerCharacterMovementComponent->Velocity.Size2D();
}

void UCatchPlayerAnimationInstance::PlayerJumped() {
	IsPlayerLanded = false;
	IsPlayerJumping = true;
}

void UCatchPlayerAnimationInstance::PlayerLanded() {
	IsPlayerFalling = false;
	IsPlayerJumping = false;
	IsPlayerLanded = true;
}

void UCatchPlayerAnimationInstance::PlayerFalling() {
	IsPlayerFalling = true;
}