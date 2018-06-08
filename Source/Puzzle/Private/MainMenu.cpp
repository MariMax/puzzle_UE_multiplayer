// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool bParentInitResult = Super::Initialize();
	if (!bParentInitResult || !Host || !Join) return false;
	
	Host->OnClicked.AddDynamic(this, &UMainMenu::OnHostClick);
	Join->OnClicked.AddDynamic(this, &UMainMenu::OnJoinClick);


	return true;
}

void UMainMenu::OnHostClick()
{
	if (!MenuInterface) return;
	MenuInterface->Host();
}

void UMainMenu::OnJoinClick()
{
	UE_LOG(LogTemp, Warning, TEXT("JOIN"))
}

void UMainMenu::SetMenuInterface(IMenuInterface* implementation)
{
	MenuInterface = implementation;
}
