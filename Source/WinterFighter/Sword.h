// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

/*
 * Base class for Player & Enemy Sword 
*/
UCLASS()
class WINTERFIGHTER_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();

protected:

	// Returns Owner Controller
	AController* GetOwnerController() const;

	// Plays Effects
	virtual void PlayEffects(FVector Location, FRotator Rotation);
	

	// Sound That is being played when capsule component overlaps (hits) something
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* HitSound;

	// Effect That is being played when capsule component overlaps (hits) something
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitFlash;

	// DEFAULT SUBOBJECTS

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp = nullptr;

		
};
