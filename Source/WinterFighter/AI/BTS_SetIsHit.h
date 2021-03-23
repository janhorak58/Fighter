// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_SetIsHit.generated.h"

/**
 * 
 */
UCLASS()
class WINTERFIGHTER_API UBTS_SetIsHit : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:
	UBTS_SetIsHit();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
