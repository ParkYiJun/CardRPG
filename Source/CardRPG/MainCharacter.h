// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FollowingDrone.h"
#include "MainCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class CARDRPG_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted);

	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	void LookUp(float Value);
	void Dodge();
	void Attack();
	void Rush();
	void WallSkill();
	void WallSkillOn();
	void RangeSkill();
	void Teleport();
	void Fast();
	void Mine();
	void Heal();
	void Shield();
	void GenerateXp();
	void ResetWalkSpeed();
	void DroneAttack();
	void Dead();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	


	FOnAttackEnd OnAttackEnd;
	FTimerHandle WaitHandle;
	FTimerHandle WaitHandleFast;
	FTimerHandle WaitHandleDrone;
	FTimerHandle WaidHandleDead;

	


private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* CastFrom;
public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* DroneLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* FireTornadoLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* IceSkillLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* TeleportLocation;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* MovingSkillLocation;

	UPROPERTY(VisibleAnywhere)
		class AFollowingDrone* FollowingDrone;

	UPROPERTY(EditDefaultsOnly)
		class UStatComponent* Stats;



private:

	UPROPERTY(VisibleAnywhere, Category = Pawn)
		bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = Pawn)
		bool IsSkillUsing = false;

	UPROPERTY()
		class UPlayerAnimInstance* AnimInstance;

	UPROPERTY()
		int32 AttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
		
	UPROPERTY()
	    class APlayerController* PC;

	UPROPERTY()
		FVector TelpoLoc;
	UPROPERTY()
		float WalkSpeed;




public:
	UPROPERTY()
		bool IsImmune=false;



public:


	UPROPERTY()
		float UpdownValue = 0;

	UPROPERTY()
		float LeftRightValue = 0;


	UPROPERTY(VisibleAnywhere, Category = Pawn)
		bool DontMove = false;

	UPROPERTY()
	bool DroneIsAttacking=false;

	UPROPERTY(VisibleAnywhere, Category= WidgetActive)
	bool TownAnimationVisible=false;


	UPROPERTY(VisibleAnywhere, Category = WidgetActive)
		bool TempleAnimationVisible = false;

	UPROPERTY(VisibleAnywhere, Category = WidgetActive)
		bool NestAnimationVisible = false;

	UPROPERTY()
		bool IsDead = false;



private:
	float Health = 0;
	float DHealth = 100;

private:
	void on_exit_game();

	class UAIPerceptionStimuliSourceComponent* stimulus;

	void setup_stimulus();


};
