// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UStatComponent* StatComp);

	void UpdateHP();

private:
	TWeakObjectPtr<class UStatComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* PB_HpBar;
	
};
