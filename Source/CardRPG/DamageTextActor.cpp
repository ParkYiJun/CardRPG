// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextActor.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADamageTextActor::ADamageTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	DamageTextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageTextWidget"));
	DamageTextWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADamageTextActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

