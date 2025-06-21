// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun/Gun.h"
#include "Bullet/Bullet.h"


AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>("Gun Mesh");
	SetRootComponent(GunMesh);
	GunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BulletComp = CreateDefaultSubobject<USceneComponent>("Bullet Comp");
	BulletComp->SetupAttachment(GunMesh);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::StartFire(const FVector& HitTarget)
{
	World = World == nullptr ? GetWorld() : World;
	if (IsValid(World))
	{
		APawn* const InstigatorPawn = Cast<APawn>(GetOwner());
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = InstigatorPawn;
		const FVector ToTarget = HitTarget - BulletComp->GetComponentLocation();
		World->SpawnActor<ABullet>(BulletClass, BulletComp->GetComponentLocation(), ToTarget.Rotation(), SpawnParams);
	}
}
