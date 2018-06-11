// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
	bool bParentInitResult = Super::Initialize();
	if (!bParentInitResult || !Host || !Join || !Back || !JoinTheGame || !ExitButton) return false;
	
	Host->OnClicked.AddDynamic(this, &UMainMenu::OnHostClick);
	Join->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClick);
	Back->OnClicked.AddDynamic(this, &UMainMenu::OnBackClick);
	JoinTheGame->OnClicked.AddDynamic(this, &UMainMenu::OnJoinTheGameClick);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::OnExitClick);

	return true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeGameOnly GameInputMode;

	PlayerController->SetInputMode(GameInputMode);
	PlayerController->bShowMouseCursor = false;

}

void UMainMenu::OnExitClick()
{
	if (!MenuInterface) return;
	MenuInterface->ExitTheGame();
}

void UMainMenu::OnHostClick()
{
	if (!MenuInterface) return;
	MenuInterface->Host();
}

void UMainMenu::OnJoinClick()
{
	if (!MenuSwitcher) return;
	auto numberOfWidgets = MenuSwitcher->GetNumWidgets();
	MenuSwitcher->SetActiveWidgetIndex(numberOfWidgets-1);
}

void UMainMenu::OnBackClick()
{
	if (!MenuSwitcher) return;
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UMainMenu::OnJoinTheGameClick()
{
	if (!IpAddress || !MenuInterface) return;
	auto ip = IpAddress->GetText();
	if (ip.IsEmpty()) return;
	MenuInterface->Join(ip.ToString());
}

void UMainMenu::Setup(IMenuInterface* implementation)
{
	AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly UIInputMode;
	UIInputMode.SetWidgetToFocus(TakeWidget());
	UIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(UIInputMode);
	PlayerController->bShowMouseCursor = true;

	MenuInterface = implementation;
}
