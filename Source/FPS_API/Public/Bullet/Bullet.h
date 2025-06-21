// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class FPS_API_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	ABullet();

	
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BulletMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float BulletLife = 2.5;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> BoxComp;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit);
};
