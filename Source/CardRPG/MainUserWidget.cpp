// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUserWidget.h"
#include "MainCharacter.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "UObject/UnrealType.h"


void UMainUserWidget::NativeConstruct()
{

	Super::NativeConstruct();


	MainCharacter=Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	SetVisibility(ESlateVisibility::Hidden);
}



void UMainUserWidget::UpdateWidgetVisibility()
{

MainCharacter->TownAnimationVisible ? SetVisibility(ESlateVisibility::Visible) : SetVisibility(ESlateVisibility::Hidden);

}

void UMainUserWidget::PlayAnimationByName()
{
	if (MainCharacter->TownAnimationVisible)
	{
		PlayAnimation(TownAnimation);
	}

}

