// Fill out your copyright notice in the Description page of Project Settings.


#include "Seung/GTAPlayer.h"

// Sets default values
AGTAPlayer::AGTAPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGTAPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGTAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGTAPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

