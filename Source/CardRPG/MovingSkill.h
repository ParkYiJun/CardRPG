// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingSkill.generated.h"

UCLASS()
class CARDRPG_API AMovingSkill : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = RangeSkill)
		class UBoxComponent* CollisionComp;
	
public:	
	// Sets default values for this actor's properties
	AMovingSkill();

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;


	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }

public:
	UPROPERTY()
		class AMainCharacter* MainCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
