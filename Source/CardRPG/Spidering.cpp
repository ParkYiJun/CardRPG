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
#include "healthBar.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "MainCharacter.h"
#include "StatComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpidering::ASpidering() :
	health(max_health),
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
		widget_component->SetWidgetSpace(EWidgetSpace::Screen);
		widget_component->SetRelativeLocation(FVector(0.0f, 0.0f, 85.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Game/UI/healthBar_BP"));
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

// Called every frame
void ASpidering::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto const uw = Cast<UhealthBar>(widget_component->GetUserWidgetObject());
	if (uw)
	{
		uw->set_bar_value_percent(health / max_health);
	}

}

float ASpidering::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	Stats->OnAttacked(DamageAmount);

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

float ASpidering::get_health() const
{
	return health;
}

float ASpidering::get_max_health() const
{
	return max_health;
}

void ASpidering::set_health(float const new_health)
{
	health = new_health;
}
