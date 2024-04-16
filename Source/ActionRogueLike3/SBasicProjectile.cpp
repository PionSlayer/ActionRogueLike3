// Fill out your copyright notice in the Description page of Project Settings.


#include "SBasicProjectile.h"

#include "Particles/ParticleSystemComponent.h"

ASBasicProjectile::ASBasicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp -> SetSimulatePhysics(false);
	SphereComp -> SetCollisionProfileName("Projectile");
	SphereComp -> SetEnableGravity(false);
	RootComponent = SphereComp;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectie");
	Projectile -> InitialSpeed = 1000;
	Projectile -> ProjectileGravityScale = 0.0f;
	Projectile -> bRotationFollowsVelocity;
	Projectile -> bInitialVelocityInLocalSpace;

	Particles = CreateDefaultSubobject<UParticleSystemComponent>("Particles");
	Particles -> SetupAttachment(SphereComp);
}

void ASBasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = SphereComp->GetComponentLocation();
}

void ASBasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(UseRange)
	{
		if(FVector::Distance(StartLocation,SphereComp->GetComponentLocation())>Range){OnDisipate();}
	}
}

void ASBasicProjectile::OnDisipate()
{
}

void ASBasicProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* OtherActor, UPrimitiveComponent* otherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}
void ASBasicProjectile::UseOnHit()
{
	SphereComp->OnComponentHit.AddDynamic(this,&ASBasicProjectile::OnHit);
}

void ASBasicProjectile::OnOverlap(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap)
{
}
void ASBasicProjectile::UseOnOverlap()
{
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASBasicProjectile::OnOverlap);

}

