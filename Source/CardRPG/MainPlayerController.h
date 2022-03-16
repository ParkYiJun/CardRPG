// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DataTable.h"
#include "PlayerCardState.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMainPlayerController();

private:
	bool isDraw;
	bool isUse;
	int32 cardIndex;
	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player State")
		APlayerCardState* CardState;
	
	UFUNCTION()
		void UsingCardSkill();
	UFUNCTION()
		void UsingCardSkill_R();
	UFUNCTION()
		void OpeningCardList();
	UFUNCTION()
		void ClosingPopups();
	UFUNCTION()
		void GetCards();

	UFUNCTION(BlueprintCallable, Category = "Card Skill")
		void DrawRandomCard();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Skill")
		FName CurCard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Variables")
		FName DetailCard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Variables")
		bool LockCUsing;
	UPROPERTY(BlueprintReadWrite, Category = "Control Variables")
		bool bShowCardList;
	UPROPERTY(BlueprintReadWrite, Category = "Control Variables")
		bool bShowDetail;
};


USTRUCT(Atomic)
struct FSkill : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ActionName;
};