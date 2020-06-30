#include "SphereManager.h"
#include "FPSpheresCharacter.h"
#include "TargetSphere.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
ASphereManager::ASphereManager()
    : CheckpointSpheresCount(10)
    , MaxSpheresCount(15)
    , MaxSpawnRadius(2000)
    , HitSpawnRadius(1500)
    , DistanceBetweenSpheres(80)
    , CurrentSpheresCount(0)
    , RadiusIncreasePercents(5)
    , MaxSpheresCountIncreasePercents(10)
    , State(ESphereManagerState::OnGenerate)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASphereManager::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASphereManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASphereManager::GenerateSphere(UPARAM(ref)FVector & pos)
{
    // Before generate we should check distance
    if (CheckDistance(pos))
    {
        // Generate sphere
        OnGenerate(pos);
        ++CurrentSpheresCount;
    }
}

void ASphereManager::OnDestroySphere()
{
    --CurrentSpheresCount;
}

void ASphereManager::CheckState()
{
    if (IsNewWave())
    {
        CurrentSpheresCount = 0; // Reset count of generated spheres
        MaxSpawnRadius += MaxSpawnRadius * (RadiusIncreasePercents / 100.0f);
        MaxSpheresCount += MaxSpheresCount * (MaxSpheresCountIncreasePercents / 100.0f);
        State = ESphereManagerState::OnGenerate;
    }
}

void ASphereManager::OnGenerate(const FVector & pos)
{
    // Try and generate target sphere
    if (TargetSphereClass != NULL)
    {
        UWorld* const World = GetWorld();
        if (World != NULL)
        {
            FRotator SpawnRotation = FRotator(0, 0, 0);
            FVector SpawnLocation = pos;

            // Set Spawn Collision Handling Override
            FActorSpawnParameters ActorSpawnParams;
            ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

            // spawn the projectile at the muzzle
            World->SpawnActor<ATargetSphere>(TargetSphereClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
        }
    }
}

void ASphereManager::OnGenerateFinished()
{
    ++WaveNum;
    State = ESphereManagerState::OnActive;
}

bool ASphereManager::CheckDistance(const FVector& pos) const
{
    // Get all target-actors
    for (TActorIterator<ATargetSphere> it(GetWorld()); it; ++it)
    {
        const FVector actorPos = it->GetActorLocation();
        // Spheres radius also has to participate in calculation
        if (GetDistanceBetweenPoints(actorPos, pos) <= DistanceBetweenSpheres + it->GetRadius())
        {
            return false;
        }
    }
    return true;
}

float ASphereManager::GetDistanceBetweenPoints(const FVector& pointA, const FVector& pointB) const
{
    return sqrt(pow(pointB.X - pointA.X, 2) + pow(pointB.Y - pointA.Y, 2) + pow(pointB.Z - pointA.Z, 2));
}

FVector ASphereManager::GetPlayerPosition() const
{
    // Get first player pawn location
    for (TActorIterator<AFPSpheresCharacter> it(GetWorld()); it; ++it)
    {
        return it->GetActorLocation();
    }
    return FVector(0, 0, 0);
}

float ASphereManager::GetCurrentMaxRadius() const
{
    // If we have at least 10 spheres in 1500 radius, then max radius can be 2000
    return CurrentSpheresCount > CheckpointSpheresCount ? MaxSpawnRadius : HitSpawnRadius;
}

bool ASphereManager::IsNeedGenerateSphere() const
{
    return CurrentSpheresCount < MaxSpheresCount;
}

bool ASphereManager::IsNeedGenerateWave() const
{
    return State == ESphereManagerState::OnGenerate;
}

bool ASphereManager::IsNewWave()
{
    return State == ESphereManagerState::OnActive && (MaxSpheresCount - CurrentSpheresCount >= CheckpointSpheresCount);
}
