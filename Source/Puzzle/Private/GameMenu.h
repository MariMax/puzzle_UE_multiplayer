// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuInterface.h"
#include "GameMenu.generated.h"


class UButton;

/**
 * 
 */
UCLASS()
class UGameMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* Resume;

	UPROPERTY(meta = (BindWidget))
	UButton* Quit;
	
	virtual bool Initialize() override;

	UFUNCTION()
	void CloseMenu();

	UFUNCTION()
	void OnQuitClick();

	IGameMenuInterface* GameMenu;

public:
	void OpenMenu();

	void SetupMenu(IGameMenuInterface* IGameMenuImplementation);
};