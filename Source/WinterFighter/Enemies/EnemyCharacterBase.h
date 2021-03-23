// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "WinterFighter/Characters/CharacterBase.h"
#include "EnemyCharacterBase.generated.h"

/*
 * Base class for all Enemies
*/
UCLASS()
class WINTERFIGHTER_API AEnemyCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	// Sets default values for this character's properties
	AEnemyCharacterBase();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AcceptanceRadius = 800.f;

	// Called when Enemy hit by another enemy
	void WasHitWithoutDamage();

	// Gets Current Attack
	virtual FAttackTemplate GetCurrentAttack() override;


private:
	UPROPERTY(EditAnywhere, Category="Attack")
	FAttackTemplate AttackTemplate;

	// Class of character's sword
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class AEnemySword> SwordBlueprintClass;

	// Sets the sword on BeginPlay()
	void SetSword();

	// Character's sword
	AEnemySword* Sword;


};
