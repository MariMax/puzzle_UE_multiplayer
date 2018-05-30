// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameInstance.h"

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer &ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("constructor"))
}

void UPuzzleGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("init"))
}
