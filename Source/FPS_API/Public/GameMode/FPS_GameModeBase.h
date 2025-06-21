// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/IHttpRequest.h"
#include "FloatingBox/HTTPRequestTypes.h"
#include "FPS_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API_API AFPS_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


private:
	FTimerHandle BoxSpawnTimer;
	void BoxSpawnTimerFinished();

	UPROPERTY(EditDefaultsOnly, Category = "Box")
	float BoxSpawnTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Box")
	TSubclassOf<class AFloatingBox> FloatingBoxClass;

	UPROPERTY()
	AFloatingBox* FloatingBox;

	void FetchData();
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY()
	FBoxData BoxData{};
};
