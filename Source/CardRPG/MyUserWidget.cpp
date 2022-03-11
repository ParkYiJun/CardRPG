// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "StatComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"

void UMyUserWidget::NativeConstruct() {
	GaugeSlot = Cast<UCanvasPanelSlot>(Gauge->Slot);
	if (GaugeSlot) {
		gaugeWidth = GaugeSlot->GetSize().X;
		UE_LOG(LogTemp, Warning, TEXT("Width: %f"), gaugeWidth);
	}
	
	UpdateHP();
}

void UMyUserWidget::BindHp(class UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	//StatComp->OnHpChanged.AddUObject(this, &UMyUserWidget::UpdateHP);
}

void UMyUserWidget::UpdateHP()
{UpdateGauge(0.8f);
	if (CurrentStatComp.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UPDATEHP"));
		
		//PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
		UE_LOG(LogTemp, Warning, TEXT("RATIO: %f"), CurrentStatComp->GetHpRatio());
	}
}

void UMyUserWidget::UpdateGauge(float percent) {
	float finwidth = gaugeWidth * percent;

	FVector2D resizing = FVector2D( finwidth, GaugeSlot->GetSize().Y);

	GaugeSlot->SetSize(resizing);
}
