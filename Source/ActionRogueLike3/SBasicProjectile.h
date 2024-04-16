// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SBasicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE3_API ASBasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBasicProjectile();

	UPROPERTY(EditAnywhere)
	float Range = 1000;
	UPROPERTY(EditAnywhere)
	bool UseRange = false;
	FVector StartLocation;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* Particles;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* Projectile;


	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnDisipate();
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* hitComp, AActor* OtherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse,const FHitResult& Hit);
	void UseOnHit();
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap);
	void UseOnOverlap();
};
