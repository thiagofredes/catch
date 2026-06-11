// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "CatchPlayerController.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Optimization: tick is disabled to save CPU processing if there is no recurreing frame logic
	PrimaryActorTick.bCanEverTick = false;

	// rotation control: player's body does not rotate with camera's control
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// camera arm configuration
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// camera configuration
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; //camera's rotation is dependant on the arm

	GetCharacterMovement()->bOrientRotationToMovement = true; // character turns to the movement's direction
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // body's rotation speed
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.5f; // partial air control
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// secure casting to modern enhanced input component
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// jump action link
		if (JumpAction) {
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}

		// movement action link
		if (MoveAction) {
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		}


		// looking action link
		if (LookAction) {
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// get the player controller assigned to this character
	ACatchPlayerController* PlayerController = Cast<ACatchPlayerController>(GetController());

	// get the enhanced input subsystem from the local player
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem && InputMappingContext)
		{
			// adds to the enhanced input player subsystem the mapping context for this character
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value) {
	// gets input 2d vector (wasd or left analog)
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// finds current camera direction to allign movmeent direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// gets forward direction (x axis) based on camera's yaw
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// gets right direction (y axis) based on camera's yaw
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// applies native character movement component's movement forces
		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value) {
	// gets input 2d vector (mouse or right analog)
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// add yaw and pitch axis rotations from playercontroller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::OnJumped_Implementation() {
	Super::OnJumped_Implementation();

	OnPlayerJumped.Broadcast();
}

void APlayerCharacter::Landed(const FHitResult& Hit) {
	Super::Landed(Hit);

	OnPlayerLanded.Broadcast();
}

void APlayerCharacter::Falling()
{
	Super::Falling();

	OnPlayerFalling.Broadcast();
}