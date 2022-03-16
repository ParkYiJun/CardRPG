// Fill out your copyright notice in the Description page of Project Settings.


#include "Spidering.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASpidering::ASpidering()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ASpidering::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpidering::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpidering::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ASpidering::melee_attack_Implementation()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
	return 0;
}

UAnimMontage* ASpidering::get_montage() const
{
	return montage;
}

