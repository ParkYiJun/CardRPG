// Fill out your copyright notice in the Description page of Project Settings.


#include "MineExplode.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "MainCharacter.h"
#include "StatComponent.h"
#include "Sound/SoundBase.h"
// Sets default values
AMineExplode::AMineExplode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ExplosionEffect"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_SpiderBoss/Impact/P_SpiderStab_Fire.P_SpiderStab_Fire'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMineExplode::OnOverlapBegin);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-8.SE-8'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}
	InitialLifeSpan = 1.5f;
	


}

// Called when the game starts or when spawned
void AMineExplode::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(EffectSound);
	AudioComponent->SetVolumeMultiplier(1000.0f);
	AudioComponent->Play();
}

// Called every frame
void AMineExplode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMineExplode::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	float Damage= MainCharacter->Stats->GetAttack();

	if (OtherActor && (OtherActor != this) && OtherComp && !MainCharacter)
	{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, GetOwner(), NULL);
	}
}

