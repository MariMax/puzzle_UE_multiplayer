// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuInterface.h"
#include "GameMenuInterface.h"
#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UPuzzleGameInstance : public UGameInstance, public IMenuInterface, public IGameMenuInterface
{
	GENERATED_BODY()

	TSubclassOf<class UUserWidget> MainMenu;
	TSubclassOf<class UUserWidget> GameMenu;

	class UGameMenu* GameMenuInstance;

	virtual void QuitGame() override;
	
public:
	UPuzzleGameInstance(const FObjectInitializer &ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(const FString& Address);

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void OpenGameMenu();
	
};
