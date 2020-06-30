#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSphere.generated.h"

UCLASS()
class FPSPHERES_API ATargetSphere : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATargetSphere();

    /** called when projectile hits something */
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    float GetRadius() const { return SphereRadius; }

public:
    /** Sphere collision component */
    UPROPERTY(EditDefaultsOnly, Category = SpheresSettings)
        class USphereComponent* CollisionComp;

    /**Bullet class to check collision */
    UPROPERTY(EditDefaultsOnly, Category = SpheresManagerSettings)
        TSubclassOf<class AFPSpheresProjectile> CharacterBulletClass;

protected:
    // Sphere radius
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SphereSettings)
        float SphereRadius;
};
