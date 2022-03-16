// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"
#include "CardRPGGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}


void UStatComponent::SetLevel(int32 NewLevel)
{
	auto GameInstance = Cast<UCardRPGGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance)
	{
		auto StatData = GameInstance->GetStatData(NewLevel);
		if (StatData)
		{
			Level = StatData->Level;
			SetHp(StatData->MaxHp);
			MaxHp = StatData->MaxHp;
			Attack = StatData->Attack;
			Defence=StatData->Defence;
			RecoveryHp= StatData->RecoveryHp;
			DropXp= StatData->DropXp;
			XpNeeded= StatData->XpNeeded;
		}
	}

}

void UStatComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
		Hp = 0;

	OnHpChanged.Broadcast();
}

void UStatComponent::HealHp(int32 HealAmount)
{
	UE_LOG(LogTemp,Warning,TEXT("Level: %d"), Level);
	Hp=Hp+HealAmount;
	if (Hp>MaxHp)
	{
		Hp=MaxHp;
	}
	OnHpChanged.Broadcast();
}

void UStatComponent::OnAttacked(float DamageAmount)
{
	int32 NewHp = Hp - DamageAmount;

	SetHp(NewHp);

	UE_LOG(LogTemp, Warning, TEXT("onAttacked %d"), Hp);
}

void UStatComponent::SetXP(int32 DropXP)
{
	CurrentXp= CurrentXp+DropXP;
	if (CurrentXp>=XpNeeded)
	{
		CurrentXp = CurrentXp - XpNeeded;
		Level+=1;
		SetLevel(Level);
	}
	OnXpChanged.Broadcast();
}

