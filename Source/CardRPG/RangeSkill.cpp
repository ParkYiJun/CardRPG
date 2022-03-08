// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeSkill.h"
#include "Components/BoxComponent.h"
#include "BlueRush.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARangeSkill::ARangeSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RANGESKILL"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_TeleCharge/P_Skill_Telecharge_Ice_Proj_03.P_Skill_Telecharge_Ice_Proj_03'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);
	InitialLifeSpan = 1.0f;
	
}

// Called when the game starts or when spawned
void ARangeSkill::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle WaitHandle;
        float WaitTime=1.0f; //시간을 설정하고
        GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
        	{
        	    GetWorld()->SpawnActor<ABlueRush>(GetActorLocation(), FRotator(0,0,0));
        	}), WaitTime, false); //반복도 여기서 추가 변수를 선언해 설정가능

	
}

// Called every frame
void ARangeSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector Location = GetActorLocation();
       
    Location +=GetActorForwardVector()*Speed*DeltaTime;
    
    SetActorLocation(Location);
}

