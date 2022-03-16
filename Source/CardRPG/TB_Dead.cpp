// Fill out your copyright notice in the Description page of Project Settings.


#include "TB_Dead.h"
#include "MainCharacter.h"
#include "InGameHud.h"
#include "Kismet/GameplayStatics.h"

void ATB_Dead::BeginPlay()
{
	Super::BeginPlay();

	InGameHud = Cast<AInGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

ATB_Dead::ATB_Dead()
{
	OnActorBeginOverlap.AddDynamic(this, &ATB_Dead::OnOverlapBegin);
}

void ATB_Dead::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OverlappedActor==MainCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("ON"));
		UGameplayStatics::ApplyDamage(MainCharacter, 500.0f, NULL, GetOwner(), NULL);
		InGameHud->UpdateWidgetVisibilityDead();
		InGameHud->PlayAnimationByNameDead();
	}


}
