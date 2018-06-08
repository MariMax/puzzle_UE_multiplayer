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

	virtual bool Initialize() override;

	UFUNCTION()
	void OnHostClick();

	UFUNCTION()
	void OnJoinClick();

	IMenuInterface* MenuInterface = nullptr;

public:
	void SetMenuInterface(IMenuInterface*);

};
