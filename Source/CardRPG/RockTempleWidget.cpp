// Fill out your copyright notice in the Description page of Project Settings.


#include "RockTempleWidget.h"
#include "MainCharacter.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "UObject/UnrealType.h"

void URockTempleWidget::NativeConstruct()
{
	Super::NativeConstruct();


	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetVisibility(ESlateVisibility::Hidden);
}

void URockTempleWidget::UpdateWidgetVisibility()
{
	MainCharacter->TempleAnimationVisible ? SetVisibility(ESlateVisibility::Visible) : SetVisibility(ESlateVisibility::Hidden);
}

void URockTempleWidget::PlayAnimationByName()
{
	if (MainCharacter->TempleAnimationVisible)
	{
		PlayAnimation(TempleAnimation);
	}


}
