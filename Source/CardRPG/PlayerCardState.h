// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCardState.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API APlayerCardState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Card")
		bool SpecialCard;
	//UFUNCTION(Category = "Card Utilities")
	//	void SetCard();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CardList")
		TArray<int32> CardLists;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card List")
		int32 Total;
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		void AddCard(int32 index);
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		bool UseCard(int32 index);
private:
	void SetTotalCards();
};
