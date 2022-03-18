// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttack.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UMeleeAttack::UMeleeAttack(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// get the Spidering
	AAIController* const cont = owner_comp.GetAIOwner();


	if (ASpidering* const spidering = Cast<ASpidering>(cont->GetPawn()))
	{
		if (montage_has_finished(spidering))
		{
			spidering->melee_attack();
		}
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UMeleeAttack::montage_has_finished(ASpidering* const spidering)
{
	return spidering->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(spidering->get_montage());
}
