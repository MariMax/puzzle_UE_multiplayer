// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"
#include "Components/Button.h"

bool UGameMenu::Initialize()
{
	bool bParentResult = Super::Initialize();
	if (!bParentResult || !Resume || !Quit) return false;

	Resume->OnClicked.AddDynamic(this, &UGameMenu::CloseMenu);
	Quit->OnClicked.AddDynamic(this, &UGameMenu::OnQuitClick);

	return true;
}

void UGameMenu::CloseMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Close menu"))
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly InputData;

	PlayerController->SetInputMode(InputData);
	
	this->RemoveFromViewport();
}

void UGameMenu::OnQuitClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit"))
	if (!GameMenu) return;
	GameMenu->LoadMainMenu();
}

void UGameMenu::OpenMenu()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly InputData;

	InputData.SetWidgetToFocus(this->TakeWidget());
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputData);
	PlayerController->bShowMouseCursor = true;
	this->AddToViewport();
}

void UGameMenu::SetupMenu(IGameMenuInterface * IGameMenuImplementation)
{
	GameMenu = IGameMenuImplementation;
}
