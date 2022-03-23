// Fill out your copyright notice in the Description page of Project Settings.


#include "healthBar.h"
#include "StatComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Spidering.h"

void UhealthBar::NativeConstruct() {
	GaugeSlot = Cast<UCanvasPanelSlot>(Gauge->Slot);
	if (GaugeSlot) {
		gaugeWidth = GaugeSlot->GetSize().X;
		UE_LOG(LogTemp, Warning, TEXT("Width: %f"), gaugeWidth);
	}


	if (HP_XP)
		UpdateHP();
	else
		UpdateXP();
}

void UhealthBar::BindHp(UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	CurrentStatComp->OnHpChanged.AddUObject(this, &UhealthBar::UpdateHP);
}

void UhealthBar::BindXp(UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	CurrentStatComp->OnXpChanged.AddUObject(this, &UhealthBar::UpdateXP);
}

void UhealthBar::UpdateHP()
{
	if (CurrentStatComp.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UPDATEHP"));

		UpdateGauge(CurrentStatComp->GetHpRatio());
		UE_LOG(LogTemp, Warning, TEXT("RATIO: %f"), CurrentStatComp->GetHpRatio());
	}
}
void UhealthBar::UpdateXP()
{
	if (CurrentStatComp.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UPDATEHP"));

		UpdateGauge(CurrentStatComp->GetXPRatio());
		UE_LOG(LogTemp, Warning, TEXT("RATIO: %f"), CurrentStatComp->GetXPRatio());
	}
}

void UhealthBar::UpdateGauge(float percent) {
	float finwidth = gaugeWidth * percent;

	FVector2D resizing = FVector2D(finwidth, GaugeSlot->GetSize().Y);

	GaugeSlot->SetSize(resizing);
}
