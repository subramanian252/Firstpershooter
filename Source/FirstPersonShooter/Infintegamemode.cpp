// Fill out your copyright notice in the Description page of Project Settings.


#include "Infintegamemode.h"
#include"NavMesh/NavMeshBoundsVolume.h"
#include"EngineUtils.h"
#include"ActorPool.h"

AInfintegamemode::AInfintegamemode()
{
	NavMeshBoundsvolume = CreateDefaultSubobject<UActorPool>(FName("navmeshboundsvolume"));
}

void  AInfintegamemode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}


void  AInfintegamemode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found Actor: %s"), *VolumeToAdd->GetName());
	NavMeshBoundsvolume->Add(VolumeToAdd);
}