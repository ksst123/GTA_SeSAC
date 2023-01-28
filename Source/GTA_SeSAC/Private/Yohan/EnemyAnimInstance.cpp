// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/EnemyAnimInstance.h"
#include "Yohan/YohanCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AYohanCharacter* owner = Cast<AYohanCharacter>(TryGetPawnOwner());

	if (owner != nullptr)
	{
		FVector velocity = owner->GetVelocity();
		Speed = FVector::DotProduct(owner->GetActorForwardVector(), velocity);

		bIsJumping = owner->GetCharacterMovement()->IsFalling();
	}
}