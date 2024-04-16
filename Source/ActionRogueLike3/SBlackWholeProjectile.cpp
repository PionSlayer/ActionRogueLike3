// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackWholeProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASBlackWholeProjectile::ASBlackWholeProjectile()
{
	Projectile->InitialSpeed=350;
	UseOnOverlap();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
	UseRange = true;
	Range = 1500;
}

void ASBlackWholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Timer,this,&ASBlackWholeProjectile::OnDisipate,CountDown);

}

void ASBlackWholeProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Pull();
}

void ASBlackWholeProjectile::Pull()
{
	TArray<FHitResult>Hits;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_PhysicsBody);
	GetWorld()->SweepMultiByObjectType(Hits,SphereComp->GetComponentLocation(),SphereComp->GetComponentLocation(),FQuat::Identity,Params,Shape);

	for(FHitResult Hit: Hits)
	{
		AActor* hitActor = Hit.GetActor();
		if(hitActor)
		{
			if(hitActor!=GetInstigator())
			{
				hitActor->GetComponentByClass<UPrimitiveComponent>()->AddImpulse(UKismetMathLibrary::FindLookAtRotation(hitActor->GetActorLocation(),SphereComp->GetComponentLocation()).Vector()*Power);
			}
		}
	}

	
}

void ASBlackWholeProjectile::OnDisipate()
{
	Super::OnDisipate();
	if(ParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ParticleSystem,SphereComp->GetComponentLocation(),FRotator::ZeroRotator,true);
	}
	Destroy();
}

void ASBlackWholeProjectile::OnOverlap(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap)
{
	Super::OnOverlap(hitComp, otherActor, otherComp, otherBodyIndex, fromSweep, Overlap);
	if(otherActor != GetInstigator()){otherActor->Destroy();}
}
