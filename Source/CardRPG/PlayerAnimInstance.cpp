// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MainCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animation/Phase_Atack_Montage.Phase_Atack_Montage'"));

	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<AMainCharacter>(Pawn);
		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();

			Vertical = Character->UpdownValue;
			Horizontal = Character->LeftRightValue;
		}
		else {
			UE_LOG(LogTemp,Warning,TEXT("NoCharacter"));
		}
	}

}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.0f);
}

void UPlayerAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage);
}

FName UPlayerAnimInstance::GetAttackMontageName(int32 SectionIndex)
{


	return FName(FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UPlayerAnimInstance::AnimNotify_AttackFire()
{
	UE_LOG(LogTemp, Log, TEXT("AnimNotifyHit"));
	OnAttackHit.Broadcast();

}
