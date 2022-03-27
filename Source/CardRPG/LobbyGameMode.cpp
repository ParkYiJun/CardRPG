// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ALobbyGameMode::ALobbyGameMode()
{
	IntroBGMPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	IntroBGMPlayer->bAutoActivate = true;
}

void ALobbyGameMode::BeginPlay()
{
	ChangeFullWidget(TitleWidget);
	PlaySound(TitleBGM);
}

void ALobbyGameMode::ChangeFullWidget(TSubclassOf<UUserWidget> targetUI)
{
	if (CurrentUI != nullptr) {
		CurrentUI->RemoveFromParent();
	}

	CurrentUI = CreateWidget(GetWorld(), targetUI);
	CurrentUI->AddToViewport();
}

void ALobbyGameMode::PlaySound(class USoundBase* targetSCue)
{
	if (IntroBGMPlayer->IsPlaying())
		IntroBGMPlayer->Stop();

	IntroBGMPlayer->Sound = targetSCue;
	IntroBGMPlayer->Play();
}

void ALobbyGameMode::GotoLobby()
{
	ChangeFullWidget(LobbyWidget);
	PlaySound(LobbyBGM);
}

void ALobbyGameMode::GotoMainLevel()
{
	UGameplayStatics::OpenLevel(this, TEXT("Level_ForgottenRelic"));
}

