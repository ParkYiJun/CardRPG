// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	void Attack();
	void DroneAttack();
	void AttackCheck();


	FOnAttackEnd OnAttackEnd;

	


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
	UPROPERTY()
		class AFollowingDrone* FollowingDrone;


private:

	UPROPERTY(VisibleAnywhere, Category = Pawn)
		bool IsAttacking = false;

	UPROPERTY()
		class UPlayerAnimInstance* AnimInstance;

	UPROPERTY()
		int32 AttackIndex = 0;


public:


	UPROPERTY()
		float UpdownValue = 0;

	UPROPERTY()
		float LeftRightValue = 0;

	UPROPERTY(VisibleAnywhere, Category = Pawn)
		bool DontMove = false;

};
