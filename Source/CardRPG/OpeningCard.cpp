// Fill out your copyright notice in the Description page of Project Settings.


#include "OpeningCard.h"
#include "Components/Border.h"
#include "Engine/DataTable.h"
#include "CardRPGGameModeBase.h"
#include "CardRPGStructure.h"

void UOpeningCard::NativeConstruct() {
	Super::NativeConstruct();
	SetCardBrush();
	Back->OnMouseButtonDownEvent.BindUFunction(this, TEXT("Open"));
}

void UOpeningCard::Open() {
		PlayAnimation(Rotating);
}

void UOpeningCard::SetCardBrush() {
	//UTexture2D* cardtexture = (CardTable->FindRow<FCard>(cardName, cardName.ToString()))->Image;
	//
	//if (cardtexture != nullptr) {
	//	Card->SetBrushFromTexture(cardtexture);
	//}
}