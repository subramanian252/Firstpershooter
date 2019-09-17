// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "FirstPersonShooterGameMode.h"
#include "Infintegamemode.generated.h"


/**
 * 
 */
UCLASS()
class FIRSTPERSONSHOOTER_API AInfintegamemode : public AFirstPersonShooterGameMode
{
	GENERATED_BODY()

public:
	AInfintegamemode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pool)
	class UActorPool* NavMeshBoundsvolume;

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

};
