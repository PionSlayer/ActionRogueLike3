// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SCharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE3_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	UCameraComponent* CameraComp;
	USpringArmComponent* SpringArmComp;
	USInteractionComponent* interactionComp;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim; 
	FTimerHandle TimerHandle_PrimaryAttack;
	
	virtual void BeginPlay() override;


public:	
	void MoveForward(float Value);
    void MoveSideWays(float Value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryInteract();
	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
