// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONSHOOTER_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()


public:
	TArray<AActor*> getpatrolpoints();

private:
	UPROPERTY(EditInstanceOnly, Category = patrol)
	TArray<AActor*>patrolpoints;
};
