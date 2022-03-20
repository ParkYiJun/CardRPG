// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "CardRPGGameModeBase.h"

void ULobbyWidget::NativeConstruct() {
	Super::NativeConstruct();
	GetOwningPlayer()->SetInputMode(FInputModeUIOnly());

	BNextMain->OnClicked.AddDynamic(this, &ULobbyWidget::GotoNextLevel);
	TransferLevelName = TEXT("Level_Start");
}

void ULobbyWidget::GotoNextLevel() {
	ACardRPGGameModeBase* myGamemode = Cast<ACardRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	UE_LOG(LogTemp, Error, TEXT("Let's go to MainLevel"));
	if (myGamemode != nullptr) {
		myGamemode->SetMainUI();
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer()->SetShowMouseCursor(false);
	}
}