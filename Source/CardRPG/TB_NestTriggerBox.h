// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TB_NestTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API ATB_NestTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	

public:
	ATB_NestTriggerBox();

	UPROPERTY()
		class AInGameHud* InGameHud;

	UPROPERTY()
		class AMainCharacter* MainCharacter;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);


	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
