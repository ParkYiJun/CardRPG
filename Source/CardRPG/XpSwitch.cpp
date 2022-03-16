// Fill out your copyright notice in the Description page of Project Settings.


#include "XpSwitch.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AXpSwitch::AXpSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent=CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent=_RootComponent;

	LightSwitch=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light switch mesh"));

	LightSwitch->SetupAttachment(RootComponent);

	Light=CreateDefaultSubobject<UPointLightComponent>(TEXT("Light bulb"));
	Light->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AXpSwitch::BeginPlay()
{
	Super::BeginPlay();
	Light->SetIntensity(0);
	InteractionWidget->SetVisibility(false);
	
}

// Called every frame
void AXpSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXpSwitch::InteractWithMe()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted ON"));
	if (bIsOn)
	{
		Light->SetIntensity(0);
		bIsOn=false;
	}
	else
	{
		Light->SetIntensity(10000);
		bIsOn=true;
	}

}

void AXpSwitch::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void AXpSwitch::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

