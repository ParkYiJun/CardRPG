// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldSkill.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
// Sets default values
AShieldSkill::AShieldSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SHIELD"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 80.0f));
	RootComponent = CollisionComp;

	UE_LOG(LogTemp,Warning,TEXT("ON"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Armor/P_Reduced_Melee_Shield_01.P_Reduced_Melee_Shield_01'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);
	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-15.SE-15'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}
	//AudioComponent->SetSound(EffectSound);
	//AudioComponent->Play()

	UE_LOG(LogTemp, Warning, TEXT("HealSkill"));
	InitialLifeSpan = 4.5f;
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


}

// Called when the game starts or when spawned
void AShieldSkill::BeginPlay()
{
	AudioComponent->SetSound(EffectSound);
	AudioComponent->Play();
	MainCharacter->IsImmune=true;
	Super::BeginPlay();
	SetActorScale3D(FVector(0.3, 0.3, 0.8));

	FTimerHandle WaitHandle;
	float WaitTime=4.4f; //시간을 설정하고
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{

			MainCharacter->IsImmune=false;

		}), WaitTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
}

// Called every frame
void AShieldSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = MainCharacter->GetActorLocation();
	FRotator Rotation = MainCharacter->GetActorRotation();

	SetActorLocation(Location + FVector(0, 0, -88));
	SetActorRotation(Rotation);
}

