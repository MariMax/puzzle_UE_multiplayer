// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer &ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("constructor"))
}

void UPuzzleGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("init"))
}

void UPuzzleGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Host"));

	UWorld* World = GetWorld();
	if (!World) return;
	World->ServerTravel("/Game/Puzzle/Maps/Game?listen");
}

void UPuzzleGameInstance::Join(const FString & Address)
{
	UEngine* Engine = GetEngine();

	if (Engine)
	{
		Engine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	}
}
