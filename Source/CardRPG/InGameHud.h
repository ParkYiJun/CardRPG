// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainUserWidget.h"
#include "RockTempleWidget.h"
#include "NestWidget.h"
#include "DeadWidget.h"
#include "InGameHud.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API AInGameHud : public AHUD
{
	GENERATED_BODY()

public:
	
	AInGameHud();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


	void UpdateWidgetVisibilityTown();

	void PlayAnimationByNameTown();

	void UpdateWidgetVisibilityRockTemple();

	void PlayAnimationByNameRockTemple();

	void UpdateWidgetVisibilityNest();

	void PlayAnimationByNameNest();

	void UpdateWidgetVisibilityDead();

	void PlayAnimationByNameDead();


public:

	UPROPERTY(EditDefaultsOnly, Category="Interactive")
	TSubclassOf<UUserWidget> TownImageWidgetClass;


	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
	TSubclassOf<UUserWidget> TempleImageWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
		TSubclassOf<UUserWidget> NestImageWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
		TSubclassOf<UUserWidget> DeadImageWidgetClass;
private:

	UPROPERTY()
	UMainUserWidget* TownImageWidget;

	UPROPERTY()
	URockTempleWidget* TempleImageWidget;

	UPROPERTY()
	UNestWidget* NestImageWidget;

	UPROPERTY()
	UDeadWidget* DeadImageWidget;

};
