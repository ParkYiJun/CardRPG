// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGameMode.h"

void ULobbyWidget::NativeConstruct() {
	Super::NativeConstruct();
	GetOwningPlayer()->SetInputMode(FInputModeUIOnly());

	BNextMain->OnClicked.AddDynamic(this, &ULobbyWidget::GotoNextLevel);
	TransferLevelName = TEXT("Level_Start");
}

void ULobbyWidget::GotoNextLevel() {
	
	ALobbyGameMode* lobbygamemode = Cast<ALobbyGameMode>(GetWorld()->GetAuthGameMode());
	if (lobbygamemode != nullptr) {
		lobbygamemode->GotoMainLevel();
	}
}
