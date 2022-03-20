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

	UPROPERTY()
		UUserWidget* CurUI;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Setting")
		TArray<FName> CardNames;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Setting")
		FName SpecialCard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* CardDataTable;
public:
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		int32 FindCard(FName name);
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		FName CardAt(int32 idx);
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		int32 GetCardCode(FName name);
	UFUNCTION(BlueprintCallable, Category = "Widget Utilities")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "Widget Utilities")
		void GotoLobby();

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> TitleUI;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> LobbyUI;
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> MainUI;

	FORCEINLINE int32 GetCardsNum() { return this->CardNames.Num(); }
	FORCEINLINE void SetMainUI() { ChangeMenuWidget(MainUI); }
	FORCEINLINE void SetTitleUI() { ChangeMenuWidget(TitleUI); }
};
