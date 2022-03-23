// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceSkill.generated.h"

UCLASS()
class CARDRPG_API AIceSkill : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = RangeSkill)
		class UBoxComponent* CollisionComp;
	
public:	
	// Sets default values for this actor's properties
	AIceSkill();


	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;

	UPROPERTY()
		class UAudioComponent* AudioComponent;

	UPROPERTY()
		class USoundBase* EffectSound;


	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
