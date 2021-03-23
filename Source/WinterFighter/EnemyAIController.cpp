// © Jan Horák 2021


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"




void AEnemyAIController::BeginPlay() 
{
    Super::BeginPlay();

    // Checking if Behavior Tree is set
    if (!AIBehavior) return;

    // Runs AI Behavior Tree
    RunBehaviorTree(AIBehavior);

    // Sets DefaultValues
    GetBlackboardComponent()->SetValueAsBool(TEXT("IsDead"), false);
    GetBlackboardComponent()->SetValueAsVector(TEXT("InitialPosition"), GetPawn()->GetActorLocation());

}

// Sets blackboard property IsDead
void AEnemyAIController::SetBlackboardIsDead(bool IsDead) 
{
    if (!AIBehavior) return;

    GetBlackboardComponent()->SetValueAsBool(TEXT("IsDead"), IsDead);
}



