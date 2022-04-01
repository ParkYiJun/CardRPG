// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlueRush.generated.h"

UCLASS()
class CARDRPG_API ABlueRush : public AActor
{
	GENERATED_BODY()
	class UBoxComponent* CollisionComp;
public:	
	// Sets default values for this actor's properties
	ABlueRush();

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;

	UPROPERTY()
		class UAudioComponent* AudioComponent;

	UPROPERTY()
		class AMainCharacter* MainCharacter;

	UPROPERTY()
		class USoundBase* EffectSound;
	
	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float Speed=1500.0f;

};
