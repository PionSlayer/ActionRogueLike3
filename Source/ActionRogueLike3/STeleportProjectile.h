// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBasicProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE3_API ASTeleportProjectile : public ASBasicProjectile
{
	GENERATED_BODY()

	bool Begin = false;
	FTimerHandle Timer;

	UPROPERTY(EditAnywhere)
	float CountDown = 0.05;




	
	void BeginPlay() override;

	virtual void OnDisipate() override;
	void OnHit(UPrimitiveComponent* hitComp, AActor* OtherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	void BeginTeleport();
	void Teleport();

};
