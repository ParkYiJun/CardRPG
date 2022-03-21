// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotify.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "CardRPG_CharacterBase.h"

void UAttackNotify::NotifyBegin(USkeletalMeshComponent* const mesh, UAnimSequenceBase* const animation, float const total_duration)
{
	if (mesh && mesh->GetOwner())
	{
		if (ACardRPG_CharacterBase* const character = Cast<ACardRPG_CharacterBase>(mesh->GetOwner()))
		{
			character->attack_start();
		}
	}
}


void UAttackNotify::NotifyEnd(USkeletalMeshComponent* const mesh, UAnimSequenceBase* const animation)
{
	if (mesh && mesh->GetOwner())
	{
		if (ACardRPG_CharacterBase* const character = Cast<ACardRPG_CharacterBase>(mesh->GetOwner()))
		{
			character->attack_end();
		}
	}
}
