// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * Class that controlls Enemy behavior
 */
UCLASS()
class WINTERFIGHTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:

	// Behavior Tree that controlls this enemy behavior
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

public:
	// Sets blackboard property IsDead
	void SetBlackboardIsDead(bool IsDead);

	bool IsDead();
	
};
