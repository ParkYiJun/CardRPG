// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UITrigger.generated.h"

UCLASS()
class CARDRPG_API AUITrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUITrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditInstanceOnly, Category = "UITrigger")
		class UBoxComponent* TriggerBox;
	UPROPERTY(EditInstanceOnly, Category = "UITrigger")
		TSubclassOf<UUserWidget> Widget;
	UPROPERTY()
		UUserWidget* TutorialUI;

public:
	UFUNCTION()
		void UILoaderBeginOverlap(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void UILoaderEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
