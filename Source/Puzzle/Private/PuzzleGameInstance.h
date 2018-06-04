// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UPuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()

	TSubclassOf<class UUserWidget> MainMenu;
	
public:
	UPuzzleGameInstance(const FObjectInitializer &ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(const FString& Address);

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();
	
};
