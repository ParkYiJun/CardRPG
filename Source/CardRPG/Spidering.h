// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Spidering.generated.h"

UCLASS()
class CARDRPG_API ASpidering : public ACharacter
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

	void melee_attack();

	UAnimMontage* get_montage() const;

	float get_health() const;
	float get_max_health() const;
	void set_health(float const new_health);

private:
	class UWidgetComponent* widget_component;
	float const max_health = 100;
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* montage;

};
