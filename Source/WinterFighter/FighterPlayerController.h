// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FighterPlayerController.generated.h"

/**
 * Player's conroller - creates UI
 */
UCLASS()
class WINTERFIGHTER_API AFighterPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	// Class of widget that displays Mana, Health, Current Atatck etc.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	// Widget that displays Mana, Health, Current Atatck etc.
	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DeathWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LevelCompleteWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> ExitReachedButNotEveryoneKilledWidget;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	UFUNCTION()
	void RemoveFromViewport(UUserWidget* Message);

protected:
	virtual void BeginPlay() override;

public:
	// Called by controlling character when his Health <= 0
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	void ExitReachedButNotEveryoneKilled();

	
};
