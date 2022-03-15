// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CardDropActor.generated.h"

class UCurveFloat;

UCLASS()
class CARDRPG_API ACardDropActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Range)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = MagnetRange)
		class USphereComponent* SecCollisionComp;

	
public:	
	// Sets default values for this actor's properties
	ACardDropActor();

	UFUNCTION()
		void TimeLineProgress(float Value);

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;

	UPROPERTY()
		class AMainCharacter* MainCharacter;


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	UPROPERTY()
	UCurveFloat* CurveFloat;

	UPROPERTY()
	FVector StartLoc;

	UPROPERTY()
	FVector EndLoc;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void XPEarned();

};
