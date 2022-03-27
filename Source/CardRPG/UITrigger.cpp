// Fill out your copyright notice in the Description page of Project Settings.


#include "UITrigger.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

// Sets default values
AUITrigger::AUITrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetGenerateOverlapEvents(true);

	RootComponent = TriggerBox;
}

// Called when the game starts or when spawned
void AUITrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUITrigger::UILoaderBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUITrigger::UILoaderEndOverlap);
}

void AUITrigger::UILoaderBeginOverlap(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* character = Cast<AMainCharacter>(otherActor);
	if (character != nullptr) {
		APlayerController* PController = Cast<APlayerController>(character->GetController());
		if (PController != nullptr) {
			if (TutorialUI == nullptr) {
				TutorialUI = CreateWidget(PController, Widget);	
			}
			TutorialUI->AddToViewport();
		}
	}
}

void AUITrigger::UILoaderEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (TutorialUI != nullptr) {
		TutorialUI->RemoveFromParent();
	}
}
