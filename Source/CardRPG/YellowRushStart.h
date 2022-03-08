// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YellowRushStart.generated.h"

UCLASS()
class CARDRPG_API AYellowRushStart : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = RushStart)
		class UBoxComponent* CollisionComp;
	
public:	
	// Sets default values for this actor's properties
	AYellowRushStart();

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;


	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
		class AMainCharacter* MainCharacter;


private:
	UPROPERTY()
	float Speed = 1500.0f;

};
