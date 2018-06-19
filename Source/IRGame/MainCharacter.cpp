// Copyright 2018 Infinite Replay. All Rights Reserved.

#include "MainCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/InputSettings.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//set turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	//Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//setup gameplay key bindings
	check(PlayerInputComponent);

	//bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	//bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveStrafe", this, &AMainCharacter::MoveStrafe);

	//binds the mouse look events
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//binds controller look events
	//PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);
}

void AMainCharacter::MoveForward(float Value)
{
	//add movement in forward/back direction
	if (Value != 0.0f)
		AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::MoveStrafe(float Value)
{
	//add movement in left/right direction
	if (Value != 0.0f)
		AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::TurnAtRate(float Rate)
{
	//calculate delta turn rate for mouse/controller movement
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	//calculate delta look rate for move/controller movement
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}