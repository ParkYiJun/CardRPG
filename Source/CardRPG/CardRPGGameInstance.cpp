// Fill out your copyright notice in the Description page of Project Settings.


#include "CardRPGGameInstance.h"

UCardRPGGameInstance::UCardRPGGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/Data/DT_StatTable.DT_StatTable'"));

	if (DATA.Succeeded())
	{
		MyStats = DATA.Object;
	}

}

void UCardRPGGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp,Warning,TEXT("HP : %d"),GetStatData(2)->MaxHp);
}

FMyCharacterData* UCardRPGGameInstance::GetStatData(int32 Level)
{
	return MyStats->FindRow<FMyCharacterData>(*FString::FromInt(Level), TEXT(""));

}
