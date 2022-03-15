// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHud.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.h"

AInGameHud::AInGameHud()
{

}

void AInGameHud::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHud::BeginPlay()
{
	Super::BeginPlay();

	if (TownImageWidgetClass)
	{
		TownImageWidget = CreateWidget<UMainUserWidget>(GetWorld(),TownImageWidgetClass);
		if (TownImageWidget)
		{
			TownImageWidget->AddToViewport();
		}
	}
}

void AInGameHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInGameHud::UpdateWidgetVisibility()
{
	if (TownImageWidget)
	{
		TownImageWidget->UpdateWidgetVisibility();
	}
}

void AInGameHud::PlayAnimationByName()
{
	if (TownImageWidget)
	{
		TownImageWidget->PlayAnimationByName();
	}

}
