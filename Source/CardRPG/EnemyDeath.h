// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealSkill.generated.h"

UCLASS()
class CARDRPG_API AHealSkill : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Heal)
		class UBoxComponent* CollisionComp;
public:	
	// Sets default values for this actor's properties
	AHealSkill();

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;

	UPROPERTY()
		class UAudioComponent* AudioComponent;

	UPROPERTY()
		class USoundBase* EffectSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
