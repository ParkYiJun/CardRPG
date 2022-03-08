// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
 DECLARE_MULTICAST_DELEGATE(FOnAttackHit);

UCLASS()
class CARDRPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UPlayerAnimInstance();

		virtual void NativeUpdateAnimation(float DeltaSeconds) override;

		void PlayAttackMontage();

		void PlayWallSkillMontage();
		
		void PlayDodgeMontage();
		
		void PlayRushSkillMontage();

		void JumpToSection(int32 SectionIndex);

		FName GetAttackMontageName(int32 SectionIndex);

private:
	UFUNCTION()
	void AnimNotify_AttackFire();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WallSkillMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DodgeMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* RushSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;
	
	UPROPERTY()
	UAnimMontage* ADGF;
	UPROPERTY()
	UAnimMontage* ADGB;
	UPROPERTY()
	UAnimMontage* ADGL;
	UPROPERTY()
	UAnimMontage* ADGR;
	UPROPERTY()
	UAnimMontage* ADGLF;
	UPROPERTY()
	UAnimMontage* ADGRF;
	UPROPERTY()
	UAnimMontage* ADGLB;
	UPROPERTY()
	UAnimMontage* ADGRB;
public:
	FOnAttackHit OnAttackHit;
private:
    float RushSpeed=1500.0f;
};
