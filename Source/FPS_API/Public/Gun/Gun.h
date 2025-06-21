// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class FPS_API_API AGun : public AActor
{
	GENERATED_BODY()

public:
	AGun();
	void StartFire(const FVector& HitTarget);

	
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> GunMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> BulletComp;

	UPROPERTY()
	UWorld* World;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABullet> BulletClass;
	
};
