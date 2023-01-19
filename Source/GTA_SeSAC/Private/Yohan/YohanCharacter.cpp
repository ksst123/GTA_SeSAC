// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/YohanCharacter.h"
//#include "EnhancedInput/Public/InputMappingContext.h"
//#include "EnhancedInput/Public/EnhancedInputSubsystems.h"


// Sets default values
AYohanCharacter::AYohanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempSkeletal(TEXT("/Script/Engine.SkeletalMesh'/Game/Yohan/Animation/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));

	if (TempSkeletal.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempSkeletal.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}
}

// Called when the game starts or when spawned
void AYohanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the player controller
	// APlayerController* PlayerController = Cast<APlayerController>(GetController());

	//if (PlayerController != nullptr)
	//{
	//	// Get the local player subsystem
	//	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	//	if (Subsystem != nullptr)
	//	{
	//		// Clear out existing mapping, and add our mapping
	//		Subsystem->ClearAllMappings();
	//		Subsystem->AddMappingContext(DefaultInputMapping, 0);
	//	}
	//}
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

}

void AYohanCharacter::OnAxisMove(const FInputActionValue& value)
{

}

void AYohanCharacter::OnAxisLook(const FInputActionValue& value)
{

}

void AYohanCharacter::OnActionJump()
{

}

void AYohanCharacter::OnActionRun()
{

}

void AYohanCharacter::OnActionAim()
{

}

void AYohanCharacter::OnActionHit()
{

}

