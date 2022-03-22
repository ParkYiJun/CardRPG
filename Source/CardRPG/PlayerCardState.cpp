// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCardState.h"
#include "Kismet/GameplayStatics.h"
#include "CardRPGGameModeBase.h"

void APlayerCardState::BeginPlay(){
	
	class ACardRPGGameModeBase* MyMode = Cast<ACardRPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	CardLists.Init( 0, MyMode->GetCardsNum());
	UE_LOG(FantasyHolic, Log, TEXT("Card list : %d"), CardLists.Num());
}

void APlayerCardState::AddCard(int32 index) {
	if (index >= 0) {
		CardLists[index]++;
		SetTotalCards();
	}
	else {
		CardLists.Add(1);
	}
}

bool APlayerCardState::UseCard(int32 index) {
	if (CardLists.IsValidIndex(index)) {
		CardLists[index]--;
		if (CardLists[index] < 0) {
			CardLists[index] = 0;
			return false;
		}
		SetTotalCards();
	}
	return true;
}

void APlayerCardState::SetTotalCards() {
	ACardRPGGameModeBase* gamemode = Cast<ACardRPGGameModeBase>(GetWorld()->GetAuthGameMode());
	Total = 0;
	for (int32 i = 0; i < gamemode->GetCardsNum(); i++) {
		Total += CardLists[i];
	}
}

void APlayerCardState::DebugSlotsLists() {
	for (int32 i = 0; i < CardLists.Num(); i++) {
		UE_LOG(FantasyHolic, Warning, TEXT("Array[%d]: %d°³"), i, CardLists[i]);
	}
}

int32 APlayerCardState::ArrayAt(int32 idx) {
	if (CardLists.IsValidIndex(idx)) return CardLists[idx];
	else return -1;
}