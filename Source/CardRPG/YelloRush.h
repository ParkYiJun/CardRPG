// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YelloRush.generated.h"

UCLASS()
class CARDRPG_API AYelloRush : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = RushEnd)
		class UBoxComponent* CollisionComp;
	
public:	
	// Sets default values for this actor's properties
	AYelloRush();

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;


	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }

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

private:
	UPROPERTY()
	float Speed = 1500.0f;

};
