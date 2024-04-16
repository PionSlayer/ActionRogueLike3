// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp -> SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp -> SetupAttachment(SpringArmComp);

	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	bUseControllerRotationYaw = false;

	interactionComp = CreateDefaultSubobject<USInteractionComponent>("interactionComp");
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent -> BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);

	PlayerInputComponent -> BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("MoveSideWays",this,&ASCharacter::MoveSideWays);

	PlayerInputComponent -> BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	PlayerInputComponent -> BindAction("PrimaryInteraction",IE_Pressed,this,&ASCharacter::PrimaryInteract);
	
}

void ASCharacter::MoveForward(float Value)
{
	FRotator Direction = GetControlRotation();
	Direction.Pitch=0;
	Direction.Roll=0;
	AddMovementInput(Direction.Vector(),Value);
}
void ASCharacter::MoveSideWays(float Value)
{
	FRotator Direction = GetControlRotation();
	Direction.Pitch=0;
	Direction.Roll=0;
	FVector RightDirection = FRotationMatrix(Direction).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightDirection,Value);
}
void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_TimeElapsed,0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector start = CameraComp->GetComponentLocation();
	FVector end = start+(GetControlRotation().Vector()*10000);
	TArray<FHitResult> Hits;
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_PhysicsBody);
	Params.AddObjectTypesToQuery(ECC_WorldDynamic);
	Params.AddObjectTypesToQuery(ECC_WorldStatic);
	Params.AddObjectTypesToQuery(ECC_Pawn);
	GetWorld()->LineTraceMultiByObjectType(Hits,start,end,Params);
	FVector HitLocation;
	bool foundHit =false;
	for(FHitResult Hit: Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(HitActor != this)
			{
				foundHit=true;
			}
		}else{foundHit = true;}
		if(foundHit){HitLocation = Hit.ImpactPoint;break;}
	}
	if(!foundHit){HitLocation=end;}
	FVector vector =GetMesh()->GetSocketLocation("Muzzle_01");
 	FTransform transform =FTransform(UKismetMathLibrary::FindLookAtRotation(vector,HitLocation),vector);
	
 	FActorSpawnParameters params;
 	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	params.Instigator=this;
	
 	GetWorld()->SpawnActor<AActor>(ProjectileClass,transform,params);
}

void ASCharacter::PrimaryInteract()
{
	interactionComp->PrimaryInteraction();
}
