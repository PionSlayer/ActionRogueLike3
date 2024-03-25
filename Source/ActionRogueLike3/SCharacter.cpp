// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent -> BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	
	PlayerInputComponent -> BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("MoveSideWays",this,&ASCharacter::MoveSideWays);

	PlayerInputComponent -> BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
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
	FVector vector =GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform transform =FTransform(GetControlRotation(),vector);

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	
	GetWorld()->SpawnActor<AActor>(ProjectileClass,transform,params);
}
