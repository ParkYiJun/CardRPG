// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SliderSlots.generated.h"

DECLARE_DELEGATE_OneParam(FCustomValueChange, float);

UCLASS()
class CARDRPG_API USliderSlots : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

private:
	float SettingValue;
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Value;
	UPROPERTY(meta = (BindWidget))
		class UButton* BDown;
	UPROPERTY(meta = (BindWidget))
		class USlider* ValueSlider;
	UPROPERTY(meta = (BindWidget))
		class UButton* BUp;
	UPROPERTY(EditDefaultsOnly)
		class USoundMix* MasterSoundMixer;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Index;

private:
protected:
	UFUNCTION(BlueprintCallable)
		void OnButtonDown();
	UFUNCTION(BlueprintCallable)
		void OnButtonUp();
	UFUNCTION(BlueprintCallable)
		void OnValueChange(float volume);
public:
	UFUNCTION(BlueprintCallable)
		void SetVolume(float volume);
	FCustomValueChange ValueChangeEvent;
};
