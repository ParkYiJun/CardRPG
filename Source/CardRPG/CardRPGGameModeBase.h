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
	UPROPERTY()
		class UAudioComponent* AudioComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Sound Asset")
		class UDataTable* Other_Sound;

public:
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		int32 FindCard(FName name);
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		FName CardAt(int32 idx);
	UFUNCTION(BlueprintCallable, Category = "Card Utilities")
		int32 GetCardCode(FName name);
	UFUNCTION(BlueprintCallable, Category = "Widget Utilities")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "Sound Utilities")
		class USoundCue* GetSound(int32 SoundCase);

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> MainUI;
	UPROPERTY(EditAnywhere, Category = "Sound")
		float SBGM;
	UPROPERTY(EditAnywhere, Category = "Sound")
		float SPSoundEffect;
	UPROPERTY(EditAnywhere, Category = "Sound")
		float SMSoundEffect;

	FORCEINLINE int32 GetCardsNum() { return this->CardNames.Num(); }
};
