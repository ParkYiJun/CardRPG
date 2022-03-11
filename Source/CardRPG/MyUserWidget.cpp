// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "StatComponent.h"
#include "Components/ProgressBar.h"

void UMyUserWidget::BindHp(class UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this, &UMyUserWidget::UpdateHP);
}

void UMyUserWidget::UpdateHP()
{
	if (CurrentStatComp.IsValid())
	{
		//UE_LOG(LogTemp, Warning, TEXT("UPDATEHP"));
		PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
		UE_LOG(LogTemp, Warning, TEXT("RATIO: %f"), CurrentStatComp->GetHpRatio());
	}
}
