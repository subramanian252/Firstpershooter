// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "choosenextwaypoint.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API Uchoosenextwaypoint : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, category = "defaults")
	struct FBlackboardKeySelector indexkey;

	UPROPERTY(EditAnywhere, category = "defaults")
	struct FBlackboardKeySelector waypointkey;
};
