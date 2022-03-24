// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API ULevelWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:

	void BindLevel(class UStatComponent* PStats);
	
private:
	TWeakObjectPtr<class UStatComponent> CurrentStatComp;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* LevelText;
	void UpdateLevel();
};
