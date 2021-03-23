// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "Sword.h"
#include "EnemySword.generated.h"

/**
 * Class of enemies Sword
 */
UCLASS()
class WINTERFIGHTER_API AEnemySword : public ASword
{
	GENERATED_BODY()
protected:
	// Called On Capsule components overlapps (hits) something - does reaction - takes damage/call fake damage
	UFUNCTION(BlueprintCallable)
	virtual void OnSwordHit(AActor* HitActor, UPrimitiveComponent* HitComponent, FHitResult HitResult, int LevelOfDamage);

	bool WasHitByEnemy(AActor* HitActor, int LevelOfDamage);

	// True if ingnoring other enemies Swords
	UPROPERTY(EditAnywhere)
	bool IgnoreEnemyHit = true;

};
