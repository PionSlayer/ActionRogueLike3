// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGamePlayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USGamePlayInterface : public UInterface
{
	GENERATED_BODY()
};

class ACTIONROGUELIKE3_API ISGamePlayInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigationPawn);
};
