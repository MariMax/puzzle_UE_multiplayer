// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer &ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuClassFinder(TEXT("/Game/Menu/BPW_MainMenu"));
	if (MainMenuClassFinder.Class)
	{
		MainMenu = MainMenuClassFinder.Class;
		UE_LOG(LogTemp, Warning, TEXT("MainMenuClass %s"), *MainMenuClassFinder.Class->GetName())
	}
	
}

void UPuzzleGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("init"))
}

void UPuzzleGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!Engine) return;
	Engine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Host"));

	UWorld* World = GetWorld();
	if (!World) return;
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

	if (!MainMenu) return;
	UUserWidget* MainMenuInstance = CreateWidget<UUserWidget>(this, MainMenu);
	if (!MainMenuInstance) return;

	MainMenuInstance->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!PlayerController) return;

	FInputModeUIOnly UIInputMode;
	UIInputMode.SetWidgetToFocus(MainMenuInstance->TakeWidget());
	UIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(UIInputMode);
	PlayerController->bShowMouseCursor = true;

	//UWorld* World = GetWorld();
	//if (!World) return;
	//UGameplayStatics::OpenLevel(World, TEXT("/Game/Menu/MainMenu"), ETravelType::TRAVEL_Absolute);
}
