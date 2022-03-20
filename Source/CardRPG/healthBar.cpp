// Fill out your copyright notice in the Description page of Project Settings.


#include "healthBar.h"

void UhealthBar::set_bar_value_percent(float const value)
{
	health_value->SetPercent(value);
}
