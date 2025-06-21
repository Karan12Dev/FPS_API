// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingBox/FloatingBox.h"
#include "FloatingBox/HTTPRequestTypes.h"
#include "Interface/ScoreInterface.h"
#include "Components/WidgetComponent.h"
#include "UI/BoxHealth.h"


AFloatingBox::AFloatingBox()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	SetRootComponent(BoxMesh);

	ScoreWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScoreWidget"));
	ScoreWidgetComponent->SetupAttachment(GetRootComponent());
}

void AFloatingBox::BeginPlay()
{
	Super::BeginPlay();
	BoxMaterialDynamic = UMaterialInstanceDynamic::Create(BoxMaterial, this);
	if (IsValid(BoxMaterial) && IsValid(BoxMaterialDynamic))
	{
		BoxMesh->SetMaterial(0, BoxMaterialDynamic);
	}
	if (IsValid(ScoreWidgetComponent->GetUserWidgetObject()))
	{
		BoxHealthWidget = Cast<UBoxHealth>(ScoreWidgetComponent->GetUserWidgetObject());
		if (IsValid(BoxHealthWidget))
		{
			BoxHealthWidget->SetVisibility(ESlateVisibility::Hidden);
			BoxHealthWidget->SetHealthBar(1, 1);
		}
	}
}

float AFloatingBox::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - DamageAmount, 0, MaxHealth);
	if (Health <= 0)
	{
		IScoreInterface* ScoreInterface = Cast<IScoreInterface>(DamageCauser->GetOwner());
		if (ScoreInterface)
		{
			ScoreInterface->SetScore(Score);
		}
		Destroy();
	}
	else if (IsValid(BoxHealthWidget))
	{
		BoxHealthWidget->SetVisibility(ESlateVisibility::Visible);
		BoxHealthWidget->SetHealthBar(Health, MaxHealth);
	}
	return DamageAmount;
}


void AFloatingBox::SetBoxData(const FBoxType& BoxType, const FBoxObject& BoxObject)
{
	Name = BoxType.name;
	Color = FColor(BoxType.color[0], BoxType.color[1], BoxType.color[2]);
	Health = BoxType.health;
	MaxHealth = Health;
	Score = BoxType.score;
	Type = BoxObject.type;
	Transform = FTransform(FRotator(BoxObject.transform.rotation[0], BoxObject.transform.rotation[1], BoxObject.transform.rotation[2]),
		FVector(BoxObject.transform.location[0], BoxObject.transform.location[1], BoxObject.transform.location[2]),
		FVector(BoxObject.transform.scale[0], BoxObject.transform.scale[1], BoxObject.transform.scale[2]));

	SetActorTransform(Transform);
	if (IsValid(BoxMaterialDynamic))
	{
		const FLinearColor NewColor = FColor(Color).ReinterpretAsLinear();
		BoxMaterialDynamic->SetVectorParameterValue("Color", NewColor);
	}
}

