// Fill out your copyright notice in the Description page of Project Settings.


#include "Spidering.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

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

void ASpidering::melee_attack()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
}

UAnimMontage* ASpidering::get_montage() const
{
	return montage;
}

float ASpidering::get_health() const
{
	return health;
}

float ASpidering::get_max_health() const
{
	return max_health;
}

void ASpidering::set_health(float const new_health)
{
	health = new_health;
}

