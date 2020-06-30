#include "TargetSphere.h"
#include "FPSpheresProjectile.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "SphereManager.h"

// Sets default values
ATargetSphere::ATargetSphere()
    :SphereRadius(55.0f)
{
    // Use a sphere as a simple collision representation
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComp->InitSphereRadius(SphereRadius);
    CollisionComp->BodyInstance.SetCollisionProfileName("PhysicsActor");
    // Set up a notification for when this component hits something blocking
    CollisionComp->OnComponentHit.AddDynamic(this, &ATargetSphere::OnHit);

    // Players can't walk on it
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;

    // Set as root component
    RootComponent = CollisionComp;
}

void ATargetSphere::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
    // Only add impulse and destroy projectile if we hit a physics
    if ((OtherActor != NULL) && OtherActor->GetClass() == CharacterBulletClass)
    {
        // Get sphere manager object
        for (TActorIterator<ASphereManager> it(GetWorld()); it; ++it)
        {
            it->OnDestroySphere();
        }
        Destroy();
    }
}
