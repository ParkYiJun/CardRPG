// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadWidget.h"
#include "MainCharacter.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "UObject/UnrealType.h"

void UDeadWidget::NativeConstruct()
{
	Super::NativeConstruct();


	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetVisibility(ESlateVisibility::Hidden);

}

void UDeadWidget::UpdateWidgetVisibility()
{
	MainCharacter->IsDead ? SetVisibility(ESlateVisibility::Visible) : SetVisibility(ESlateVisibility::Hidden);
}

void UDeadWidget::PlayAnimationByName()
{
	if (MainCharacter->IsDead)
	{
		PlayAnimation(DeadAnimation);
	}
}
