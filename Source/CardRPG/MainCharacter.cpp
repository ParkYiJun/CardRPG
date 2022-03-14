// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAnimInstance.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Bullet.h"
#include "WallSkill.h"
#include "RangeSkill.h"
#include "Teleport.h"
#include "YellowRushStart.h"
#include "FollowingDrone.h"
#include "MovingSkill.h"
#include "SpiderMine.h"
#include "StatComponent.h"
#include "MyUserWidget.h"
#include "Components/WidgetComponent.h"
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

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/BluePrints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(64.0f, 120.0f, 120.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());



	Stats = CreateDefaultSubobject<UStatComponent>(TEXT("STATS"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.0f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/Developers/ooo95/Collections/UserInterface/WBP_Hp.WBP_Hp_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.0f, 50.0f));
	}
	

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PC = Cast<APlayerController>(GetController());
    CursorToWorld->SetVisibility(false);
    
}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMainCharacter::OnAttackMontageEnded);
		//AnimInstance->OnAttackHit.AddUObject(this, &AMainCharacter::AttackCheck);
	}

	HpBar->InitWidget();

	auto HpWidget = Cast<UMyUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
		HpWidget->BindHp(Stats);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr)
	{
		if (PC)
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

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
	PlayerInputComponent->BindAction(TEXT("Dodge"),EInputEvent::IE_Pressed,  this, &AMainCharacter::Dodge);
	PlayerInputComponent->BindAction(TEXT("Rush"),EInputEvent::IE_Pressed, this, &AMainCharacter::Rush);
	PlayerInputComponent->BindAction(TEXT("Fast"),EInputEvent::IE_Pressed,this, &AMainCharacter::Fast);
	PlayerInputComponent->BindAction(TEXT("Mine"),EInputEvent::IE_Pressed,this, &AMainCharacter::Mine);
	PlayerInputComponent->BindAction(TEXT("DroneAttack"), EInputEvent::IE_Pressed, this, &AMainCharacter::DroneAttack);
	PlayerInputComponent->BindAction(TEXT("WallSkill"),EInputEvent::IE_Pressed,this, &AMainCharacter::WallSkill);
	PlayerInputComponent->BindAction(TEXT("WallSkill"),EInputEvent::IE_Released,this, &AMainCharacter::WallSkillOn);
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

void AMainCharacter::Dodge()
{
	if ((IsAttacking == false) && (IsSkillUsing == false))
	{
	    AnimInstance->PlayDodgeMontage();
	}
	IsSkillUsing=true;

}

void AMainCharacter::Attack()
{
	if (IsAttacking || IsSkillUsing)
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
    CursorToWorld->SetVisibility(true);	
    auto PlayerController = UGameplayStatics::GetPlayerController(this,0);
    PlayerController->SetMouseLocation(600,300);
}
void AMainCharacter::WallSkillOn()
{
	if (IsSkillUsing)
	{
		return;
	}
	IsSkillUsing= true;
    CursorToWorld->SetVisibility(false);
	FVector WorldLocation;
    FVector WorldDirection;
	float DistanceAboveGround = 50;
    auto PlayerController = UGameplayStatics::GetPlayerController(this,0);
    PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
    
    FVector PlaneOrigin(0.0f, 0.0f, DistanceAboveGround);
    
    FVector ActorWorldLocation = FMath::LinePlaneIntersection(
    	WorldLocation,
    	WorldLocation + WorldDirection,
    	PlaneOrigin,
    	FVector::UpVector);   		
    FRotator SpawnRotation = GetCapsuleComponent()->GetComponentRotation();
    
    AnimInstance->PlayWallSkillMontage();
    GetWorld()->SpawnActor<AWallSkill>(ActorWorldLocation, SpawnRotation);
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
	TelpoLoc = TeleportLocation->GetComponentLocation();
	FVector CurrentLoc= GetCapsuleComponent()->GetComponentLocation() + FVector(0, 0, -88);

	GetWorld()->SpawnActor<ATeleport>(TelpoLoc, FRotator(0, 0, 0));
	GetWorld()->SpawnActor<ATeleport>(CurrentLoc, FRotator(0, 0, 0));
	float WaitTime= 1.0f; //�ð��� �����ϰ�
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			SetActorLocation(TelpoLoc +FVector(0,0,88));
		}), WaitTime, false);
	IsSkillUsing = true;
}

void AMainCharacter::Fast()
{
	if (IsSkillUsing)
	{
		return;
	}
	AnimInstance->PlayWallSkillMontage();
	FVector CurrentLoc = GetCapsuleComponent()->GetComponentLocation() + FVector(0,0,-88);
	GetWorld()->SpawnActor<AMovingSkill>(CurrentLoc,FRotator(0,0,0));
	UCharacterMovementComponent* CM= GetCharacterMovement();
	WalkSpeed = CM->MaxWalkSpeed;
	CM->MaxWalkSpeed=WalkSpeed*2;


	float WaitTime = 10.0f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			ResetWalkSpeed();
		}), WaitTime, false);
	IsSkillUsing = true;

}

void AMainCharacter::Mine()
{
	if (IsSkillUsing)
	{
		return;
	}
	AnimInstance->PlayWallSkillMontage();
	FVector CurrentLoc = GetCapsuleComponent()->GetComponentLocation() + FVector(0, 0, -80);
	GetWorld()->SpawnActor<ASpiderMine>(CurrentLoc, FRotator(0, 0, 0));
	IsSkillUsing = true;
}

void AMainCharacter::ResetWalkSpeed()
{
	UCharacterMovementComponent* CM = GetCharacterMovement();
	CM->MaxWalkSpeed = WalkSpeed;
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
			}), WaitTime, true); //�ݺ��� ���⼭ �߰� ������ ������ ��������
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
			}), WaitTime, false); //�ݺ��� ���⼭ �߰� ������ ������ ��������
		return;
	}
}

void AMainCharacter::Rush()
{
    if (IsSkillUsing)
	{
		return;
	}

	AnimInstance->PlayRushSkillMontage();
	FVector SpawnLocation = IceSkillLocation->GetComponentLocation();
	FRotator SpawnRotation = GetCapsuleComponent()->GetComponentRotation();
	GetWorld()->SpawnActor<AYellowRushStart>(SpawnLocation, SpawnRotation);
	IsSkillUsing = true;

}


float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stats->OnAttacked(DamageAmount);
	return DamageAmount;
}

void AMainCharacter::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	IsAttacking = false;
	IsSkillUsing=false;

	OnAttackEnd.Broadcast();
}
