// Fill out your copyright notice in the Description page of Project Settings.


#include "choosenextwaypoint.h"
#include"Behaviortree/BlackboardComponent.h"
#include "PatrolRoute.h"
#include "AIController.h"

EBTNodeResult::Type Uchoosenextwaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto controlledpawn = OwnerComp.GetAIOwner()->GetPawn();
	auto patrolroute = controlledpawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(patrolroute)) { return EBTNodeResult::Failed; }

	auto patrolpoints = patrolroute->getpatrolpoints();
	if (patrolpoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("no patrol points"));
		return EBTNodeResult::Failed;
	}

	auto blackboardcomp = OwnerComp.GetBlackboardComponent();
	auto index = blackboardcomp->GetValueAsInt(indexkey.SelectedKeyName);
	blackboardcomp->SetValueAsObject(waypointkey.SelectedKeyName, patrolpoints[index]);

	auto nextindex = (index + 1) % patrolpoints.Num();
	blackboardcomp->SetValueAsInt(indexkey.SelectedKeyName, nextindex);

	return EBTNodeResult::Succeeded;
}