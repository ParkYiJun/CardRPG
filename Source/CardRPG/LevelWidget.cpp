// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/TextBlock.h"
#include "StatComponent.h"
#include "MainCharacter.h"

#define LOCTEXT_NAMESPACE "LevelUserWidget"
void ULevelWidget::NativeConstruct() {
	Super::NativeConstruct();

	class AMainCharacter* player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player) {
		BindLevel(player->Stats);
		UpdateLevel();
	}
}

void ULevelWidget::BindLevel(class UStatComponent* PStats)
{
	CurrentStatComp = PStats;
	CurrentStatComp->OnXpChanged.AddUObject(this, &ULevelWidget::UpdateLevel);
}

void ULevelWidget::UpdateLevel() {
	if (CurrentStatComp.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Update Level: %d"), CurrentStatComp->GetLevel());
		FString lvtext = FString::Printf(TEXT("%02d"), CurrentStatComp->GetLevel());
		LevelText->SetText(FText::FromString(lvtext));
	}
}

#undef LOCTEXT_NAMESPACE