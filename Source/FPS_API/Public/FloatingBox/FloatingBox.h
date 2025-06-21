// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingBox.generated.h"

struct FBoxType;
struct FBoxObject;
UCLASS()
class FPS_API_API AFloatingBox : public AActor
{
	GENERATED_BODY()

public:
	AFloatingBox();
	void SetBoxData(const FBoxType& BoxType, const FBoxObject& BoxObject);

	
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	
private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> BoxMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	TObjectPtr<UMaterialInstance> BoxMaterial;

	UPROPERTY()
	int32 MaxHealth{};

	UPROPERTY()
	UMaterialInstanceDynamic* BoxMaterialDynamic;

	UPROPERTY(VisibleAnywhere, Category = "Box Data")
	FString Name{};

	UPROPERTY(VisibleAnywhere, Category = "Box Data")
	FColor Color{};
	
	UPROPERTY(VisibleAnywhere, Category = "Box Data")
	int32 Health{};

	UPROPERTY(VisibleAnywhere, Category = "Box Data")
	int32 Score{};

	UPROPERTY(VisibleAnywhere, Category = "Box Data")
	FString Type{};

	UPROPERTY(VisibleAnywhere, Category = "Box Data")
	FTransform Transform{};

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> ScoreWidgetComponent;

	UPROPERTY()
	TObjectPtr<class UBoxHealth> BoxHealthWidget;
	
};
