// © Jan Horák 2021


#include "BTT_MakeAttack.h"
#include "WinterFighter/Enemies/EnemyCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


UBTT_MakeAttack::UBTT_MakeAttack() 
{
    NodeName = TEXT("MakeAttack");
}

EBTNodeResult::Type UBTT_MakeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (ACharacterBase* OwnerCharacter = Cast<AEnemyCharacterBase>(OwnerComp.GetAIOwner()->GetPawn()))
    {
        // Sets delay between attacks
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("PauseBetweenAttacks"), OwnerCharacter->GetCurrentAttack().ReloadTime);
        
        // Making Attack
        OwnerCharacter->Attack();
    }
    

    return EBTNodeResult::Succeeded;

}
