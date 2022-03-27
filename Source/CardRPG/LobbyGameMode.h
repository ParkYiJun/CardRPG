// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyWidget.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class UUserWidget* CurrentUI;
	UPROPERTY()
		class UAudioComponent* IntroBGMPlayer;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Intro GameMode")
		TSubclassOf<UUserWidget> TitleWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Intro GameMode")
		TSubclassOf<ULobbyWidget> LobbyWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Intro Music")
		class USoundBase* TitleBGM;
	UPROPERTY(EditDefaultsOnly, Category = "Intro Music")
		class USoundBase* LobbyBGM;

private:
	ALobbyGameMode();
	virtual void BeginPlay() override;
	
	void ChangeFullWidget(TSubclassOf<UUserWidget> targetUI);
	void PlaySound(class USoundBase* targetSCue);

protected:
public:
	UFUNCTION(BlueprintCallable)
		void GotoLobby();
	UFUNCTION(BlueprintCallable)
		void GotoMainLevel();

};
