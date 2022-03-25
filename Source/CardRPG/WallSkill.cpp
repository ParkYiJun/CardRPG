// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSkill.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MainCharacter.h"
#include "StatComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"


// Sets default values
AWallSkill::AWallSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WALL"));
	CollisionComp->InitBoxExtent(FVector(50.0f,20.0f,500.0f));
	//CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireStorm.P_ky_fireStorm'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWallSkill::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this,&AWallSkill::OnOverlapEnd);
	UE_LOG(LogTemp, Warning, TEXT("Created!"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);
	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-10.SE-10'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}
	//AudioComponent->SetSound(EffectSound);
	//AudioComponent->Play()
	InitialLifeSpan=7.0f;
}

void AWallSkill::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Damage=MainCharacter->Stats->GetAttack();
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GetOtherActor=OtherActor;
		float WaitTime = 1.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{

					UE_LOG(LogTemp, Warning, TEXT("DotF"));
					UGameplayStatics::ApplyDamage(GetOtherActor, Damage, NULL, GetOwner(), NULL);


			}), WaitTime, true);
	}

}


void AWallSkill::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(WaitHandle);
}

// Called when the game starts or when spawned
void AWallSkill::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(EffectSound);
	AudioComponent->SetVolumeMultiplier(10000.0f);
	AudioComponent->Play();
}

// Called every frame
void AWallSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

