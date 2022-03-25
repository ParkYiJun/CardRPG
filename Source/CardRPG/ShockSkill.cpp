// Fill out your copyright notice in the Description page of Project Settings.


#include "ShockSkill.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MainCharacter.h"
#include "StatComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AShockSkill::AShockSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WALL"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 500.0f));
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_Whirlwind/P_Whirlwind_Lightning_Veng_Typh_01.P_Whirlwind_Lightning_Veng_Typh_01'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AShockSkill::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AShockSkill::OnOverlapEnd);
	UE_LOG(LogTemp, Warning, TEXT("Created!"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);
	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-28.SE-28'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}
	//AudioComponent->SetSound(EffectSound);
	//AudioComponent->Play()
	InitialLifeSpan = 7.0f;
}

void AShockSkill::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GetOtherActor = OtherActor;
		float WaitTime = 1.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{

				UE_LOG(LogTemp, Warning, TEXT("DotF"));
				UGameplayStatics::ApplyDamage(GetOtherActor, 80, NULL, GetOwner(), NULL);


			}), WaitTime, true);
	}

}

void AShockSkill::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(WaitHandle);
}

// Called when the game starts or when spawned
void AShockSkill::BeginPlay()
{
	Super::BeginPlay();
	Super::BeginPlay();
	//AudioComponent->SetSound(EffectSound);
	//AudioComponent->SetVolumeMultiplier(10000.0f);
	//AudioComponent->Play();
}

// Called every frame
void AShockSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

