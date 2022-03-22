// Fill out your copyright notice in the Description page of Project Settings.


#include "MineExplode.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

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

	InitialLifeSpan = 1.5f;
	


}

// Called when the game starts or when spawned
void AMineExplode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMineExplode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMineExplode::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
			UGameplayStatics::ApplyDamage(OtherActor, 10, NULL, GetOwner(), NULL);
	}
}

