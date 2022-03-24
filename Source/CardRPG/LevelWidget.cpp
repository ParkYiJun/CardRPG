// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelWidget.h"
#include "Kismet/GamePlayStatics.h"
#include "StatComponent.h"
#include "MainCharacter.h"

void ULevelWidget::NativeConstruct() {
	Super::NativeConstruct();

	class AMainCharacter* player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player) {
//		BindLevel(player->Stats);
	}
}

//void ULevelWidget::BindLevel(UStatComponent* PStats)
//{
//	CurrentStatComp = PStats;
//	CurrentStatComp->OnXpChanged.AddUObject(this, &ULevelWidget::UpdateLevel);
//}

void ULevelWidget::UpdateLevel() {
	if (CurrentStatComp.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Update Level: %d"), CurrentStatComp->GetLevel());
	}
}