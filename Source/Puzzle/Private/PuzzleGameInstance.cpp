// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "GenericPlatform/GenericPlatformMisc.h"

void UPuzzleGameInstance::LoadMainMenu()
{
	//FGenericPlatformMisc::RequestExit(true);
	this->Join(TEXT("/Game/Menu/MainMenu"));
}

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer &ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuClassFinder(TEXT("/Game/Menu/BPW_MainMenu"));
	static ConstructorHelpers::FClassFinder<UUserWidget> GameMenuClassFinder(TEXT("/Game/Menu/BPW_GameMenu"));
	if (MainMenuClassFinder.Class)
	{
		MainMenu = MainMenuClassFinder.Class;
	}
	if (GameMenuClassFinder.Class)
	{
		GameMenu = GameMenuClassFinder.Class;
	}
	
}

void UPuzzleGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("init"))
}

void UPuzzleGameInstance::ExitTheGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;

	PlayerController->ConsoleCommand("quit");
}

void UPuzzleGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!Engine) return;
	
	UWorld* World = GetWorld();
	if (!World) return;
	Engine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Host"));
	World->ServerTravel("/Game/Puzzle/Maps/Game?listen");
}

void UPuzzleGameInstance::Join(const FString & Address)
{
	UEngine* Engine = GetEngine();

	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzleGameInstance::LoadMenu()
{

	if (MainMenu)
	{
		UMainMenu* MainMenuInstance = CreateWidget<UMainMenu>(this, MainMenu);
		if (!MainMenuInstance) return;

		MainMenuInstance->Setup(this);
	}

	//UWorld* World = GetWorld();
	//if (!World) return;
	//UGameplayStatics::OpenLevel(World, TEXT("/Game/Menu/MainMenu"), ETravelType::TRAVEL_Absolute);
}

void UPuzzleGameInstance::OpenGameMenu()
{
	if (GameMenu && !GameMenuInstance)
	{
		GameMenuInstance = CreateWidget<UGameMenu>(this, GameMenu);
	}

	if (GameMenuInstance)
	{
		GameMenuInstance->SetupMenu(this);
		GameMenuInstance->OpenMenu();
	}
}
