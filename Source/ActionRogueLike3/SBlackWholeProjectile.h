// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBasicProjectile.h"
#include "SBlackWholeProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE3_API ASBlackWholeProjectile : public ASBasicProjectile
{
	ASBlackWholeProjectile();
public:
	UPROPERTY(EditAnywhere)
	float CountDown = 5;
	FTimerHandle Timer;

	UPROPERTY(EditAnywhere)
	float Radius = 1000;
	UPROPERTY(EditAnywhere)
	float Power = 10000;





	
	GENERATED_BODY()
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void Pull();
	virtual void OnDisipate() override;
	virtual void OnOverlap(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap) override;
	
};
