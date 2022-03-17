// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "OpeningCard.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API UOpeningCard : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
		class UBorder* Back;
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* Rotating;
	
	UFUNCTION()
		void Open();
public:

};