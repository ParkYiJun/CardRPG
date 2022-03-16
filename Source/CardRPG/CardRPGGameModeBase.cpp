// Copyright Epic Games, Inc. All Rights Reserved.


#include "CardRPGGameModeBase.h"
#include "MainCharacter.h"
#include "Engine/DataTable.h"
#include "Internationalization/Text.h"
#include "Blueprint/UserWidget.h"
#include "CardRPGStructure.h"
#include "MainPlayerController.h"
#include "PlayerCardState.h"

ACardRPGGameModeBase::ACardRPGGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter>BP_Char(TEXT("Blueprint'/Game/BluePrints/BP_MainCharacter.BP_MainCharacter_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DTCPP_Card(TEXT("DataTable'/Game/Developers/ooo95/Collections/UserInterface/Structure/DT_Cards.DT_Cards'"));

	if (DTCPP_Card.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed"));
		CardDataTable = DTCPP_Card.Object;
	}
	
	PlayerControllerClass = AMainPlayerController::StaticClass();
	PlayerStateClass = APlayerCardState::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> main(TEXT("/Game/UI/UI"));
	if (main.Succeeded()) {
		MainUI = main.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> lobby(TEXT("/Game/UI/Lobby"));
	if (lobby.Succeeded()) {
		LobbyUI = lobby.Class;
	}

	//static ConstructorHelpers::FClassFinder<UUserWidget> title(TEXT("/Game/UI/Title"));
	//if (title.Succeeded()) {
	//	TitleUI = title.Class;
	//}
	
}

void ACardRPGGameModeBase::BeginPlay() {
	for (int i = 0; i < CardNames.Num(); i++) {
		FCard ACard = *(CardDataTable->FindRow<FCard>(CardNames[i], CardNames[i].ToString()));
		
		FFormatNamedArguments Args;
		Args.Add(TEXT("Index"), FText::FromString(FString::FromInt(i)));
		Args.Add(TEXT("Name"), FText::FromName(CardNames[i]));

		FText msg = FText::Format(FTextFormat::FromString("Card Name[{Index}] : {Name}"), Args);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, msg.ToString());
		
	}

	ChangeMenuWidget(MainUI);
}


int32 ACardRPGGameModeBase::FindCard(FName name) {
	return CardNames.Find(name);
}

FName ACardRPGGameModeBase::CardAt(int32 idx) {
	if (CardNames.IsValidIndex(idx)) {
		return CardNames[idx];
	}
	else {
		return SpecialCard;
	}
}

void ACardRPGGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurUI != nullptr) {
		CurUI->RemoveFromViewport();
		CurUI = nullptr;
	}
	else {
		CurUI = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurUI != nullptr) {
			CurUI->AddToViewport();
		}
	}
}