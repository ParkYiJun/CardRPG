// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);
DECLARE_MULTICAST_DELEGATE(FOnXpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDRPG_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:	

	void SetLevel(int32 Level);
	void SetHp(int32 NewHp);
	void HealHp(int32 HealAmount);
	void OnAttacked(float DamageAmount);
	void SetXP(int32 DropXP);


	int32 GetLevel() { return Level; }

	int32 GetHp() { return Hp; }

	int32 GetMaxHp() { return MaxHp; }

	float GetHpRatio() { return Hp / (float)MaxHp; }

	float GetXPRatio() { return CurrentXp / (float)XpNeeded; }

	int32 GetAttack() { return Attack; }



private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Defence;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 RecoveryHp;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 XpNeeded;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentXp=0;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 DropXp;

public:
	FOnHpChanged OnHpChanged;
	FOnHpChanged OnXpChanged;

};
