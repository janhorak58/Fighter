// © Jan Horák 2021

#pragma once

#include "CoreMinimal.h"
#include "WinterFighter/Characters/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/*
 * Class Reperesenting Player character
*/
UCLASS()
class WINTERFIGHTER_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles attack if is unlocked
	virtual void Attack() override;
	
	// Gets Current Attack
	virtual FAttackTemplate GetCurrentAttack() override;

private:
	// UFUNCTIONS

	// Returns Health / MaxHealth
	UFUNCTION(BlueprintPure)
	float GetHealthPercent();

	// Returns Mana / MaxMana
	UFUNCTION(BlueprintPure)
	float GetManaPercent();

	// Gets This attack in float (This attack index / Max attack index)
	UFUNCTION(BlueprintPure)
	float GetSelectedAttackInPercent();

	// Returns FName of current Attack
	UFUNCTION(BlueprintPure)
	FName GetCurrentAttackName();

	UFUNCTION(BlueprintPure)
	bool GetAttackUnlockedByIndex(int Index);

	UFUNCTION(BlueprintPure)
	int GetCurrentAttackIndex();

	// Returns FName of current Attack
	UFUNCTION(BlueprintCallable)
	void SetCurrentAttackIndex(int Index);

	// INPUT & CONTROLL
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);

	// Changes Attack index
	void ChangeAttackIndex(float AxisValue);

	// ATTACK

	UFUNCTION(BlueprintPure)
	int GetAttackIndex();

	// Array of all the attacks that this character can use
	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray<FAttackTemplate> AttackTemplates;

		// Index of current attack
	UPROPERTY(EditAnywhere, Category = "Attack")
	int AttackIndex = 0;

	// Actual number of attacks - 1
	int MaxAttackIndex = 0;

	// Class of character's sword
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class APlayerSword> SwordBlueprintClass;

	// UPROPERTY(VisibleAnywhere)
	// USkeletalMeshComponent* RoboticHand;

	// Character's sword
	APlayerSword* Sword;

	// Sets MaxAttackIndex property on BeginPlay()
	void SetMaxAttackIndex();

	// Sets the sword on BeginPlay()
	void SetSword();

	UPROPERTY(EditDefaultsOnly)
	float MaxMana = 200;

	float Mana = 200;

	UPROPERTY(EditDefaultsOnly)
	float ManaIncrease = 0.01;

};
