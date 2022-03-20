// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API UAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	void NotifyBegin(USkeletalMeshComponent* const mesh, UAnimSequenceBase* const animation, float const total_duration);
	void NotifyEnd(USkeletalMeshComponent* const mesh, UAnimSequenceBase* const animation) override;
};
