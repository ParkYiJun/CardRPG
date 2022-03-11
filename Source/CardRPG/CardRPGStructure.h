// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CardRPGStructure.generated.h"

UCLASS()
class CARDRPG_API ACardRPGStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardRPGStructure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(Atomic, BlueprintType)
struct FCard : public FTableRowBase
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Detail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Image;
};