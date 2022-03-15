// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/public/UMG.h"
#include "NestWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API UNestWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void UpdateWidgetVisibility();
	

public:
	UPROPERTY()
		class AMainCharacter* MainCharacter;


	UPROPERTY(meta = (BindWidget))
		class UImage* NestImage;

	void PlayAnimationByName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* NestAnimation;

};
