// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "DrawDebugHelpers.h"
#include"Engine.h"
#include"EngineUtils.h"
#include"ActorPool.h"
#include"NavMesh/NavMeshBoundsVolume.h"
#include"Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Navigationsystemboundingoffset= FVector(2000,0,0);
	MinExtent=FVector (0,-2000,0);
	MaxExtent=FVector (4000,2000,0);

}

template<class T>
void  ATile::RandomlySpawnActors(TSubclassOf<T> ToSpawn, int MinSpawn , int MaxSpawn , float Radius , float MinScale , float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		if (found)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}



}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	RandomlySpawnActors(ToSpawn, MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	RandomlySpawnActors(ToSpawn, MinSpawn, MaxSpawn, Radius, 1, 1);
}




void ATile::setpool(UActorPool* InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsvolume = Pool->Checkout();
	if (NavMeshBoundsvolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("(%s)Not enough actors in pool."),*GetName());
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("(%s)checked out:(%s)."), *GetName(),*NavMeshBoundsvolume->GetName());
	NavMeshBoundsvolume->SetActorLocation(GetActorLocation()+ Navigationsystemboundingoffset);
	GetWorld();
	FNavigationSystem::Build(*GetWorld());
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Pool != nullptr && NavMeshBoundsvolume != nullptr)
	{
		Pool->Return(NavMeshBoundsvolume);
	}
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius) {
	FBox Bounds(MinExtent, MaxExtent);
	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint, Radius)) {
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (Spawned)
	{
		Spawned->SetActorRelativeLocation(SpawnPosition.Location);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
		Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
	}
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	FRotator Rotation = FRotator(0, SpawnPosition.Rotation, 0);
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, SpawnPosition.Location,Rotation);
	if (Spawned)
	{
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SpawnDefaultController();
		Spawned->Tags.Add(FName("enemy"));
	}
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	/*auto ActorIterator = TActorIterator<AActor>(GetWorld());
	while (ActorIterator)
	{
		AActor* FoundActor = *ActorIterator;
		UE_LOG(LogTemp, Warning, TEXT("found:%s"), *FoundActor->GetName());
		++ActorIterator;
	}*/
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(Radius)
	);
	return !HasHit;
}