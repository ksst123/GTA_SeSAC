// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/YohanCharacter.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
// #include "EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Yohan/EnemyAnimInstance.h"
#include "Yohan/InteractableCar.h"


// Sets default values
AYohanCharacter::AYohanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempSkeletal(TEXT("/Script/Engine.SkeletalMesh'/Game/Yohan/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));

	if (TempSkeletal.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempSkeletal.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spinrg Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = SpringArmLength;
	// Rotate the arm based on the controller
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocationAndRotation(FVector(-150.f, 0.f, 150.f), FRotator::ZeroRotator);
	// Camera does not rotate relative to arm
	CameraComponent->bUsePawnControlRotation = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	// Character moves in the direction of input
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Character movement settings
	GetCharacterMovement()->JumpZVelocity = JumpValue;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = MinWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = WalkDecelerationValue;
}

// Called when the game starts or when spawned
void AYohanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the player controller
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr)
	{
		// Get the local player subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem != nullptr)
		{
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultInputMapping, 0);
		}
	}

	// 애니메이션 블루프린트
	BPAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AYohanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYohanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Get the EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind Input Actions
	EnhancedInputComp->BindAction(InputMoveVertical, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionMoveVertical);
	EnhancedInputComp->BindAction(InputMoveHorizontal, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionMoveHorizontal);

	EnhancedInputComp->BindAction(InputLookUp, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionLookUp);
	EnhancedInputComp->BindAction(InputTurnRight, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionTurnRight);

	EnhancedInputComp->BindAction(InputJump, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionJump);

	EnhancedInputComp->BindAction(InputRun, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionRunPressed);
	EnhancedInputComp->BindAction(InputRun, ETriggerEvent::Completed, this, &AYohanCharacter::OnActionRunReleased);

	EnhancedInputComp->BindAction(InputAim, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionAimPressed);
	EnhancedInputComp->BindAction(InputAim, ETriggerEvent::Completed, this, &AYohanCharacter::OnActionAimReleased);

	EnhancedInputComp->BindAction(InputJap, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionJap);
	EnhancedInputComp->BindAction(InputStraight, ETriggerEvent::Triggered, this, &AYohanCharacter::OnActionStraight);
}

void AYohanCharacter::OnActionMoveVertical(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float MoveValue = Value.Get<float>();
		const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

		// Move Vertical
		if (MoveValue != 0.f)
		{
			// Get Forward Vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue);
		}
	}
}

void AYohanCharacter::OnActionMoveHorizontal(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float MoveValue = Value.Get<float>();
		const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

		// Move Horizontal
		if (MoveValue != 0.f)
		{
			// Get Right Vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue);
		}
	}
}

void AYohanCharacter::OnActionLookUp(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float LookValue = Value.Get<float>();

		if (LookValue != 0.f)
		{
			AddControllerYawInput(LookValue * MouseSensitivity);
		}
	}
}

void AYohanCharacter::OnActionTurnRight(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const float LookValue = Value.Get<float>();

		if (LookValue != 0.f)
		{
			AddControllerPitchInput(LookValue * MouseSensitivity);
		}
	}
}

void AYohanCharacter::OnActionJump()
{
	Jump();
}

void AYohanCharacter::OnActionRunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AYohanCharacter::OnActionRunPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = RunMultiplier * WalkSpeed;
}

void AYohanCharacter::OnActionAimPressed()
{
	if (!bHasWeapon && BPAnim != nullptr)
	{
		BPAnim->IsFighting = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void AYohanCharacter::OnActionAimReleased()
{
	if (!bHasWeapon && BPAnim != nullptr)
	{
		BPAnim->IsFighting = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AYohanCharacter::OnActionJap()
{
	// UAnimInstance* Jap = Cast<UEnemyAnimInstance>(PunchJap);
	if ((PunchJap != nullptr) && (BPAnim->IsFighting == true))
	{
		PlayAnimMontage(PunchJap, 1.f, TEXT("Default"));
	}
}

void AYohanCharacter::OnActionStraight()
{
	if ((PunchStraight != nullptr) && (BPAnim->IsFighting == true))
	{
		PlayAnimMontage(PunchStraight, 1.f, TEXT("Default"));
	}
}

void AYohanCharacter::OnActionEnteringCar()
{
	if ((EnteringCar != nullptr))
	{
		PlayAnimMontage(EnteringCar, 2.f, TEXT("Default"));
	}
}

