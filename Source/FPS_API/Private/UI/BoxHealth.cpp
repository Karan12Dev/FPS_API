// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BoxHealth.h"
#include "Components/ProgressBar.h"


void UBoxHealth::SetHealthBar(const float CurrentHealth, const float MaxHealth) const
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}
