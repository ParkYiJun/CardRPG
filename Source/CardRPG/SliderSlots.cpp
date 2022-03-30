// Fill out your copyright notice in the Description page of Project Settings.


#include "SliderSlots.h"
#include "Sound/SoundMix.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Button.h"

void USliderSlots::NativeConstruct() {
	Super::NativeConstruct();
	
	ValueSlider->StepSize = 0.01f;
	BDown->OnClicked.AddDynamic(this, &USliderSlots::OnButtonDown);
	BUp->OnClicked.AddDynamic(this, &USliderSlots::OnButtonUp);
	ValueSlider->OnValueChanged.AddDynamic(this, &USliderSlots::OnValueChange);
	
	SettingValue = MasterSoundMixer->SoundClassEffects[Index].VolumeAdjuster;

	ValueChangeEvent.BindUFunction(this, FName("SetVolume"));
	ValueChangeEvent.ExecuteIfBound(SettingValue);
}

void USliderSlots::SetVolume(float volume)
{
	SettingValue = volume;
	MasterSoundMixer->SoundClassEffects[Index].VolumeAdjuster = SettingValue;
	
	ValueSlider->SetValue(SettingValue);

	FString valuetxt = FString::Printf(TEXT("%d"), FMath::FloorToInt(SettingValue * 100));
	Value->SetText(FText::FromString(valuetxt));
}

void USliderSlots::OnButtonDown() {
	if (SettingValue - 0.01f >= 0)
		ValueChangeEvent.ExecuteIfBound(SettingValue - 0.01f);
}

void USliderSlots::OnButtonUp() {
	if (SettingValue + 0.01f <= 1)
		ValueChangeEvent.ExecuteIfBound(SettingValue + 0.01f);
}

void USliderSlots::OnValueChange(float volume) {
	ValueChangeEvent.ExecuteIfBound(volume);
}