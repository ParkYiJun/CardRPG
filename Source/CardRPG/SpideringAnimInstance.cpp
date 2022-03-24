// Fill out your copyright notice in the Description page of Project Settings.


#include "SpideringAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Spidering.h"

USpideringAnimInstance::USpideringAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>DM(TEXT("AnimMontage'/Game/InfinityBladeAdversaries/AI/Animation/Spidering/Spidering_Death.Spidering_Death'"));
	if (DM.Succeeded())
	{
		DeadMontage = DM.Object;
	}

}

void USpideringAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		auto spidering = Cast<ASpidering>(Pawn);

	}

}

void USpideringAnimInstance::PlayDeadMontage()
{
	if (!Montage_IsPlaying(DeadMontage))
	{
		Montage_Play(DeadMontage, 1.0f);
	}

}



