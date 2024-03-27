

#include "SInteractionComponent.h"

#include "SGamePlayInterface.h"


USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void USInteractionComponent::PrimaryInteraction()
{
	AActor* Owner = GetOwner();
	FVector EyePosition;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyePosition,EyeRotation);
	FVector End = EyePosition+(EyeRotation.Vector()*1000);
	
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_WorldDynamic);

	float radius = 30;
	FCollisionShape Shape;
	Shape.SetSphere(radius);
	
	TArray<FHitResult>Hits;
	bool lineHit = GetWorld()->SweepMultiByObjectType(Hits,EyePosition,End,FQuat::Identity,Params,Shape);
	FColor lineColor = lineHit? FColor::Green : FColor::Red;

	for(FHitResult Hit: Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor->Implements<USGamePlayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(HitActor);
			ISGamePlayInterface::Execute_Interact(HitActor,MyPawn);
		}
	}
	DrawDebugLine(GetWorld(),EyePosition,End,lineColor,false,2,0,1);
}