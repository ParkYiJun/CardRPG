// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderMine.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "MineExplode.h"

// Sets default values
ASpiderMine::ASpiderMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SETMINE"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Spider/Fire/P_CrawlingSpiders_CrawlMamma_Fire.P_CrawlingSpiders_CrawlMamma_Fire'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);


	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);
	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-7.SE-7'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}
	//AudioComponent->SetSound(EffectSound);
	//AudioComponent->Play();

	InitialLifeSpan = 3.1f;
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called when the game starts or when spawned
void ASpiderMine::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle WaitHandle;
	float WaitTime = 3.0f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			GetWorld()->SpawnActor<AMineExplode>(GetActorLocation(), FRotator(0, 0, 0));
		}), WaitTime, false);
	AudioComponent->SetSound(EffectSound);
	AudioComponent->Play();


	
}

// Called every frame
void ASpiderMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

