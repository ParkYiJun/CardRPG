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
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Attack %d"), GetStatData(1)->Attack);
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Health %d"), GetStatData(1)->MaxHp);
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance Defence %d"), GetStatData(1)->Defence);

}

FMyCharacterData* UCardRPGGameInstance::GetStatData(int32 Level)
{
	return MyStats->FindRow<FMyCharacterData>(*FString::FromInt(Level), TEXT(""));

}
