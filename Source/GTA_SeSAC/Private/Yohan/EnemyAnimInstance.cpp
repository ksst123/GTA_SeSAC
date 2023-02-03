// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/EnemyAnimInstance.h"
#include "Yohan/YohanCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	owner = Cast<AYohanCharacter>(TryGetPawnOwner());

	if (owner != nullptr)
	{
		FVector velocity = owner->GetVelocity();
		Speed = FVector::DotProduct(owner->GetActorForwardVector(), velocity);

		bIsJumping = owner->GetCharacterMovement()->IsFalling();
	}
}

void UEnemyAnimInstance::AnimNotify_JapEnd()
{
}

void UEnemyAnimInstance::AnimNotify_StraightEnd()
{
}

void UEnemyAnimInstance::AnimNotify_DamagedJapEnd()
{
	owner->CurrentHP -= owner->FistDamage;
}

void UEnemyAnimInstance::AnimNotify_DamagedStraightEnd()
{
	owner->CurrentHP -= owner->FistDamage;
}

void UEnemyAnimInstance::AnimNotify_DamagedFistDie()
{
}
