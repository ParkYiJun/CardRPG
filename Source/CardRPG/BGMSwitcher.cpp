// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMSwitcher.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/AmbientSound.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "CardRPGGameModeBase.h"

// Sets default values
ABGMSwitcher::ABGMSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGERBOX"));
	TriggerBox->SetGenerateOverlapEvents(true);

	RootComponent = TriggerBox;
}

// Called when the game starts or when spawned
void ABGMSwitcher::BeginPlay()
{
	Super::BeginPlay();
	if (Situation > 0) {
		ACardRPGGameModeBase* gamemode = Cast<ACardRPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (gamemode != nullptr)
			Track = gamemode->GetSound(Situation);
	}
}

void ABGMSwitcher::SetTargetAmbient(AAmbientSound* targetambient) {
	DisplayedAmbient = targetambient;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABGMSwitcher::SwitcherBeginOverlap);
}

void ABGMSwitcher::SwitcherBeginOverlap(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* character = Cast<AMainCharacter>(otherActor);
	if (character != nullptr) {
		DisplayedAmbient->Stop();
		DisplayedAmbient->GetAudioComponent()->Sound = Cast<USoundBase>(Track);
		DisplayedAmbient->Play();
		Destroy();
	}
}
