// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextActor.h"
#include "Components/SceneComponent.h"
#include "DamageTextWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADamageTextActor::ADamageTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = _RootComponent;

	MyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageTextWidget"));
	MyWidget->SetupAttachment(RootComponent);
	static ConstructorHelpers::FClassFinder<UUserWidget>DW(TEXT("WidgetBlueprint'/Game/UI/WBP_FloatingDamageText.WBP_FloatingDamageText_C'"));
	if (DW.Succeeded())
	{
	MyWidget->SetWidgetClass(DW.Class);
	MyWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}


	InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void ADamageTextActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ActorOn"));
	
}

// Called every frame
void ADamageTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

