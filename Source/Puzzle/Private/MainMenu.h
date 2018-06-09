// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* Host;

	UPROPERTY(meta = (BindWidget))
	UButton* Join;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinTheGame;

	UPROPERTY(meta = (BindWidget))
	UButton* Back;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IpAddress;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	UFUNCTION()
	void OnHostClick();

	UFUNCTION()
	void OnJoinClick();

	UFUNCTION()
	void OnBackClick();

	UFUNCTION()
	void OnJoinTheGameClick();

	int32 ActiveMenu = 0;

	IMenuInterface* MenuInterface = nullptr;

public:
	void Setup(IMenuInterface*);

};
