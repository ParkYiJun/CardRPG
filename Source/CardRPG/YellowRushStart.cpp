// Fill out your copyright notice in the Description page of Project Settings.


#include "YellowRushStart.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "StatComponent.h"
#include "YelloRush.h"

// Sets default values
AYellowRushStart::AYellowRushStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RUSHSTART"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_TeleCharge/P_Skill_Telecharge_Shock_Proj_03.P_Skill_Telecharge_Shock_Proj_03'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);
	InitialLifeSpan = 1.0f;

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AYellowRushStart::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AYellowRushStart::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle WaitHandle;
	float WaitTime = 1.0f; 
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			GetWorld()->SpawnActor<AYelloRush>(GetActorLocation(), FRotator(0, 0, 0));
		}), WaitTime, false); 


	
}

// Called every frame
void AYellowRushStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	FRotator Rotation= GetActorRotation();
	FVector CharacterLocation = MainCharacter->GetActorLocation();

	Location += GetActorForwardVector() * Speed * DeltaTime;
	//CharacterLocation+=MainCharacter->GetActorForwardVector()*Speed*DeltaTime;

	if (IsOverlap !=true)
	{
		SetActorLocation(Location);
		MainCharacter->SetActorLocation(Location);
		MainCharacter->SetActorRotation(Rotation);
	}
}

void AYellowRushStart::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	float Damage = MainCharacter->Stats->GetAttack();
	FDamageEvent DamageEvent;
	if (OtherActor!=MainCharacter && OtherActor && (OtherActor != this) && OtherComp)
	{
		IsOverlap = true;
		UE_LOG(LogTemp, Warning, TEXT("ONHIT!"));
		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, GetOwner(), NULL);
		
	}

}

