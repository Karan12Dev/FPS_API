// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/Bullet.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
	BulletMesh->SetupAttachment(BoxComp);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	Projectile->InitialSpeed = 3000.f;
	Projectile->MaxSpeed = 4000.f;
	Projectile->ProjectileGravityScale = 0.1f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(BulletLife);
	BoxComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(Hit.GetActor(), 1.f, GetInstigator()->GetController(), this, UDamageType::StaticClass());
	Destroy();
}

