// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "XpSwitch.generated.h"

UCLASS()
class CARDRPG_API AXpSwitch : public AActor , public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXpSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithMe() override;

	virtual void ShowInteractionWidget() override;

	virtual void HideInteractionWidget() override;

private:

	UPROPERTY(EditAnywhere)
	class USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LightSwitch;

	UPROPERTY(EditAnywhere)
	class UPointLightComponent* Light;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* InteractionWidget;

	bool bIsOn=true;
};
