// Fill out your copyright notice in the Description page of Project Settings.


#include "IceSkill.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AIceSkill::AIceSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RANGESKILL"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Combat_Base/WeaponCombo/P_IB_OneShotAOE.P_IB_OneShotAOE'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);

	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-11.SE-11'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}


	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AIceSkill::OnOverlapBegin);
	InitialLifeSpan = 1.0f;
}

void AIceSkill::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10, NULL, GetOwner(), NULL);
	}

}

// Called when the game starts or when spawned
void AIceSkill::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(EffectSound);
	AudioComponent->Play();
	
}

// Called every frame
void AIceSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

