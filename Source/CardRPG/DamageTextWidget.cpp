// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextWidget.h"
#include "MainCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StatComponent.h"
#include "UObject/UnrealType.h"
#include "Internationalization/Text.h"

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Damage=MainCharacter->Stats->GetAttack(); 

	DamageText=(UTextBlock*)GetWidgetFromName(TEXT("DamageText"));
	DamageText->SetText(FText::AsNumber(Damage));
	PlayAnimation(DamageAnimation);
	UE_LOG(LogTemp,Warning,TEXT("WidgetON"));
}
