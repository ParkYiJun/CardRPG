// Fill out your copyright notice in the Description page of Project Settings.


#include "HardAttackSkill.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MainCharacter.h"
#include "StatComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AHardAttackSkill::AHardAttackSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BIM"));
	CollisionComp->InitBoxExtent(FVector(100.0f, 30.0f, 30.0f));
	//CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	//CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/Fire/P_Beam_Laser_Fire_Large.P_Beam_Laser_Fire_Large'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(RootComponent);

	SecondCollisionComp=CreateDefaultSubobject<UBoxComponent>(TEXT("COllider"));
	SecondCollisionComp->InitBoxExtent(FVector(480,32,32));
	SecondCollisionComp->SetRelativeLocation(FVector(445,0,0));
	SecondCollisionComp->SetupAttachment(CollisionComp);


	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SecondCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHardAttackSkill::OnOverlapBegin);
	SecondCollisionComp->OnComponentEndOverlap.AddDynamic(this, &AHardAttackSkill::OnOverlapEnd);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);
	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-36.SE-36'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}
	InitialLifeSpan = 4.0f;

}

// Called when the game starts or when spawned
void AHardAttackSkill::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(EffectSound);
	AudioComponent->SetVolumeMultiplier(1000.0f);
	AudioComponent->Play();
}

// Called every frame
void AHardAttackSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CharacterLocation = MainCharacter->CastFrom->GetComponentLocation();
	FRotator CharacterRotation = MainCharacter->CastFrom->GetComponentRotation();

		SetActorLocation(CharacterLocation);
		SetActorRotation(MainCharacter->GetActorRotation());

}

void AHardAttackSkill::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GetOtherActor = OtherActor;
		float WaitTime = 0.3f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{

					UE_LOG(LogTemp, Warning, TEXT("O"));
					UGameplayStatics::ApplyDamage(GetOtherActor, MainCharacter->Stats->GetAttack(), NULL, GetOwner(), NULL);



			}), WaitTime, true);
	}

}

void AHardAttackSkill::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(WaitHandle);
}

