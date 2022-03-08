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
	static ConstructorHelpers::FObjectFinder<UAnimMontage> WM(TEXT("AnimMontage'/Game/Animation/Phase_WallSkill_Montage.Phase_WallSkill_Montage'"));
	if (WM.Succeeded())
	{
		WallSkillMontage=WM.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>RM(TEXT("AnimMontage'/Game/Animation/RushMontage.RushMontage'"));
	if(RM.Succeeded())
	{
	    RushSkillMontage=RM.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGF(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_Forward_Montage.YinA_SW_Roll_Forward_Montage'"));
	if(DGF.Succeeded()){ADGF=DGF.Object;}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGB(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_Backward_Montage.YinA_SW_Roll_Backward_Montage'"));
	if(DGB.Succeeded()){ADGB=DGB.Object;}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGL(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_Left_Montage.YinA_SW_Roll_Left_Montage'"));
	if(DGL.Succeeded()){ADGL=DGL.Object;}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGR(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_Right_Montage.YinA_SW_Roll_Right_Montage'"));
	if(DGR.Succeeded()){ADGR=DGR.Object;}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGLB(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_BackwardLeft_Montage.YinA_SW_Roll_BackwardLeft_Montage'"));
	if(DGLB.Succeeded()){ADGLB=DGLB.Object;}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGRB(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_BackwardRight_Montage.YinA_SW_Roll_BackwardRight_Montage'"));
	if(DGRB.Succeeded()){ADGRB=DGRB.Object;}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGLF(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_ForwardLeft_Montage.YinA_SW_Roll_ForwardLeft_Montage'"));
	if(DGLF.Succeeded()){ADGLF=DGLF.Object;}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DGRF(TEXT("AnimMontage'/Game/Animation/Dodge/YinA_SW_Roll_ForwardRight_Montage.YinA_SW_Roll_ForwardRight_Montage'"));
	if(DGRF.Succeeded()){ADGRF=DGRF.Object;}
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
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage,1.0f);
	}
}

void UPlayerAnimInstance::PlayWallSkillMontage()
{
	if (!Montage_IsPlaying(WallSkillMontage))
	{
		Montage_Play(WallSkillMontage, 1.0f);
	}

}
void UPlayerAnimInstance::PlayRushSkillMontage()
{
    if(!Montage_IsPlaying(RushSkillMontage))
    {
        Montage_Play(RushSkillMontage,1.0f);
    }
}

void UPlayerAnimInstance::PlayDodgeMontage()
{
    if(Vertical==1 && Horizontal==0)
    {
        DodgeMontage= ADGF;
    }
    else if(Vertical ==-1 && Horizontal ==0)
    {
         DodgeMontage= ADGB;
    }
    else if(Vertical ==0 && Horizontal ==-1)
    {
        DodgeMontage= ADGL;
    }
    else if(Vertical ==0 && Horizontal ==1)
    {
        DodgeMontage= ADGR;
    }
    else if(Vertical ==1 && Horizontal ==-1)
    {
         DodgeMontage= ADGLF;
    }
    else if(Vertical ==1 && Horizontal ==1)
    {
        DodgeMontage= ADGRF;
    }
    else if(Vertical ==-1 && Horizontal ==-1)
    {
        DodgeMontage= ADGLB;
    }
    else if(Vertical ==-1 && Horizontal ==1)
    {
        DodgeMontage= ADGRB;
    }
    
    if(!Montage_IsPlaying(DodgeMontage))
    {
        Montage_Play(DodgeMontage,1.2f);
    }
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
