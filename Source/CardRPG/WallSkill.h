// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallSkill.generated.h"

UCLASS()
class CARDRPG_API AWallSkill : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Wall)
		class UBoxComponent* CollisionComp;
public:	
	// Sets default values for this actor's properties
	AWallSkill();

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;

	UPROPERTY()
		class AMainCharacter* MainCharacter;

	UPROPERTY()
		class AActor* GetOtherActor;
	UPROPERTY(VisibleAnywhere)
		class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* EffectSound;


	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	bool IsOverlapped=false;

	FTimerHandle WaitHandle;

	int32 Damage;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
