// Fill out your copyright notice in the Description page of Project Settings.


#include "CardDropActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "MainCharacter.h"

// Sets default values
ACardDropActor::ACardDropActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	RootComponent=CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/Bullet/P_Fireball_Projectile.P_Fireball_Projectile'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	SecCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("GetRange"));
	SecCollisionComp->SetupAttachment(CollisionComp);
	SecCollisionComp->SetRelativeScale3D(FVector(5.0f,5,5));
	SecCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACardDropActor::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/BluePrints/CurveFloat.CurveFloat'"));
	check(Curve.Succeeded());
	CurveFloat=Curve.Object;

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}


void ACardDropActor::TimeLineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLoc,EndLoc,Value);
	SetActorLocation(NewLocation);

}

void ACardDropActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Called when the game starts or when spawned
void ACardDropActor::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("On"));
	Super::BeginPlay();
	if (CurveFloat)
	{
		UE_LOG(LogTemp,Warning,TEXT("On"));
		FOnTimelineFloat TimeLineProgress;
		TimeLineProgress.BindUFunction(this,FName("TimeLineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimeLineProgress);
		CurveTimeline.SetLooping(true);

		StartLoc=GetActorLocation();

		CurveTimeline.PlayFromStart();
	}

	
}

// Called every frame
void ACardDropActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EndLoc = MainCharacter->GetActorLocation();
	CurveTimeline.TickTimeline(DeltaTime);
}

void ACardDropActor::XPEarned()
{

}

