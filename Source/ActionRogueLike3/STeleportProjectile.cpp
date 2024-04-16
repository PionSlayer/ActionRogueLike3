

#include "STeleportProjectile.h"

#include "InputBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	Begin=false;
	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	UseRange = true;
	Range = 2000;
	UseOnHit();
}



void ASTeleportProjectile::OnDisipate()
{
	Super::OnDisipate();
	BeginTeleport();
}

void ASTeleportProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* OtherActor, UPrimitiveComponent* otherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(hitComp, OtherActor, otherComp, NormalImpulse, Hit);

		BeginTeleport();
	
}



void ASTeleportProjectile::BeginTeleport()
{
	if(!Begin)
	{
		Begin=true;
		Projectile->SetVelocityInLocalSpace(FVector::Zero());
		Particles->Deactivate();
		if(ParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ParticleSystem,SphereComp->GetComponentLocation(),FRotator::ZeroRotator,true);
		}
		GetWorld()->GetTimerManager().SetTimer(Timer,this,&ASTeleportProjectile::Teleport,CountDown);
	}
}
void ASTeleportProjectile::Teleport()
{
	GetInstigator()->SetActorLocation(SphereComp->GetComponentLocation());
}