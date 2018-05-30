// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UMovingComponent::UMovingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UMovingComponent::MovePlatform(float DeltaTime)
{
	if (OwnerActor && OwnerActor->HasAuthority() && Enabled && DestinationLocationSet)
	{

		FVector currentLocation = OwnerActor->GetActorLocation();
		FVector direction = (DestinationLocation - InitialLocation).GetSafeNormal();
		float FullDistance = (DestinationLocation - InitialLocation).Size();
		float CurrentDistance = (InitialLocation - currentLocation).Size();
		if (FullDistance < CurrentDistance)
		{
			SwapDirection();
			float DistanceToStart = (StartPosition - currentLocation).Size();
			float DistanceToEnd = (EndPosition - currentLocation).Size();
			OnEndPosition.Broadcast(DistanceToStart > DistanceToEnd ? MCEndPositionEnum::MC_End : MCEndPositionEnum::MC_Start);
			return;
		}

		OwnerActor->SetActorLocation(currentLocation + direction * Speed * DeltaTime);
	}

}

void UMovingComponent::SwapDirection()
{
	if (!DestinationLocationSet) return;

	auto Swap = DestinationLocation;
	DestinationLocation = InitialLocation;
	InitialLocation = Swap;
}


// Called when the game starts
void UMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner();
	if (!OwnerActor) return;
	InitialLocation = OwnerActor->GetActorLocation();
	StartPosition = InitialLocation;

}


// Called every frame
void UMovingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MovePlatform(DeltaTime);
	// ...
}

void UMovingComponent::SetDestiantionLocation(FVector GlobalTargetPosition)
{
	DestinationLocation = GlobalTargetPosition;
	EndPosition = GlobalTargetPosition;
	DestinationLocationSet = true;
}

void UMovingComponent::EnableComponent(bool enabled)
{
	Enabled = enabled;
}

