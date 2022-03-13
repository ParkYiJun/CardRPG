// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CardRPGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API ACardRPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ACardRPGGameModeBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Setting")
		TArray<FName> CardNames;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Setting")
		FName SpecialCard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* CardDataTable;

	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		int32 FindCard(FName name);
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		FName CardAt(int32 idx, bool& Valid);
};
