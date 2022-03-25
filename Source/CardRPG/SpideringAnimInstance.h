// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SpideringAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackHit);

UCLASS()
class CARDRPG_API USpideringAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	USpideringAnimInstance();

		virtual void NativeUpdateAnimation(float DeltaSeconds) override;

		void PlayDeadMontage();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DeadMontage1;

public:
	FOnAttackHit OnAttackHit;
private:
	float RushSpeed = 1500.0f;
};
