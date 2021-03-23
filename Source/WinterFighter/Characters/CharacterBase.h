// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

// Struct of an Attack - describes all the properties that attack has
USTRUCT(BlueprintType)
struct FAttackTemplate
{
	GENERATED_USTRUCT_BODY()

	// Name Of the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AttackName;

	// Index of the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttackIndex;

	// Level of damage of the attack - on this depends the reaction on this attack (levels 1 - 4)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelOfDamage;

	// Damage of the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	// Duration Of the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDuration;

	// How long the opponent is stunned after being hit by this attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShockTime;

	// How much Mana does the attack takes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaValue;

	// This is only for Enemies - how long should they wait until next executement of the attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;

	// If The attack is unlocked
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeDone = true;
};

/*
 * Base class of the Player & Enemy Character
 * Includes the Attack Struct
*/
UCLASS()
class WINTERFIGHTER_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// FUNCTIONS
	// 		UFUNCTIONS

	// Sets bIsHit Property to the passed argument
	UFUNCTION(BlueprintCallable)
	void SetIsHit(bool IsHitParam);

	// Sets bCanMove Property to the passed argument
	UFUNCTION(BlueprintCallable)
	void SetCanMove(bool CanMoveParam);

	UFUNCTION(BlueprintPure)
	bool GetCanMove();

	// Sets the bIsAttacking Property to the passed argument
	UFUNCTION(BlueprintCallable)
	virtual void SetIsAttacking(bool IsAttackingParam);

	// OTHER FUNCTIONS

	// Called by sword that hits this character to decrease the health 
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// PROPERTIES
	// 		UPROPERTIES

	// State of being hit or not
	UPROPERTY(EditAnywhere, Category = "State")
	bool bIsHit;

	// State of attacking or not
	UPROPERTY(EditAnywhere, Category = "State")
	bool bIsAttacking = false;

	// Starting Heath of the character
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 500.f;

	// Current Health of the character
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float Health = 500.f;

	// Current Health of the character
	UPROPERTY(VisibleAnywhere, Category = "Cutscene")
	bool bCanMove = true;

	// 		OTHER PROPERTIES



public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// FUNCTIONS
	//  	UFUNCTIONS

	// Return bool bIsHit
	UFUNCTION(BlueprintPure)
	bool GetIsHit();
	
	// Returns bool bIsAttacking
	UFUNCTION(BlueprintPure)
	bool GetIsAttacking();
	
	// Return true if Character is dead (Health <= 0)
	UFUNCTION(BlueprintPure)
	bool GetIsDead();

	// Returns Level Of Damage of current attack
	UFUNCTION(BlueprintPure)
	int GetLevelOfDamage();

	// Returns level of damage to apply on this Character 
	UFUNCTION(BlueprintPure)
	int GetHitLevelOfDamage();

	// Sets level of damage to apply on this Character 
	UFUNCTION(BlueprintCallable)
	void SetHitLevelOfDamage(int LevelOfDamage);

	// When Character is dead
	virtual void HandleDeath();
	
	// Sets timer after being hit
	void SetIsHitFalseTimer(float ShockTimeAfterHit);

	// Does the attack
	virtual void Attack();

	// Gets Current Attack
	UFUNCTION(BlueprintPure)
	virtual FAttackTemplate GetCurrentAttack();



protected:
	// FUNCTIONS

	// Disables visibility of the mesh after death
	void DisableVisibility();

	// Sets timer to set bIsAttacking back to false
	void SetAfterAttackTimer();

	// PROPERTIES
	// 		UPROPERTIES

	// Socket for the sword
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponSocketName = "Socket";

	// Time afte mesh diappears after death
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float DisappearTimeAfterDeath = 2.5f;

	// 		OTHER PROPERTIES

	// Level of damage to apply on this Character - Controlls animation (Values: 1-4)
	int CurrentHitLevelOfDamage = 1;

};
