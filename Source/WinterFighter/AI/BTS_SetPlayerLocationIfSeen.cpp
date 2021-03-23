//© Jan Horák 2021


#include "WinterFighter/AI/BTS_SetPlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "WinterFighter/Enemies/EnemyCharacterBase.h"
#include "GenericPlatform/GenericPlatformMath.h"


UBTS_SetPlayerLocationIfSeen::UBTS_SetPlayerLocationIfSeen() 
{
    NodeName = TEXT("SetPlayerLocationIfSeen");
}

// How far is the player from this enemy
float UBTS_SetPlayerLocationIfSeen::GetDistanceFromPlayer(UBehaviorTreeComponent& OwnerComp) 
{
    FVector OwnerLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
    FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
    return FGenericPlatformMath::Abs(OwnerLocation.Size() - PlayerLocation.Size());
}

void UBTS_SetPlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    if (!OwnerComp.GetAIOwner()) return;
    
    // Gets Player Pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn) return;

    // if Line trace to player in acceptance radius is successful sets selected blackboard value to PlayerPawn
    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn) && GetDistanceFromPlayer(OwnerComp) < Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn())->AcceptanceRadius)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else 
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }  


}
    