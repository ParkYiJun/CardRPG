// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "GameFramework/Controller.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CardRPGGameModeBase.h"
#include "MainCharacter.h"

AMainPlayerController::AMainPlayerController() {
	
	CardState = Cast<APlayerCardState>(this->PlayerState);
	if (CardState) {
		UE_LOG(LogTemp, Warning, TEXT("Cast Success: APlayerCardState"));
	}

	isDraw = true;
	isUse = true;
}

void AMainPlayerController::BeginPlay() {
	DelGetThree.BindUFunction(this, FName("CreateGetsEvent"));
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	if (LockCUsing) {
		if (isDraw) {
			DrawRandomCard();
			isDraw = false;
			isUse = true;
		}
	}
	else {
		if (!isDraw) isDraw = true;
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
	int32 cover = 0;
	for (int32 i = 0; i < CardState->CardLists.Num(); i++) {
		cover += CardState->CardLists[i];
		if (random <= cover) {
			ACardRPGGameModeBase* gamemode = Cast<ACardRPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			CurCard = gamemode->CardAt(i);
			AMainCharacter* character = Cast<AMainCharacter>(GetCharacter());
			if (character) {
				character->SkillCode = gamemode->GetCardCode(CurCard);
			}
			break;
		}
	}
}

void AMainPlayerController::GetNewCards() {
	for (int32 i = 0; i < 3; i++) {
		gatheredCard[i] = FMath::RandRange(0, CardState->CardLists.Last());
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

		Popup->AddToViewport(0);
	}
}

#pragma endregion