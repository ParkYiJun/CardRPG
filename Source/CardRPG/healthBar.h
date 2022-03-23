// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "healthBar.generated.h"

/**
 * 
 */
UCLASS()
class CARDRPG_API UhealthBar : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, Category = "Target")
		bool HP_XP;
	void BindHp(class UStatComponent* StatComp);
	void BindXp(class UStatComponent* StatComp);
	void UpdateHP();
	void UpdateXP();

private:
	TWeakObjectPtr<class UStatComponent> CurrentStatComp;
	float gaugeWidth = 0.0f;
	class UCanvasPanelSlot* GaugeSlot;
	
	void UpdateGauge(float width);
	
	UPROPERTY(meta = (BindWidget))
		class UImage* Gauge;

};
