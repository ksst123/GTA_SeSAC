// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/PoliceStars.h"
#include "Components/Image.h"




void UPoliceStars::NativeConstruct()
{
	Super::NativeConstruct();

	/*FString Path = FString("/Script/Engine.Texture2D'/Game/Yohan/Images/EmptyStar.EmptyStar'");
	UTexture2D* StarTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path));*/

	/*PoliceStarImage1->SetBrushFromTexture(StarTexture);
	PoliceStarImage2->SetBrushFromTexture(StarTexture);
	PoliceStarImage3->SetBrushFromTexture(StarTexture);
	PoliceStarImage4->SetBrushFromTexture(StarTexture);
	PoliceStarImage5->SetBrushFromTexture(StarTexture);*/

	// PoliceStarImage1 = NewObject<UImage>(UImage::StaticClass());


	PoliceStarImages.Add(PoliceStarImage1);
	PoliceStarImages.Add(PoliceStarImage2);
	PoliceStarImages.Add(PoliceStarImage3);
	PoliceStarImages.Add(PoliceStarImage4);
	PoliceStarImages.Add(PoliceStarImage5);

	PoliceStarImages[0]->SetVisibility(ESlateVisibility::Visible);
	PoliceStarImages[1]->SetVisibility(ESlateVisibility::Hidden);
	PoliceStarImages[2]->SetVisibility(ESlateVisibility::Hidden);
	PoliceStarImages[3]->SetVisibility(ESlateVisibility::Hidden);
	PoliceStarImages[4]->SetVisibility(ESlateVisibility::Hidden);
}

void UPoliceStars::OnVisibleStar()
{
	PoliceStarImages[1]->SetVisibility(ESlateVisibility::Visible);
}

void UPoliceStars::OffVisibleStar()
{
	
}
