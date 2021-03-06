// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "CardRPGGameInstance.generated.h"

/**
 * 
 */
 USTRUCT()
	 struct FMyCharacterData : public FTableRowBase
 {
	 GENERATED_BODY()

 public:
	

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Data)
	 int32 Level;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	 int32 Attack;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	 int32 MaxHp;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	 int32 Defence;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	 int32 RecoveryHp;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	 int32 DropXp;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	 int32 XpNeeded;
 };




UCLASS()
class CARDRPG_API UCardRPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCardRPGGameInstance();

	virtual void Init() override;

	FMyCharacterData* GetStatData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* MyStats;


	
};
