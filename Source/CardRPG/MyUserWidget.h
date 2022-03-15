// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	void BindHp(class UStatComponent* StatComp);

	void UpdateHP();

	void TownImageUpdate();

private:
	TWeakObjectPtr<class UStatComponent> CurrentStatComp;
	float gaugeWidth = 0.0f;
	class UCanvasPanelSlot* GaugeSlot;
	
	void UpdateGauge(float width);
	
	UPROPERTY(meta = (BindWidget))
		class UImage* Gauge;

};
