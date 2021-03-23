// © Jan Horák 2021


#include "KillEmAllAndPullTriggerGameMode.h"
#include "GameFramework/Controller.h"
#include "WinterFighter/EnemyAIController.h"
#include "EngineUtils.h"
#include "FighterPlayerController.h"
#include "WinterFighter/Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"


void AKillEmAllAndPullTriggerGameMode::PawnKilled(APawn* PawnKilled) 
{
    if (PawnKilled)
    {
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
        LevelComplete(false, PlayerController);
    }
    }
    

    for (AEnemyAIController* Controller : TActorRange<AEnemyAIController>(GetWorld()))
    {
        if (!Cast<ACharacterBase>(Controller->GetPawn())->GetIsDead()) return;
    }
    AreAllEnemiesDead = true;
}

bool AKillEmAllAndPullTriggerGameMode::GetAreAllEnemiesDead() 
{
    return AreAllEnemiesDead;
}

void AKillEmAllAndPullTriggerGameMode::LevelComplete(bool bPlayerWon, AController* Controller) 
{
    if (AreAllEnemiesDead)
    {
        Controller->GameHasEnded(UGameplayStatics::GetPlayerPawn(GetWorld(), 0), bPlayerWon);  
    }
    else
    {
        if (bPlayerWon)
        {
            Cast<AFighterPlayerController>(Controller)->ExitReachedButNotEveryoneKilled();
        }
        else if (Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->GetIsDead())
        {
            Controller->GameHasEnded(Controller->GetPawn(), bPlayerWon);  
            
        }

    }  
}

void AKillEmAllAndPullTriggerGameMode::BeginPlay() 
{
    Super::BeginPlay();
    AreAllEnemiesDead = false;
}
