// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "Spidering.generated.h"

UCLASS()
class CARDRPG_API ASpidering : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpidering();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*/UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int melee_attack();*/

	int melee_attack_Implementation() override;

	UAnimMontage* get_montage() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* montage;

};
