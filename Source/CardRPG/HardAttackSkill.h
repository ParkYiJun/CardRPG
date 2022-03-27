// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HardAttackSkill.generated.h"

UCLASS()
class CARDRPG_API AHardAttackSkill : public AActor
{
GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = HardSkill)
		class UBoxComponent* CollisionComp;

		UPROPERTY(VisibleAnywhere, Category = HardSkill)
		class UBoxComponent* SecondCollisionComp;

public:
	// Sets default values for this actor's properties
	AHardAttackSkill();

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

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY()
		class AMainCharacter* MainCharacter;

	UPROPERTY()
		class AActor* GetOtherActor;

private:
	bool IsOverlapped = false;

	FTimerHandle WaitHandle;
};
