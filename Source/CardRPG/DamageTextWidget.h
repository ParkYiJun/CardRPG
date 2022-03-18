// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/public/UMG.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	
	UPROPERTY()
		class AMainCharacter* MainCharacter;


	UPROPERTY(meta = (BindWidget))
		UTextBlock* DamageText;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* DamageAnimation;

	
};
