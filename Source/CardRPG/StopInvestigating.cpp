// Fill out your copyright notice in the Description page of Project Settings.


#include "StopInvestigating.h"
#include "Spidering_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"

UStopInvestigating::UStopInvestigating(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Stop Investigating");
}

EBTNodeResult::Type UStopInvestigating::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const cont = Cast<ASpidering_AIController>(owner_comp.GetAIOwner());
	cont->get_blackboard()->SetValueAsBool(GetSelectedBlackboardKey(), false);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
