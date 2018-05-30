// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovingComponent.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class MCEndPositionEnum : uint8
{
	MC_Start 	UMETA(DisplayName = "Start position"),
	MC_End 	UMETA(DisplayName = "End Position"),
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FMovingComponentPosition, MCEndPositionEnum, Position );


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDestiantionLocation(FVector);
	void EnableComponent(bool);

	FMovingComponentPosition OnEndPosition;
	void SwapDirection();

private:
	FVector StartPosition;
	FVector EndPosition;
	FVector DestinationLocation;
	FVector InitialLocation;
	class AActor* OwnerActor = nullptr;
	bool DestinationLocationSet = false;

	void MovePlatform(float);
	

	UPROPERTY(EditAnywhere, Category = "Moving Component Speed")
	float Speed = 20;

	UPROPERTY(EditAnywhere, Category = "Moving Component Enabled?")
	bool Enabled = true;
};
