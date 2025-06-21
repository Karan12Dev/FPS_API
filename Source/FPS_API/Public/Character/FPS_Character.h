// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interface/ScoreInterface.h"
#include "FPS_Character.generated.h"

class UCameraComponent;
class AGun;
class UInputAction;

UCLASS()
class FPS_API_API AFPS_Character : public ACharacter, public IScoreInterface
{
	GENERATED_BODY()

public:
	AFPS_Character();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetScore(const int32 BoxScore) override;

	
protected:
	virtual void BeginPlay() override;


private:
	void AddInputMappingContext() const;
	void SpawnAndEquipWeapon();
	void AddWidgetToViewport();

	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> GunComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	TObjectPtr<AGun> Gun;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;
	void Move(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireAction;
	void Fire();

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	int32 Score{};

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class UScoreWidget> ScoreWidgetClass;

	UPROPERTY()
	TObjectPtr<UScoreWidget> ScoreWidget;
};
