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
	
	UPROPERTY(EditDefaultsOnly, Category = "Get Event Order")
		class UDataTable* CardTable;
	UPROPERTY(EditAnywhere, Category = "Get Event Order")
		int32 Index;

private:
	UPROPERTY()
		FName cardName;
	UPROPERTY(meta = (BindWidget))
		class UBorder* Back;
	UPROPERTY(meta = (BindWidget))
		class UBorder* Card;
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* Rotating;
	
	UFUNCTION()
		void Open();
	UFUNCTION()
		void SetCardBrush();
public: 

};