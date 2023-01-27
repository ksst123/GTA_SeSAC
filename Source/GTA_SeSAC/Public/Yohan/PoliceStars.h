// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PoliceStars.generated.h"

/**
 * 
 */
UCLASS()
class GTA_SESAC_API UPoliceStars : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Police Stars", meta = (BindWidget))
	TArray<class UImage*> PoliceStarImages;



	void OnVisibleStar();
	void OffVisibleStar();
};
