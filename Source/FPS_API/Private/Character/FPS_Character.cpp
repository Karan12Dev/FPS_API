// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPS_Character.h"
#include "Gun/Gun.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/ScoreWidget.h"
#include "Kismet/GameplayStatics.h"


AFPS_Character::AFPS_Character()
{
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	GunComp = CreateDefaultSubobject<USceneComponent>("Gun Location");
	GunComp->SetupAttachment(GetRootComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();
	AddInputMappingContext();
	SpawnAndEquipWeapon();
	AddWidgetToViewport();
}

void AFPS_Character::AddInputMappingContext() const
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AFPS_Character::SpawnAndEquipWeapon()
{
	if (UWorld* World = GetWorld(); IsValid(World) && IsValid(GunClass))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		Gun = World->SpawnActor<AGun>(GunClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if (IsValid(Gun))
		{
			Gun->AttachToComponent(GunComp, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void AFPS_Character::AddWidgetToViewport()
{
	if (!IsValid(ScoreWidgetClass)) return;
	ScoreWidget = CreateWidget<UScoreWidget>(GetWorld()->GetFirstPlayerController(), ScoreWidgetClass);
	if (IsValid(ScoreWidget))
	{
		ScoreWidget->AddToViewport();
	}
}

void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent); IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPS_Character::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPS_Character::Look);
		EnhancedInput->BindAction(FireAction, ETriggerEvent::Started, this, &AFPS_Character::Fire);
	}
}

void AFPS_Character::Move(const FInputActionValue& Value)
{
	const FVector2D MoveAxis = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveAxis.Y);
	AddMovementInput(GetActorRightVector(), MoveAxis.X);
}

void AFPS_Character::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxis.Y);
	AddControllerYawInput(LookAxis.X);
}

void AFPS_Character::Fire()
{
	if (!IsValid(Gun)) return;
	
	FVector2D ViewportSize{};
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	const FVector2D ScreenCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector ScreenWorldPosition;
	FVector ScreenWorldDirection;
	const bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0), ScreenCenter, ScreenWorldPosition, ScreenWorldDirection);
	if (bScreenToWorld)
	{
		const FVector Start = ScreenWorldPosition;
		const FVector End = Start + ScreenWorldDirection * 4000.f;
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility);
		if (!Hit.bBlockingHit)
		{
			Hit.ImpactPoint = End;
		}
		Gun->StartFire(Hit.ImpactPoint);
	}
}

void AFPS_Character::SetScore(const int32 BoxScore)
{
	Score += BoxScore;
	if (IsValid(ScoreWidget))
	{
		ScoreWidget->SetScore(Score);
	}
}
