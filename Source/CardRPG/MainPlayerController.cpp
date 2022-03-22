// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "GameFramework/Controller.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CardRPGGameModeBase.h"
#include "MainCharacter.h"

AMainPlayerController::AMainPlayerController() {
	isDraw = true;
	isUse = true;
	LockCUsing = true;
	gatheredCard.Init(0, 3);
}

void AMainPlayerController::BeginPlay() {
	CardState = Cast<APlayerCardState>(PlayerState);

	if (CardState != nullptr) {
		UE_LOG(FantasyHolic, Log, TEXT("Cast Success: APlayerCardState"));
	}

	DelGetThree.BindUFunction(this, FName("CreateGetsEvent"));
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	if (!LockCUsing) {
		if (isDraw) {
			UE_LOG(FantasyHolic, Log, TEXT("is Draw: %d"), isDraw);
			DrawRandomCard();
			isDraw = false;
			isUse = true;
		}
	}
	else {
		if (!isDraw) isDraw = true;
	}

	if (WasInputKeyJustPressed(EKeys::N)) {
		CardState->DebugSlotsLists();
	}
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Slots"), EInputEvent::IE_Pressed, this, &AMainPlayerController::OpeningCardList);
	//InputComponent->BindAction(TEXT("X"), EInputEvent::IE_Pressed, this, &AMainPlayerController::ClosingPopups);
}

#pragma region Control Variables Function
void AMainPlayerController::OpeningCardList() {
	bShowCardList = !bShowCardList;

	if (!bShowCardList) {
		bShowDetail = false;
		this->SetInputMode(FInputModeGameOnly());
		SetShowMouseCursor(false);
	}
	else {
		this->SetInputMode(FInputModeGameAndUI());
		SetShowMouseCursor(true);
	}
	
}

void AMainPlayerController::ClosingPopups() {
	if (bShowDetail) bShowDetail = false;
	else
		if (bShowCardList) bShowCardList = false;
}
#pragma endregion

#pragma region Can Move Later
void AMainPlayerController::GetCards() {
	ACardRPGGameModeBase* gamemode = Cast<ACardRPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//특수 카드 분기 필요

	int32 random = -1;
	for (int32 i = 0; i < 3; i++) {
		random = FMath::RandRange(0, gamemode->GetCardsNum() - 1);
		CardState->AddCard(random);
	}
}

void AMainPlayerController::DrawRandomCard() {
	int32 random = FMath::RandRange(1, CardState->Total);
	UE_LOG(FantasyHolic, Log, TEXT("Random Card: %d"), random);
	int32 cover = 0;
	for (int32 i = 0; i < CardState->CardLists.Num(); i++) {
		cover = CardState->ArrayAt(i) + cover;
		UE_LOG(FantasyHolic, Log, TEXT("Coverage: %d"), cover);
		if (random <= cover) {
			ACardRPGGameModeBase* gamemode = Cast<ACardRPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			CurCard = gamemode->CardAt(i);
			UE_LOG(FantasyHolic, Log, TEXT("Cur Card Setting : %s"), &CurCard);
			AMainCharacter* character = Cast<AMainCharacter>(GetCharacter());
			if (character) {
				character->SkillCode = gamemode->GetCardCode(CurCard);
			}
			break;
		}
	}
}

void AMainPlayerController::GetNewCards() {
	int32 last = Cast<ACardRPGGameModeBase>(GetWorld()->GetAuthGameMode())->GetCardsNum();
	LockCUsing = false;
	UE_LOG(FantasyHolic, Log, TEXT("last Index : %d"), last);

	for (int32 i = 0; i < 3; i++) {
		gatheredCard[i] = FMath::RandRange(0, last-1);
		CardState->AddCard(gatheredCard[i]);
	}
}

#pragma endregion
#pragma region Delegate

void AMainPlayerController::CreateGetsEvent() {
	UUserWidget* Popup = CreateWidget(this, CardGetEvent_UI);
	if (Popup != nullptr) {
		SetPause(true);
		SetShowMouseCursor(true);
		GetNewCards();
		Popup->AddToViewport(0);
	}
}

#pragma endregion