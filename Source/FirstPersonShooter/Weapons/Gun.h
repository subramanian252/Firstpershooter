// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABallProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation1p;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation3p;
	
	class UAnimInstance* AnimInstance1p;
	class UAnimInstance* AnimInstance3p;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable,Category=Input)
	void OnFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
