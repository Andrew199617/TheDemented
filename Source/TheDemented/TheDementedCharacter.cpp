// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TheDemented.h"
#include "TheDementedCharacter.h"
#include "TheDementedProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "Components/SpotLightComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATheDementedCharacter

ATheDementedCharacter::ATheDementedCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Phone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FP_Phone"));
	FP_Phone->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Phone->bCastDynamicShadow = false;
	FP_Phone->CastShadow = false;
	//FP_Phone->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Phone->SetupAttachment(RootComponent);

	FP_Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightLocation"));
	FP_Light->SetupAttachment(RootComponent);

	// Default offset from the character location for projectiles to spawn
	PhoneOffset = FVector(0.0f, 0.0f, 0.0f);

}

void ATheDementedCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Phone->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	FP_Light->SetIntensity(0.0f);
	phoneIsOn = false;
	isCrouching = false;
	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	Mesh1P->SetHiddenInGame(false, true);
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheDementedCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATheDementedCharacter::StartCrouch);

	PlayerInputComponent->BindAction("TurnOnPhone", IE_Pressed, this, &ATheDementedCharacter::TurnOnPhone);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATheDementedCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATheDementedCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATheDementedCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATheDementedCharacter::LookUpAtRate);
}

void ATheDementedCharacter::StartCrouch()
{
	if (isCrouching)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
	isCrouching = !isCrouching;
}

void ATheDementedCharacter::EndCrouch()
{

}

void ATheDementedCharacter::TurnOnPhone()
{
	if (FP_Light)
	{
		if (!phoneIsOn)
		{
			FP_Light->SetIntensity(10000.f);
		}
		else
		{
			FP_Light->SetIntensity(0.0f);
		}
		phoneIsOn = !phoneIsOn;
	}

	// try and play the sound if specified
	if (PhoneSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PhoneSound, GetActorLocation());
	}
}

void ATheDementedCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATheDementedCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATheDementedCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATheDementedCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

