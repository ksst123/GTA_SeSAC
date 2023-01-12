// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���ʹ� ������ �ش��ϴ� �ּ� �б�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemySkeletal(TEXT("/Script/Engine.SkeletalMesh'/Game/Yohan/Animation/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));

	// ���ʹ� ���� �ּ� �б⸦ �����ߴٸ�
	if (EnemySkeletal.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(EnemySkeletal.Object);
	}

	// ���ʹ� Transform ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

