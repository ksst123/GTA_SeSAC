// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YohanCharacter.generated.h"

UCLASS()
class GTA_SESAC_API AYohanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYohanCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputMappingContext* DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputRun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputAim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputHit;*/

private:
	int currentHP;
	int maxHP = 100;


	void OnAxisMove(const struct FInputActionValue& value);
	void OnAxisLook(const struct FInputActionValue& value);

	void OnActionJump();
	void OnActionRun();
	void OnActionAim();
	void OnActionHit();
};
