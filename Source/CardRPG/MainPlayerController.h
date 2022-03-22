// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CardRPG.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DataTable.h"
#include "PlayerCardState.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FGetCards);
UCLASS()
class CARDRPG_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMainPlayerController();

private:
	bool isDraw;
	bool isUse;
	int32 cardIndex;

	UPROPERTY()
		TArray<int32> gatheredCard;
	UFUNCTION()
		void CreateGetsEvent();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadOnly, Category = "Player State")
		APlayerCardState* CardState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event UI")
		TSubclassOf<UUserWidget> CardGetEvent_UI;
	
	UFUNCTION()
		void OpeningCardList();
	UFUNCTION()
		void ClosingPopups();
	UFUNCTION()
		void GetCards();

	UFUNCTION(BlueprintCallable, Category = "Card Skill")
		void DrawRandomCard();
	UFUNCTION()
		void GetNewCards();
public:
	UPROPERTY(BlueprintReadWrite, Category = "Card Skill")
		FName CurCard;
	UPROPERTY(BlueprintReadWrite, Category = "Control Variables")
		FName DetailCard;
	UPROPERTY(BlueprintReadWrite, Category = "Control Variables")
		bool LockCUsing;
	UPROPERTY(BlueprintReadWrite, Category = "Control Variables")
		bool bShowCardList;
	UPROPERTY(BlueprintReadWrite, Category = "Control Variables")
		bool bShowDetail;

	FORCEINLINE int32 WhereAt(int32 idx) { return gatheredCard[idx]; }

	FGetCards DelGetThree;
};


USTRUCT(Atomic)
struct FSkill : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ActionName;
};