// Fill out your copyright notice in the Description page of Project Settings.


#include "Spidering.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "MainCharacter.h"
#include "StatComponent.h"
#include "MyUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SpideringAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASpidering::ASpidering() :
	widget_component(CreateDefaultSubobject<UWidgetComponent>(TEXT("healthBar")))
{
	Stats = CreateDefaultSubobject<UStatComponent>(TEXT("STATS"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	if (widget_component)
	{
		widget_component->SetupAttachment(RootComponent);
		widget_component->SetWidgetSpace(EWidgetSpace::World);
		widget_component->SetRelativeLocation(FVector(0.0f, 0.0f, 85.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Game/UI/HPXP/WCBP_HP"));
		if (widget_class.Succeeded())
		{
			widget_component->SetWidgetClass(widget_class.Class);
		}
	}
}

// Called when the game starts or when spawned
void ASpidering::BeginPlay()
{
	Super::BeginPlay();

	if (right_fist_collision_box)
	{
		right_fist_collision_box->OnComponentBeginOverlap.AddDynamic(this, &ASpidering::on_attack_overlap_begin);
		right_fist_collision_box->OnComponentEndOverlap.AddDynamic(this, &ASpidering::on_attack_overlap_end);
	}

	class UMyUserWidget* widget = Cast<UMyUserWidget>(widget_component->GetWidget());
	if (widget != nullptr) {
		widget->BindHp(Stats);
	}

}

void ASpidering::on_attack_overlap_begin(UPrimitiveComponent* const overlapped_component, AActor* const other_actor, UPrimitiveComponent* other_component, int const other_body_index, bool const from_sweep, FHitResult const& sweep_result)
{
	if (AMainCharacter* const player = Cast<AMainCharacter>(other_actor))
	{
		UGameplayStatics::ApplyDamage(other_actor, 10, NULL, GetOwner(), NULL);
	}
}

void ASpidering::on_attack_overlap_end(UPrimitiveComponent* const overlapped_component, AActor* const other_actor, UPrimitiveComponent* other_component, int const other_body_index)
{
}

void ASpidering::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<USpideringAnimInstance>(GetMesh()->GetAnimInstance());

}

// Called every frame
void ASpidering::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpidering::Dead()
{
	AnimInstance->PlayDeadMontage();
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

float ASpidering::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stats->OnAttacked(DamageAmount);
	if (Stats->GetHp() <= 0 && IsDead == false)
	{
		Dead();
		IsDead = true;
	}
	return DamageAmount;
}

// Called to bind functionality to input
void ASpidering::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpidering::melee_attack()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
}

UAnimMontage* ASpidering::get_montage() const
{
	return montage;
}

