// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE3_API ASItemChest : public AActor, public ISGamePlayInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float pitch;
	void Interact_Implementation(APawn* InstigationPawn) override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	ASItemChest();
};
