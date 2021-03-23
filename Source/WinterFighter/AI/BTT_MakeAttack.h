// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_MakeAttack.generated.h"

/**
 * Makes actual attack - calls function on Enemy - Attack()
 */
UCLASS()
class WINTERFIGHTER_API UBTT_MakeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_MakeAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
