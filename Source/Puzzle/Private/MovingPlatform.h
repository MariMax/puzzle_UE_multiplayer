// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
	virtual void Tick(float DeltaTime) override;
	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:
	UPROPERTY(VisibleAnywhere, Category = "MovingComponent")
	class UMovingComponent* MovingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Number Active Triggers")
	int32 ActiveTriggers = 1;

	UPROPERTY(EditAnywhere, Category = "TargetLocation", Meta = (MakeEditWidget = true))
	FVector TargetLocation;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	FVector GlobalTargetLocation = FVector::ZeroVector;
};
