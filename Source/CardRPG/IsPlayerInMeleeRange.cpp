// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInMeleeRange.h"
#include "Spidering_AIController.h"
#include "Spidering.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
#include <cmath>

UIsPlayerInMeleeRange::UIsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Melee Range");
}

void UIsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	//get NPC
	ASpidering_AIController* const cont = Cast<ASpidering_AIController>(owner_comp.GetAIOwner());
	ASpidering* const spidering = Cast<ASpidering>(cont->GetPawn());

	//get player character
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	float const distance = spidering->GetDistanceTo(player);

	UE_LOG(LogTemp, Warning, TEXT("Distance: %d"), distance);

	//write true or false depending on whether the player is within melee_range
	cont->get_blackboard()->SetValueAsBool(GetSelectedBlackboardKey(), distance <= melee_range);
}
   