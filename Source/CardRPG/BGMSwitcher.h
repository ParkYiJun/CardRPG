// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardRPG.h"
#include "GameFramework/Actor.h"
#include "BGMSwitcher.generated.h"

UCLASS()
class CARDRPG_API ABGMSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGMSwitcher();
	UPROPERTY(EditInstanceOnly, Category = "BGMSwitcher")
		uint32 Situation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditInstanceOnly, Category = "BGMSwitcher")
		class UBoxComponent* TriggerBox;
	UPROPERTY(VisibleAnywhere, Category = "BGMSwitcher")
		class USoundCue*  Track;
	UPROPERTY(VisibleAnywhere, Category = "BGMSwitcher")
		class AAmbientSound* DisplayedAmbient;

	UFUNCTION()
		void SwitcherBeginOverlap(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	UFUNCTION(BlueprintCallable)
		void SetTargetAmbient(AAmbientSound * targetambient);
	
};
