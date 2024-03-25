// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionProfileName("PhysicsActor");
	RootComponent=Mesh;
	Mesh->SetSimulatePhysics(true);
	Mesh->OnComponentHit.AddDynamic(this,&ASExplosiveBarrel::OnHit);

	RadialComp = CreateDefaultSubobject<URadialForceComponent>("RadialComp");
	RadialComp->Radius=2000;
	RadialComp->ImpulseStrength=2000;
	RadialComp->bIgnoreOwningActor=true;
	RadialComp->bImpulseVelChange=true;
	RadialComp->SetupAttachment(Mesh);
}
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherComp->GetCollisionObjectType()==ECC_GameTraceChannel1)
	{
		RadialComp->FireImpulse();
		FVector vector = OtherComp->GetComponentVelocity();
		vector.Z = vector.Z*2;
		Mesh->AddImpulse(vector*500);
	}
}


