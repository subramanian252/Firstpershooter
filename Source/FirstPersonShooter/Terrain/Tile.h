// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

		FVector Location;
	float Rotation;
	float Scale;
};

class UActorPool;

UCLASS()
class FIRSTPERSONSHOOTER_API ATile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500 , float minsacle=1,float maxscale=1);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500);
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void setpool(UActorPool* Pool);

	UPROPERTY(EditAnywhere, Category = SpawnExtent)
	FVector Navigationsystemboundingoffset;

	UPROPERTY(EditAnywhere, Category = SpawnExtent)
	FVector MinExtent;

	UPROPERTY(EditAnywhere, Category = SpawnExtent)
	FVector MaxExtent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PositionNavMeshBoundsVolume();

	 AActor* NavMeshBoundsvolume;

private:

	template<class T>
	void RandomlySpawnActors(TSubclassOf<T> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	//TArray<FSpawnPosition> RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;



	
};