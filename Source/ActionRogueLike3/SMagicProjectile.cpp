// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"


void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}
