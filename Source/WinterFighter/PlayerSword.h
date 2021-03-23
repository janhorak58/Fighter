// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "Sword.h"
#include "PlayerSword.generated.h"

/**
 * Class representing Player Sword
 */
UCLASS()
class WINTERFIGHTER_API APlayerSword : public ASword
{
	GENERATED_BODY()

protected:

	// Called On Capsule components overlapps (hits) something - does reaction - takes damage
	UFUNCTION(BlueprintCallable)
	virtual void OnSwordHit(AActor* HitActor, UPrimitiveComponent* HitComponent, FHitResult HitResult, int LevelOfDamage);

	
};
