// © Jan Horák 2021


#include "EnemySword.h"

#include "WinterFighter/Characters/PlayerCharacter.h"
#include "WinterFighter/Enemies/EnemyCharacterBase.h"




void AEnemySword::OnSwordHit(AActor* HitActor, UPrimitiveComponent* HitComponent, FHitResult HitResult, int LevelOfDamage) 
{

    // CHECKS

    // Checking if causer is owner
	if (GetOwner()->GetName() == HitActor->GetName()) return;

	APlayerCharacter*  PlayerChar = Cast<APlayerCharacter>(HitActor);
	AEnemyCharacterBase* ThisChar = Cast<AEnemyCharacterBase>(GetOwner());

	// Checking if PlayerChar =! nullptr
	if (!ThisChar) return;

	// Checking if This character is attacking
	if (!ThisChar->GetIsAttacking()) return;

    //  Checking if causer was enemy
    if (!IgnoreEnemyHit)
    {
        if (WasHitByEnemy(HitActor, LevelOfDamage)) return;
    }

	// Checks if PlayerChar =! nullptr
	if (!PlayerChar) return;

	// Setting Player's HitLevelOfDamage property
	PlayerChar->SetHitLevelOfDamage(LevelOfDamage);

	// Plays Sound & Effects
	PlayEffects(HitActor->GetActorLocation(), HitActor->GetActorRotation());

    // Creating OwnerConroller & checking if not nullptr  
	AController* OwnerController = GetOwnerController();
    if (!OwnerController) return;

    // CALING TAKE DAMAGE FUNCTION ON PLAYER
    float Damage = ThisChar->GetCurrentAttack().Damage;
	FPointDamageEvent DamageEvent(Damage, HitResult, FVector(0), nullptr);
	HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);

    // Setting timer to se player's bIsHit property to false
	PlayerChar->SetIsHitFalseTimer(ThisChar->GetCurrentAttack().ShockTime);

    // Checking if player is dead (Health <= 0)
	if (PlayerChar->GetIsDead())
	{
		PlayerChar->HandleDeath();
	}	
}

// Cheks if This character was hit by enemy
bool AEnemySword::WasHitByEnemy(AActor* HitActor, int LevelOfDamage) 
{
    if (Cast<AEnemyCharacterBase>(HitActor)) 
    {
        Cast<AEnemyCharacterBase>(HitActor)->SetHitLevelOfDamage(LevelOfDamage);
        Cast<AEnemyCharacterBase>(HitActor)->WasHitWithoutDamage();
        return true;
    }
    return false;
}