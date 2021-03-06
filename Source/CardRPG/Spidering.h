// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "CardRPG_CharacterBase.h"
#include "Spidering.generated.h"

UCLASS()
class CARDRPG_API ASpidering : public ACardRPG_CharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties

	ASpidering();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void melee_attack();

	void Dead();

	UAnimMontage* get_montage() const;

	UPROPERTY(EditDefaultsOnly)
		class UStatComponent* Stats;

	UPROPERTY()
		bool IsDead = false;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY()
	class UWidgetComponent* widget_component;

	UPROPERTY()
		class USpideringAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* montage;

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

	UPROPERTY()
		class AInGameHud* InGameHud;

	FTimerHandle HpVisibleHandle;
	bool BarVisible=true;
public:
	FTimerHandle WaidHandleDead;
};
