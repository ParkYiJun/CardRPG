// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "StatComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

void UMyUserWidget::NativeConstruct() {
	GaugeSlot = Cast<UCanvasPanelSlot>(Gauge->Slot);
	if (GaugeSlot) {
		gaugeWidth = GaugeSlot->GetSize().X;
		UE_LOG(LogTemp, Warning, TEXT("Width: %f"), gaugeWidth);
	}

	class APlayerController* P_Controller = GetOwningPlayer();
	if (P_Controller) {
		class AMainCharacter* player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player) {
			BindHp(player->Stats);
		}
	}
	UpdateHP();
}

void UMyUserWidget::BindHp(UStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	CurrentStatComp->OnHpChanged.AddUObject(this, &UMyUserWidget::UpdateHP);
}

void UMyUserWidget::UpdateHP()
{
	if (CurrentStatComp.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UPDATEHP"));
		
		UpdateGauge(CurrentStatComp->GetHpRatio());
		UE_LOG(LogTemp, Warning, TEXT("RATIO: %f"), CurrentStatComp->GetHpRatio());
	}
}

void UMyUserWidget::UpdateGauge(float percent) {
	float finwidth = gaugeWidth * percent;

	FVector2D resizing = FVector2D( finwidth, GaugeSlot->GetSize().Y);

	GaugeSlot->SetSize(resizing);
}
