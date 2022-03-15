// Fill out your copyright notice in the Description page of Project Settings.


#include "NestWidget.h"
#include "MainCharacter.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "UObject/UnrealType.h"

void UNestWidget::NativeConstruct()
{
	Super::NativeConstruct();


	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetVisibility(ESlateVisibility::Hidden);
}

void UNestWidget::UpdateWidgetVisibility()
{
	MainCharacter->NestAnimationVisible ? SetVisibility(ESlateVisibility::Visible) : SetVisibility(ESlateVisibility::Hidden);
}

void UNestWidget::PlayAnimationByName()
{
	if (MainCharacter->NestAnimationVisible)
	{
		PlayAnimation(NestAnimation);
	}
}
