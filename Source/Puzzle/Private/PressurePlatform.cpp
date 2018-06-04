// Fill out your copyright notice in the Description page of Project Settings.

#include "PressurePlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "MovingPlatform.h"


void APressurePlatform::InitPlatfomMovementLimits()
{
	UStaticMesh* mesh = Mesh->GetStaticMesh();
	if (!mesh) return;
	auto scale = Mesh->GetComponentScale();
	FBox box = mesh->GetBoundingBox();
	auto Height = box.GetSize().Z * scale.Z;
	auto NormalState = Mesh->GetComponentLocation();
	auto PressedState = NormalState - 2* FVector(0, 0, Height);
	MC->SetDestiantionLocation(PressedState);
}

// Sets default values
APressurePlatform::APressurePlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(SceneRoot);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	TriggerVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MC = CreateDefaultSubobject<UMovingComponent>(FName("MC"));
	MC->EnableComponent(false);

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

// Called when the game starts or when spawned
void APressurePlatform::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(TriggerVolume != nullptr)) return;
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APressurePlatform::OnBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APressurePlatform::OnEndOverlap);
	InitPlatfomMovementLimits();
	MC->OnEndPosition.AddDynamic(this, &APressurePlatform::OnButtonAtTheSwap);
}

void APressurePlatform::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	for (AMovingPlatform* platform : PlatformsToTrigger)
	{
		platform->AddActiveTrigger();
	}
	if (ButtonPosition == MCEndPositionEnum::MC_Start)
	{
		return MC->EnableComponent(true);
	}
	return MC->SwapDirection();

}

void APressurePlatform::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	for (AMovingPlatform* platform : PlatformsToTrigger)
	{
		platform->RemoveActiveTrigger();
	}
	if (ButtonPosition == MCEndPositionEnum::MC_End)
	{
		return MC->EnableComponent(true);
	}
	return MC->SwapDirection();
}

void APressurePlatform::OnButtonAtTheSwap(MCEndPositionEnum Position)
{
	ButtonPosition = Position;
	MC->EnableComponent(false);
}

// Called every frame
void APressurePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

