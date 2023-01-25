// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/InteractableCar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Yohan/YohanCharacter.h"
//#include "Kismet/GameplayStatics.h"
//#include "../GTA_SeSACGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


AInteractableCar::AInteractableCar()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArm);

	GetIntoCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Get Into Collision"));
	GetIntoCollision->SetupAttachment(RootComponent);
	GetIntoCollision->SetGenerateOverlapEvents(true);
}

void AInteractableCar::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem != nullptr)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DrivingInputMapping, 0);
		}
	}

	GetIntoCollision->OnComponentBeginOverlap.AddDynamic(this, &AInteractableCar::OnCarBeginOverlap);
	GetIntoCollision->OnComponentEndOverlap.AddDynamic(this, &AInteractableCar::OnCarEndOverlap);
}

void AInteractableCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AInteractableCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComp->BindAction(InputThrottle, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionThrottle);
	
	EnhancedInputComp->BindAction(InputBreak, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionBreak);

	EnhancedInputComp->BindAction(InputSteering, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionSteering);

	EnhancedInputComp->BindAction(InputInteract, ETriggerEvent::Triggered, this, &AInteractableCar::OnActionInteract);
}

void AInteractableCar::OnActionThrottle(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value.Get<float>());
	UE_LOG(LogTemp, Warning, TEXT("Throttle"));
}

void AInteractableCar::OnActionBreak(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(Value.Get<float>());
	UE_LOG(LogTemp, Warning, TEXT("Break"));
}

void AInteractableCar::OnActionSteering(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value.Get<float>());
	UE_LOG(LogTemp, Warning, TEXT("Steering"));
}

void AInteractableCar::OnActionInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Interactable"));
	if (player != nullptr)
	{
		player->OnActionEnteringCar();
		player->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

		auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		controller->UnPossess();
		controller->Possess(this);
	}
}


void AInteractableCar::OnCarBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap"));
	player = Cast<AYohanCharacter>(OtherActor);	
}

void AInteractableCar::OnCarEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End Overlap"));
	player = Cast<AYohanCharacter>(OtherActor);

	if (player != nullptr)
	{
		player->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	}

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	controller->UnPossess();
	controller->Possess(player);
}
