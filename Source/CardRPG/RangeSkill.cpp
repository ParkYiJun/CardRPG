// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeSkill.h"
#include "Components/BoxComponent.h"
#include "BlueRush.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

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

	AudioComponent=CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);

	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-12.SE-12'"));
	if (EF.Succeeded())
	{
	EffectSound=EF.Object;
	}
	//AudioComponent->SetSound(EffectSound);
	//AudioComponent->Play();

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_TeleCharge/P_Skill_Telecharge_Ice_Proj_03.P_Skill_Telecharge_Ice_Proj_03'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ARangeSkill::OnOverlapBegin);
	InitialLifeSpan = 1.0f;
	
}

// Called when the game starts or when spawned
void ARangeSkill::BeginPlay()
{
	Super::BeginPlay();
	
	AudioComponent->SetSound(EffectSound);
	AudioComponent->Play();

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

void ARangeSkill::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10, NULL, GetOwner(), NULL);
	}

}

