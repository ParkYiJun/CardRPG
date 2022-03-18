// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include"GameFramework/SpringArmComponent.h"
#include"Camera/CameraComponent.h"
#include"Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
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
#include "HealSkill.h"
#include "ShieldSkill.h"
#include "CardDropActor.h"
#include "InGameHud.h"
#include "HardAttackSkill.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "InteractionInterface.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "ai_tags.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

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
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteraactionBox"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation=true;
	Camera->SetupAttachment(SpringArm);
	CastFrom->SetupAttachment(GetCapsuleComponent());
	DroneLocation->SetupAttachment(GetCapsuleComponent());
	FireTornadoLocation->SetupAttachment(GetCapsuleComponent());
	IceSkillLocation->SetupAttachment(GetCapsuleComponent());
	TeleportLocation->SetupAttachment(GetCapsuleComponent());
	InteractionBox->SetupAttachment(RootComponent);

	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f));
	CastFrom->SetRelativeLocation(FVector(85.f,0.f,20.f));
	DroneLocation->SetRelativeLocation(FVector(5.0f, 140.0f, 45.0f));
	FireTornadoLocation->SetRelativeLocation(FVector(500.0f, 0.f,0.0f));
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
	CursorToWorld->DecalSize = FVector(64.0f, 130.0f, 120.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());



	Stats = CreateDefaultSubobject<UStatComponent>(TEXT("STATS"));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bStartWithTickEnabled = true;

	setup_stimulus();
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	PC = Cast<APlayerController>(GetController());
    CursorToWorld->SetVisibility(false);
	//InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnBoxBeginOverlap);
	//InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnBoxEndOverlap);
}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMainCharacter::OnAttackMontageEnded);
	}

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

	TArray<AActor*>OverlappingActors;
	InteractionBox->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num()==0)
	{
		if (Interface)
		{
			Interface->HideInteractionWidget();
			Interface=nullptr;
		}
		return;
	}

	AActor* CloestActor = OverlappingActors[0];

	for (auto CurrentActor:OverlappingActors)
	{
		if (GetDistanceTo(CurrentActor)<GetDistanceTo(CloestActor))
		{
			CloestActor=CurrentActor;
		}
	}

	if (Interface)
	{
		Interface->HideInteractionWidget();
	}

	Interface= Cast<IInteractionInterface>(CloestActor);

	if (Interface)
	{
		Interface->ShowInteractionWidget();
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Yaw);
	PlayerInputComponent->BindAxis(TEXT("Lookup"),this, &AMainCharacter::LookUp);
	PlayerInputComponent->BindAction(TEXT("Attack"),EInputEvent::IE_Pressed,this,&AMainCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Dodge"),EInputEvent::IE_Pressed,  this, &AMainCharacter::Dodge);
	PlayerInputComponent->BindAction(TEXT("Rush"),EInputEvent::IE_Pressed, this, &AMainCharacter::Rush);
	PlayerInputComponent->BindAction(TEXT("Fast"),EInputEvent::IE_Pressed,this, &AMainCharacter::Fast);
	PlayerInputComponent->BindAction(TEXT("Mine"),EInputEvent::IE_Pressed,this, &AMainCharacter::Mine);
	PlayerInputComponent->BindAction(TEXT("Heal"),EInputEvent::IE_Pressed,this, &AMainCharacter::Heal);
	PlayerInputComponent->BindAction(TEXT("Shield"),EInputEvent::IE_Pressed,this, &AMainCharacter::Shield);
	PlayerInputComponent->BindAction(TEXT("GetXp"),EInputEvent::IE_Pressed,this, &AMainCharacter::GenerateXp);
	PlayerInputComponent->BindAction(TEXT("DroneAttack"), EInputEvent::IE_Pressed, this, &AMainCharacter::DroneAttack);
	PlayerInputComponent->BindAction(TEXT("WallSkill"),EInputEvent::IE_Pressed,this, &AMainCharacter::WallSkill);
	PlayerInputComponent->BindAction(TEXT("WallSkill"),EInputEvent::IE_Released,this, &AMainCharacter::WallSkillOn);
	PlayerInputComponent->BindAction(TEXT("IceSkill"),EInputEvent::IE_Pressed,this, &AMainCharacter::RangeSkill);
	PlayerInputComponent->BindAction(TEXT("Teleport"),EInputEvent::IE_Pressed,this, &AMainCharacter::Teleport);
	//Interact Key
	PlayerInputComponent->BindAction(TEXT("Interact"),EInputEvent::IE_Pressed,this, &AMainCharacter::OnInteract);
	PlayerInputComponent->BindAction(TEXT("Distract"), IE_Pressed, this, &AMainCharacter::on_distract);
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

void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
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
	if (AttackIndex<5)
	{
		GetWorld()->SpawnActor<ABullet>(SpawnLocation, SpawnRotation);
	}
	else
	{
		GetWorld()->SpawnActor<AHardAttackSkill>(SpawnLocation,SpawnRotation);
	}

	AnimInstance->JumpToSection(AttackIndex);

	AttackIndex = (AttackIndex + 1) % 6;
	IsAttacking = true;

}

void AMainCharacter::UseSkill() {  //Binding Q Key Pressed
	switch (SkillCode) {
	case 101:
		WallSkill();
		break;
	case 102:
		Rush(); //Yellow Rush
		break;
	case 103:
		Fast();
		break;
	case 104:
		Mine();
		break;
	case 105:
		Heal();
		break;
	case 106:
		Shield();
		break;
	case 107:
		RangeSkill();
		break;
	case 108:
		Teleport();
		break;
	case 109: //ice_explosion
		break;
	case 110: //Blue Rush
		break;
	default:
		break;
	}
}

void AMainCharacter::UseSkill_R() { //Binding Q Key Released
	switch (SkillCode)
	{
	case 101:
		WallSkillOn();
		break;
	default:
		break;
	}
}

#pragma region Q Skills
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

void AMainCharacter::WallSkill()
{
	UE_LOG(LogTemp, Warning,TEXT("WALLSKILL"));
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

/*
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
*/
	UE_LOG(LogTemp, Warning, TEXT("WALLSKILLON"));
	if (IsSkillUsing)
	{
		return;
	}
	IsSkillUsing= true;
    CursorToWorld->SetVisibility(false);
	FVector WorldLocation;
    FVector WorldDirection;
	float DistanceAboveGround = CursorToWorld->GetComponentLocation().Z;
	//float DistanceAboveGround=50.0f;

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

void AMainCharacter::Heal()
{
	if (IsSkillUsing)
	{
		return;
	}
	AnimInstance->PlayWallSkillMontage();
	FVector CurrentLoc = GetCapsuleComponent()->GetComponentLocation() + FVector(0, 0, -80);
	GetWorld()->SpawnActor<AHealSkill>(CurrentLoc, FRotator(0, 0, 0));
	Stats->HealHp(50);
	IsSkillUsing = true;

}

void AMainCharacter::Shield()
{
	if (IsSkillUsing)
	{
		return;
	}
	AnimInstance->PlayWallSkillMontage();
	FVector CurrentLoc = GetCapsuleComponent()->GetComponentLocation() + FVector(0, 0, -80);
	GetWorld()->SpawnActor<AShieldSkill>(CurrentLoc, FRotator(0, 0, 0));
	IsSkillUsing = true;


}

#pragma endregion

void AMainCharacter::GenerateXp()
{
	GetWorld()->SpawnActor<ACardDropActor>(FireTornadoLocation->GetComponentLocation(), FRotator(0, 0, 0));
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

void AMainCharacter::Dead()
{
	IsSkillUsing = true;
	AnimInstance->PlayDeadMontage();
	InGameHud = Cast<AInGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	InGameHud->UpdateWidgetVisibilityDead();
	InGameHud->PlayAnimationByNameDead();
	float WaitTime = 1.0;
	GetWorld()->GetTimerManager().SetTimer(WaidHandleDead, FTimerDelegate::CreateLambda([&]()
		{	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			UE_LOG(LogTemp, Warning, TEXT("DEAD"));
			GetCharacterMovement()->Deactivate();
			GetMesh()->SetSimulatePhysics(true);
			AnimInstance->StopSlotAnimation(0.1f, "DefaultSlot");
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}), WaitTime, false);
}





float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsImmune==true)
	{
		return DamageAmount;
	}
	Stats->OnAttacked(DamageAmount);
	AnimInstance->PlayAttackedMontage();
	if (Stats->GetHp()<=0 && IsDead==false)
	{
		Dead();
		IsDead=true;
	}
	return DamageAmount;
}

float AMainCharacter::GetXP(float XpAmount)
{
	Stats->SetXP(XpAmount);
	return XpAmount;
}

/*void AMainCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interface=Cast<IInteractionInterface>(OtherActor);

	if (Interface)
	{
		Interface->ShowInteractionWidget();
	}
}

void AMainCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (Interface)
	{
		Interface->HideInteractionWidget();
		Interface=nullptr;
	}

}
*/

void AMainCharacter::OnInteract()
{
	if (Interface)
	{
		Interface->InteractWithMe();
	}
}

void AMainCharacter::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf < UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

void AMainCharacter::on_distract()
{
	if (distraction_sound)
	{
		FVector const loc = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), distraction_sound, loc);
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), loc, 1.0f, this, 0.0f, tags::noise_tag);
	}
}

void AMainCharacter::OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	IsAttacking = false;
	IsSkillUsing=false;
	if (IsDead==true)
	{
		IsAttacking = true;
		IsSkillUsing = true;
	}

	OnAttackEnd.Broadcast();
}
