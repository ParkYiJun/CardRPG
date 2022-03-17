// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "GameFramework/Controller.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CardRPGGameModeBase.h"

AMainPlayerController::AMainPlayerController() {
	
	CardState = Cast<APlayerCardState>(this->PlayerState);
	if (CardState) {
		UE_LOG(LogTemp, Warning, TEXT("Cast Success: APlayerCardState"));
	}

	isDraw = true;
	isUse = true;
}

void AMainPlayerController::BeginPlay() {
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

	if (WasInputKeyJustPressed(EKeys::Z)) {
		UUserWidget* Popup =  CreateWidget(this, CardGetEvent_UI);
		if (Popup != nullptr) {
			SetPause(true);
			SetShowMouseCursor(true);
			
			Popup->AddToViewport(0);
		}
	}
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction(TEXT("WallSkill"), EInputEvent::IE_Pressed, this, &AMainPlayerController::UsingCardSkill);
	//InputComponent->BindAction(TEXT("WallSkill"), EInputEvent::IE_Released, this, &AMainPlayerController::UsingCardSkill_R);
	InputComponent->BindAction(TEXT("Slots"), EInputEvent::IE_Pressed, this, &AMainPlayerController::OpeningCardList);
	//InputComponent->BindAction(TEXT("X"), EInputEvent::IE_Pressed, this, &AMainPlayerController::ClosingPopups);
	//InputComponent->BindAction(TEXT("E"), EInputEvent::IE_Pressed, this, &AMainPlayerController::ClosingPopups);
}

void AMainPlayerController::UsingCardSkill() {
	CardState->UseCard(cardIndex);
}

void AMainPlayerController::UsingCardSkill_R() {

}

void AMainPlayerController::OpeningCardList() {
	bShowCardList = !bShowCardList;
	SetShowMouseCursor(bShowCardList);
	if (!bShowCardList) bShowDetail = false;
	
}

void AMainPlayerController::ClosingPopups() {
	if (bShowDetail) bShowDetail = false;
	else
		if (bShowCardList) bShowCardList = false;
}

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
			break;
		}
	}
}

