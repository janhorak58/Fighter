// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_SetPlayerLocationIfSeen.generated.h"

/**
 * Sets Player if is in acceptance radius & can be seen
 */
UCLASS()
class WINTERFIGHTER_API UBTS_SetPlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()


private:
	UBTS_SetPlayerLocationIfSeen();

	// How far is the player from this enemy
	float GetDistanceFromPlayer(UBehaviorTreeComponent& OwnerComp);
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
