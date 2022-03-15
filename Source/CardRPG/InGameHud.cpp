// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHud.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.h"
#include "RockTempleWidget.h"
#include "NestWidget.h"
#include "DeadWidget.h"

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
	if (TempleImageWidgetClass)
	{
		TempleImageWidget = CreateWidget<URockTempleWidget>(GetWorld(),TempleImageWidgetClass);
		if (TempleImageWidget)
		{
			TempleImageWidget->AddToViewport();
		}
	}
	if (NestImageWidgetClass)
	{
		NestImageWidget = CreateWidget<UNestWidget>(GetWorld(), NestImageWidgetClass);
		if (NestImageWidget)
		{
			NestImageWidget->AddToViewport();
		}
	}
	if (DeadImageWidgetClass)
	{
		DeadImageWidget = CreateWidget<UDeadWidget>(GetWorld(), DeadImageWidgetClass);
		if (DeadImageWidget)
		{
			DeadImageWidget->AddToViewport();
		}
	}
}

void AInGameHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInGameHud::UpdateWidgetVisibilityTown()
{
	if (TownImageWidget)
	{
		TownImageWidget->UpdateWidgetVisibility();
	}
}

void AInGameHud::PlayAnimationByNameTown()
{
	if (TownImageWidget)
	{
		TownImageWidget->PlayAnimationByName();
	}

}

void AInGameHud::UpdateWidgetVisibilityRockTemple()
{
	if (TempleImageWidget)
	{
		TempleImageWidget->UpdateWidgetVisibility();
	}

}

void AInGameHud::PlayAnimationByNameRockTemple()
{
	if (TempleImageWidget)
	{
		TempleImageWidget->PlayAnimationByName();
	}

}

void AInGameHud::UpdateWidgetVisibilityNest()
{
	if (NestImageWidget)
	{
		NestImageWidget->UpdateWidgetVisibility();
	}

}

void AInGameHud::PlayAnimationByNameNest()
{
	if (NestImageWidget)
	{
		NestImageWidget->PlayAnimationByName();
	}
}

void AInGameHud::UpdateWidgetVisibilityDead()
{
	if (DeadImageWidget)
	{
		DeadImageWidget->UpdateWidgetVisibility();
	}

}

void AInGameHud::PlayAnimationByNameDead()
{
	if (DeadImageWidget)
	{
		DeadImageWidget->PlayAnimationByName();
	}

}
