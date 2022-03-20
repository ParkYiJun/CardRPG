// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "CardRPGGameModeBase.h"

void ULobbyWidget::NativeConstruct() {
	Super::NativeConstruct();

	BNextMain->OnClicked.AddDynamic(this, &ULobbyWidget::GotoNextLevel);
	TransferLevelName = TEXT("M_UITEST");
}

void ULobbyWidget::GotoNextLevel() {
	UGameplayStatics::OpenLevel(this, FName(*TransferLevelName));
}