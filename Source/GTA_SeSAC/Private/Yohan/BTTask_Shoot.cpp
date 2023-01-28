// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/BTTask_Shoot.h"
#include "Yohan/BaseEnemy.h"
#include "Yohan/BaseEnemyAIController.h"
#include "Yohan/YohanCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	/*Enemy = Cast<ABaseEnemy>(OwnerComp.GetAIOwner());
	if (Enemy == nullptr)
	{
		return EBTNodeResult::Failed;
	}*/

	AYohanCharacter* character = Cast<AYohanCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	character->OnActionPistol();
	character->OnActionAimPressed();
	character->OnActionJap();
	UE_LOG(LogTemp, Warning, TEXT("Shooting"));

	return EBTNodeResult::Succeeded;
}
