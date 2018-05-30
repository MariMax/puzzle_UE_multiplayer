// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "MovingComponent.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetMobility(EComponentMobility::Movable);

	MovingComponent = CreateDefaultSubobject<UMovingComponent>(FName("MovingComponent"));
	MovingComponent->bAutoActivate = true;
	//MovingComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	MovingComponent->SetDestiantionLocation(GlobalTargetLocation);
	MovingComponent->EnableComponent(ActiveTriggers > 0);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
	MovingComponent->EnableComponent(true);
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
	if (ActiveTriggers == 0)
	{
		MovingComponent->EnableComponent(false);
	}
}
