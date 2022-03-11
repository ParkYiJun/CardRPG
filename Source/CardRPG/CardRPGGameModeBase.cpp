// Copyright Epic Games, Inc. All Rights Reserved.


#include "CardRPGGameModeBase.h"
#include "MainCharacter.h"


ACardRPGGameModeBase::ACardRPGGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter>BP_Char(TEXT("Blueprint'/Game/BluePrints/BP_MainCharacter.BP_MainCharacter_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}
}

int32 ACardRPGGameModeBase::FindCard(FName name) {
	return CardNames.Find(name);
}

FName ACardRPGGameModeBase::CardAt(int32 idx) {
	if (CardNames.IsValidIndex(idx)) {
		return CardNames[idx];
	}
	else {
		return FName::FName(TEXT("NONE"));
	}
}