// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (AllowPrivateAccess = "true"))
		FString TransferLevelName;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ShowName;
	UPROPERTY(meta = (BindWidget))
		class UButton* BNextMain;

	void GotoNextLevel();
};
