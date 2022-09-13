
#include "GQ_3DShootingProjectile.h"
#include "ACTargetActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AGQ_3DShootingProjectile::AGQ_3DShootingProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AGQ_3DShootingProjectile::OnHit);		// set up a notification for when this component hits something blocking
	
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 8.0f;
}

void AGQ_3DShootingProjectile::BeginPlay()
{
	Super::BeginPlay();

	
	// find all AnyActors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAC_TargetHitEvent::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		AAC_TargetHitEvent* AnyActor = Cast<AAC_TargetHitEvent>(Actor);
		if (AnyActor)
		{
			AC_TargetHitEvent = AnyActor;
		}
	}
}



void AGQ_3DShootingProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AACTargetActor* pTarget = Cast<AACTargetActor>(OtherActor);
		if (pTarget != nullptr)
		{		
			if (pTarget->HitEvent())
			{
				// イベントディスパッチャ
				AC_TargetHitEvent->HitFunc();

				Destroy();
			}
		}

	}
}