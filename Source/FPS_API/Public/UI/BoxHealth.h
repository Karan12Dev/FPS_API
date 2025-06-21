// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxHealth.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API_API UBoxHealth : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HealthBar;


public:
	void SetHealthBar(const float CurrentHealth, const float MaxHealth) const;
};
