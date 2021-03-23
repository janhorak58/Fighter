// © Jan Horák 2021

#include "WinterFighter/AI/SetIsAttackingService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "WinterFighter/Characters/CharacterBase.h"


USetIsAttackingService::USetIsAttackingService() 
{
    NodeName = TEXT("SetIsAttacking");
}

void USetIsAttackingService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{

    if (!OwnerComp.GetAIOwner()) return;
    
    ACharacterBase* SelfCharacter = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
    if (!SelfCharacter) return;

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), SelfCharacter->GetIsAttacking());
}


