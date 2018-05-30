// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingComponent.h"
#include "PressurePlatform.generated.h"

UCLASS()
class APressurePlatform : public AActor
{
	GENERATED_BODY()

	void InitPlatfomMovementLimits();
	MCEndPositionEnum ButtonPosition = MCEndPositionEnum::MC_Start;
	
public:	
	// Sets default values for this actor's properties
	APressurePlatform();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USceneComponent* SceneRoot = nullptr;
	class UMovingComponent* MC = nullptr;

	UPROPERTY(EditAnywhere, Category = "Platforms")
	TArray<class AMovingPlatform*> PlatformsToTrigger;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "TriggerVolume")
	class UBoxComponent* TriggerVolume = nullptr;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnButtonAtTheSwap(MCEndPositionEnum Position);
};
