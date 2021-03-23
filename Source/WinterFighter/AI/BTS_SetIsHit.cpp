// © Jan Horák 2021


#include "WinterFighter/AI/BTS_SetIsHit.h"
#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WinterFighter/Characters/CharacterBase.h"


UBTS_SetIsHit::UBTS_SetIsHit() 
{
    NodeName = TEXT("SetIsHit");
}

void UBTS_SetIsHit::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{

    ACharacterBase* SelfCharacter = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
    if (!SelfCharacter) return;
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), SelfCharacter->GetIsHit());
}