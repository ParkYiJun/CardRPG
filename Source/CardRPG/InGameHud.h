// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainUserWidget.h"
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


	void UpdateWidgetVisibility();

	void PlayAnimationByName();


public:

	UPROPERTY(EditDefaultsOnly, Category="Interactive")
	TSubclassOf<UUserWidget> TownImageWidgetClass;

private:

	UPROPERTY()
	UMainUserWidget* TownImageWidget;

};
