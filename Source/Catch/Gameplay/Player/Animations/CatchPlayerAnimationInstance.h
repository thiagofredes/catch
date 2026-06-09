// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CatchPlayerAnimationInstance.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class CATCH_API UCatchPlayerAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UCharacterMovementComponent> PlayerCharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	float PlayerVelocity;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsPlayerJumping;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsPlayerFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool IsPlayerLanded;

private:
	void PlayerJumped();

	void PlayerLanded();

	void PlayerFalling();
};
