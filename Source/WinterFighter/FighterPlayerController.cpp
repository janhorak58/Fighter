// © Jan Horák 2021


#include "FighterPlayerController.h"
#include "Blueprint/UserWidget.h"


void AFighterPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    // Creates & places widget on the screen if we're not in the menu
    if (GetWorld()->GetName() != "Menu")
    {
        HUD = CreateWidget(this, HUDClass);
        if (!HUD) return;
        HUD->AddToViewport();
    }
    
}



    void AFighterPlayerController::RemoveFromViewport(UUserWidget* Message)
    {
    if (Message)
    {
        Message->RemoveFromViewport();
    }
    }
    
    void AFighterPlayerController::ExitReachedButNotEveryoneKilled() 
    {
        UUserWidget* Message = CreateWidget(this, ExitReachedButNotEveryoneKilledWidget);

        if (!Message) return;
        Message->AddToViewport();
        FTimerHandle TimerHandle;
	    FTimerDelegate TimerDel;
        TimerDel.BindUFunction(this, FName("RemoveFromViewport"), Message);
        GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 5, false);
    }

// Called by controlling character when his Health <= 0
void AFighterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    // Removes Widget
    if (HUD)
    {
        HUD->RemoveFromViewport();
    }
   if (!bIsWinner)
    {
        UUserWidget* LoseScreen = CreateWidget(this, DeathWidget);

        if (!LoseScreen) return;
        LoseScreen->AddToViewport();

        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, RestartDelay, false);

    } 
    else
    {
        UUserWidget* WinScreen = CreateWidget(this, LevelCompleteWidget);

        if (!WinScreen) return;
        WinScreen->AddToViewport();
    }

}
