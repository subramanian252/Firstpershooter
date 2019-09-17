// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Components/HierarchicalInstancedStaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grass.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONSHOOTER_API UGrass : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrass();

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FBox SpawningExtents;
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	int SpawnCount;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SpawnGrass();
};
