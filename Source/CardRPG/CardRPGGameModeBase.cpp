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

	static ConstructorHelpers::FObjectFinder<UDataTable> DTCPP_Card(TEXT("DataTable'/Game/Data/DT_Card.DT_Card'"));

	if (DTCPP_Card.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed"));
		CardDataTable = DTCPP_Card.Object;
	}
	

	PlayerStateClass = APlayerCardState::StaticClass();	
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

int32 ACardRPGGameModeBase::GetCardCode(FName name) {
	FCard thatCard = *(CardDataTable->FindRow<FCard>(name, name.ToString()));
	return thatCard.SkillCode;
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