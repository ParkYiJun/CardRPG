// Fill out your copyright notice in the Description page of Project Settings.


#include "CardRPG_CharacterBase.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

// Sets default values
ACardRPG_CharacterBase::ACardRPG_CharacterBase() :
	right_fist_collision_box(CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionBox")))
{

	PrimaryActorTick.bCanEverTick = true;
	if (right_fist_collision_box)
	{
		FVector const extent(5.0f);
		right_fist_collision_box->SetBoxExtent(extent, false);
		right_fist_collision_box->SetCollisionProfileName("NoCollision");
	}

}

// Called when the game starts or when spawned
void ACardRPG_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (right_fist_collision_box)
	{
		FAttachmentTransformRules const rules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false);
		right_fist_collision_box->AttachToComponent(GetMesh(), rules, "hand_r_socket");
		right_fist_collision_box->SetRelativeLocation(FVector(-7.0f, 0.0f, 0.0f));
	}
	
}

// Called every frame
void ACardRPG_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACardRPG_CharacterBase::attack_start()
{
	right_fist_collision_box->SetCollisionProfileName("Fist");
	right_fist_collision_box->SetNotifyRigidBodyCollision(true);
}

void ACardRPG_CharacterBase::attack_end()
{
	right_fist_collision_box->SetCollisionProfileName("NoCollision");
	right_fist_collision_box->SetNotifyRigidBodyCollision(false);
}

