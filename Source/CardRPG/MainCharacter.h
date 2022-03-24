// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FollowingDrone.h"
#include "Sound/SoundBase.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* right_fist_collision_box;

	virtual void PostInitializeComponents() override;

	float get_health() const;
	float get_max_health() const;
	void set_health(float const new_health);


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
	void UseSkill();
	void UseSkill_R();
	void BlueRush();
	void Rush();
	void WallSkill();
	void WallSkillOn();
	void RangeSkill();
	void Teleport();
	void Fast();
	void Mine();
	void Heal();
	void Shield();
	void ElectoronicShock();
	void ElectoronicShockOn();
	void GenerateXp();
	void ResetWalkSpeed();
	void DroneAttack();
	void IceExplosion();
	void Dead();
	void OnInteract();


public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	float GetXP(float XpAmount);

	FOnAttackEnd OnAttackEnd;
	FTimerHandle WaitHandle;
	FTimerHandle WaitHandleFast;
	FTimerHandle WaitHandleDrone;
	FTimerHandle WaidHandleDead;

	int32 SkillCode;


private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;
public:
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
	UPROPERTY(EditAnywhere)
		class UBoxComponent* InteractionBox;

	class IInteractionInterface* Interface = nullptr;

	//UFUNCTION()
	//void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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

	UPROPERTY()
		class AInGameHud* InGameHud;




public:
	UPROPERTY()
		bool IsImmune=false;

	UPROPERTY()
		class UAudioComponent* AudioComponent;

	UPROPERTY()
		class USoundBase* AttackedSound;

	UPROPERTY()
		class USoundBase* FireReadySound;

	UPROPERTY()
		class USoundBase* RollSound;



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
	class UWidgetComponent* widget_component;
	float const max_health = 100.0f;
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* distraction_sound;   

	void on_exit_game();

	class UAIPerceptionStimuliSourceComponent* stimulus;

	void setup_stimulus();

	void on_attack();
	void on_distract();

	UFUNCTION()
	void on_attack_overlap_begin(
		UPrimitiveComponent* const overlapped_component,
		AActor* const other_actor,
		UPrimitiveComponent* other_component,
		int const other_body_index,
		bool const from_sweep,
		FHitResult const& sweep_result);

	UFUNCTION()
	void on_attack_overlap_end(
		UPrimitiveComponent* const overlapped_component,
		AActor* const other_actor,
		UPrimitiveComponent* other_component,
		int const other_body_index);

};
