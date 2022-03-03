// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowingDrone.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "AIController.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Bullet.h"


// Sets default values
AFollowingDrone::AFollowingDrone()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AFollowingDrone::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	AIController = Cast<AAIController>(GetController());
	

	FTimerHandle WaitHandle;
	float WaitTime =0.2f; //시간을 설정하고
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			FollowPlayer();
		}), WaitTime, true); //반복도 여기서 추가 변수를 선언해 설정가능
}

// Called every frame
void AFollowingDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFollowingDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AFollowingDrone::FollowPlayer()
{
	auto Drone = MainCharacter->DroneLocation;
	//UE_LOG(LogTemp,Warning,TEXT("a"));

	FVector DS = Drone->GetComponentLocation();

if (GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))<=1000.0f)
{
	AIController->AAIController::MoveToLocation(DS, -1, false);
}
else
{
	SetActorLocation(DS);
}
}


