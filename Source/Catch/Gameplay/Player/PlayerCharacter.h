// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;


UCLASS(Abstract, Blueprintable)
class CATCH_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	// movement
	void Move(const FInputActionValue& Value);
	
	// camera rotation
	void Look(const FInputActionValue& Value);

private:
	// camera setup: arm + camera object
	// camera support arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	// player third-person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;


	// input action for moving
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	// look with camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	// jump action
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	// input mapping context
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext;
};
