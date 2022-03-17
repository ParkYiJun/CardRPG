// Fill out your copyright notice in the Description page of Project Settings.


#include "OpeningCard.h"
#include "Components/Border.h"

void UOpeningCard::NativeConstruct() {
	Super::NativeConstruct();
	
	Back->OnMouseButtonDownEvent.BindUFunction(this, TEXT("Open"));
}

void UOpeningCard::Open() {
		PlayAnimation(Rotating);
}
