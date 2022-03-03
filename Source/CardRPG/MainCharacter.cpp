// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebughelpers.h"
#include "PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Bullet.h"
#include "WallSkill.h"
#include "RangeSkill.h"
#include "Teleport.h"
#include "FollowingDrone.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CastFrom= CreateDefaultSubobject<USceneComponent>(TEXT("CASTFROM"));
	DroneLocation= CreateDefaultSubobject<USceneComponent>(TEXT("DRONELOCATION"));
	FireTornadoLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FIRETORNADOLOCATION"));
	IceSkillLocation= CreateDefaultSubobject<USceneComponent>(TEXT("ICESKILLLOCATION"));
	TeleportLocation = CreateDefaultSubobject<USceneComponent>(TEXT("TELEPORTLOCATION"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	CastFrom->SetupAttachment(GetCapsuleComponent());
	DroneLocation->SetupAttachment(GetCapsuleComponent());
	FireTornadoLocation->SetupAttachment(GetCapsuleComponent());
	IceSkillLocation->SetupAttachment(GetCapsuleComponent());
	TeleportLocation->SetupAttachment(GetCapsuleComponent());

	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f));
	CastFrom->SetRelativeLocation(FVector(85.f,0.f,20.f));
	DroneLocation->SetRelativeLocation(FVector(5.0f, 140.0f, 45.0f));
	FireTornadoLocation->SetRelativeLocation(FVector(1000.0f, 0.f,-88.0f));
	IceSkillLocation->SetRelativeLocation(FVector(20.0f,0.0f,0.0f));
	TeleportLocation->SetRelativeLocation(FVector(800.0f,0,-88.0f));

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM(TEXT("SkeletalMesh'/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC'"));


	if (SM.Succeeded())
	{	
		UE_LOG(LogTemp,Warning,TEXT("GetMesh Succeeded"));
		GetMesh()->SetSkeletalMesh(SM.Object);
	}


}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMainCharacter::OnAttackMontageEnded);
		AnimInstance->OnAttackHit.AddUObject(this, &AMainCharacter::AttackCheck);
	}

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Yaw);
	PlayerInputComponent->BindAction(TEXT("Attack"),EInputEvent::IE_Pressed,this,&AMainCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("DroneAttack"), EInputEvent::IE_Pressed, this, &AMainCharacter::DroneAttack);
	PlayerInputComponent->BindAction(TEXT("WallSkill"),EInputEvent::IE_Pressed,this, &AMainCharacter::WallSkill);
	PlayerInputComponent->BindAction(TEXT("IceSkill"),EInputEvent::IE_Pressed,this, &AMainCharacter::RangeSkill);
	PlayerInputComponent->BindAction(TEXT("Teleport"),EInputEvent::IE_Pressed,this, &AMainCharacter::Teleport);
}

void AMainCharacter::UpDown(float Value)
{	
	if ((IsAttacking==false)&&(IsSkillUsing==false))
	{
		UpdownValue = Value;
		AddMovementInput(GetActorForwardVector(), Value);
	}


}

void AMainCharacter::LeftRight(float Value)
{
	if ((IsAttacking == false) && (IsSkillUsing == false))
	{
		LeftRightValue = Value;
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMainCharacter::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void AMainCharacter::Attack()
{
	if (IsAttacking)
	{
		return;
	}
	AnimInstance->PlayAttackMontage();

	FVector SpawnLocation= CastFrom->GetComponentLocation();
	FRotator SpawnRotation=GetCapsuleComponent()->GetComponentRotation();
	GetWorld()->SpawnActor<ABullet>(SpawnLocation,SpawnRotation);

	AnimInstance->JumpToSection(AttackIndex);

	AttackIndex = (AttackIndex + 1) % 5;
	IsAttacking = true;

}

void AMainCharacter::WallSkill()
{
	if (IsSkillUsing)
	{
	return;
	}
	
	AnimInstance->PlayWallSkillMontage();
	FVector SpawnLocation = FireTornadoLocation->GetComponentLocation();
	FRotator SpawnRotation = GetCapsuleComponent()->GetComponentRotation();
	GetWorld()->SpawnActor<AWallSkill>(SpawnLocation,SpawnRotation);

	IsSkillUsing= true;
}

void AMainCharacter::RangeSkill()
{
	if (IsSkillUsing)
	{
		return;
	}

	AnimInstance->PlayWallSkillMontage();
	FVector SpawnLocation = IceSkillLocation->GetComponentLocation();
	FRotator SpawnRotation = GetCapsuleComponent()->GetComponentRotation();
	GetWorld()->SpawnActor<ARangeSkill>(SpawnLocation, SpawnRotation);
	IsSkillUsing = true;
}

void AMainCharacter::Teleport()
{
	if (IsSkillUsing)
	{
		return;
	}

	AnimInstance->PlayWallSkillMontage();
	FVector TelpoLoc = TeleportLocation->GetComponentLocation();
	FVector CurrentLocation= GetCapsuleComponent()->GetComponentLocation() + FVector(0, 0, -88);

	GetWorld()->SpawnActor<ATeleport>(TelpoLoc, FRotator(0, 0, 0));
	GetWorld()->SpawnActor<ATeleport>(CurrentLocation, FRotator(0, 0, 0));
	float WaitTime= 1.0f; //시간을 설정하고
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			SetActorLocation(TeleportLocation->GetComponentLocation());
		}), WaitTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
	IsSkillUsing = true;
}

void AMainCharacter::DroneAttack()
{
	float WaitTime=0.5f;
	if (DroneIsAttacking==false)
	{
		DroneIsAttacking=true;
		GetWorld()->GetTimerManager().SetTimer(WaitHandleDrone, FTimerDelegate::CreateLambda([&]()
			{
				FVector SpawnLocation = DroneLocation->GetComponentLocation();
				FRotator SpawnRotation = GetCapsuleComponent()->GetComponentRotation();
				GetWorld()->SpawnActor<ABullet>(SpawnLocation, SpawnRotation);
			}), WaitTime, true); //반복도 여기서 추가 변수를 선언해 설정가능
			return;
	}
	if (DroneIsAttacking==true)
	{
		DroneIsAttacking=false;
		GetWorld()->GetTimerManager().SetTimer(WaitHandleDrone, FTimerDelegate::CreateLambda([&]()
			{
				FVector SpawnLocation = DroneLocation->GetComponentLocation();
				FRotator SpawnRotation = GetCapsuleComponent()->GetComponentRotation();
				GetWorld()->SpawnActor<ABullet>(SpawnLocation, SpawnRotation);
			}), WaitTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
		return;
	}
}

void AMainCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.0f;
	float AttackRadius = 50.0f;

	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	FVector Vec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Vec * 0.5f;
	float HalfHegith = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;
	if (bResult)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;

	DrawDebugCapsule(GetWorld(), Center, HalfHegith, AttackRadius,
		Rotation, DrawColor, false, 2.0f);

	if (bResult && HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitResult.Actor->GetName());

		FDamageEvent DamageEvent;
	}
}

void AMainCharacter::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	IsAttacking = false;
	IsSkillUsing=false;

	OnAttackEnd.Broadcast();
}
