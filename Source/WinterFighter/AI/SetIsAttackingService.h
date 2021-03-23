// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "SetIsAttackingService.generated.h"

/**
 * Class checking if enemy character is currently attacking & setting the value to Blackboard property
 */
UCLASS()
class WINTERFIGHTER_API USetIsAttackingService : public UBTService_BlackboardBase
{
	GENERATED_BODY()


private:
	USetIsAttackingService();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
