// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSkill.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MainCharacter.h"
#include "StatComponent.h"


// Sets default values
AWallSkill::AWallSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WALL"));
	CollisionComp->InitBoxExtent(FVector(50.0f,20.0f,80.0f));
	//CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireStorm.P_ky_fireStorm'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWallSkill::OnOverlapBegin);

	UE_LOG(LogTemp, Warning, TEXT("Created!"));
	InitialLifeSpan=7.0f;
}

void AWallSkill::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	float Damage = MainCharacter->Stats->GetAttack();
	FDamageEvent DamageEvent;
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("ONHIT!"));
		UGameplayStatics::ApplyDamage(OtherActor,Damage, NULL, GetOwner(),NULL);
	}

}

// Called when the game starts or when spawned
void AWallSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

