#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereManager.generated.h"

UCLASS()
class FPSPHERES_API ASphereManager : public AActor
{
    GENERATED_BODY()

public:
    enum class ESphereManagerState
    {
        OnActive,
        OnGenerate,
    };

public:
    // Sets default values for this actor's properties
    ASphereManager();

    // Called every frame
    void Tick(float DeltaTime) override;

    // Generate new spheres wave
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        void GenerateSphere(UPARAM(ref) FVector& pos);

    void OnDestroySphere();

protected:
    // Called when the game starts or when spawned
    void BeginPlay() override;

private:
    // Check state
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        void CheckState();

    // Set state on generate spheres finished
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        void OnGenerateFinished();

    // Get Spawn Position
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        FVector GetPlayerPosition() const;

    // Get Current Max Radius
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        float GetCurrentMaxRadius() const;

    // Need generate sphere in while loop
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        bool IsNeedGenerateSphere() const;

    // Need generate new wave
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        bool IsNeedGenerateWave() const;

    // Get wave number
    UFUNCTION(BlueprintCallable, Category = "SphereManager")
        int GetWaveNum() const { return WaveNum; }

    // Generate sphere
    void OnGenerate(const FVector& pos);

    // Check distance for new pos
    bool CheckDistance(const FVector& pos) const;

    // Calculate distance between two points
    float GetDistanceBetweenPoints(const FVector& pointA, const FVector& pointB) const;

    // Is need generate new wave
    bool IsNewWave();

protected:
    // Sphere numbers to complete wave
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpheresManagerSettings)
        int CheckpointSpheresCount;

    // Max spheres numbers on the current wave
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpheresManagerSettings)
        int MaxSpheresCount;

    // Max spawn radius
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpheresManagerSettings)
        float MaxSpawnRadius;

    //  Max spawn radius to complete wave
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpheresManagerSettings)
        float HitSpawnRadius;

    // Min distance between spheres
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpheresManagerSettings)
        int DistanceBetweenSpheres;

    // Percentage radius increasing
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpheresManagerSettings)
        float RadiusIncreasePercents;
    
    // Percentage increase max number of spheres
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpheresManagerSettings)
        float MaxSpheresCountIncreasePercents;

    /** TargetSphere class to spawn spheres */
    UPROPERTY(EditDefaultsOnly, Category = SpheresManagerSettings)
        TSubclassOf<class ATargetSphere> TargetSphereClass;

private:
    int CurrentSpheresCount;

    ESphereManagerState State;

    int WaveNum;

};
