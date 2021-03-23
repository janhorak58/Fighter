// © Jan Horák 2021


#include "PlayerSword.h"
#include "WinterFighter/Characters/PlayerCharacter.h"
#include "WinterFighter/Enemies/EnemyCharacterBase.h"




void APlayerSword::OnSwordHit(AActor* HitActor, UPrimitiveComponent* HitComponent, FHitResult HitResult, int LevelOfDamage) 
{
    // CHECKS

    // Checking if causer is owner
	if (GetOwner()->GetName() == HitActor->GetName()) return;


	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(GetOwner());
	AEnemyCharacterBase* HitEnemyChar = Cast<AEnemyCharacterBase>(HitActor);

	// Checking if HitEnemyChar =! nullptr
	if (!PlayerChar) return;

	// Checks if player is attacking
	if (!PlayerChar->GetIsAttacking()) return;

	// Checks if HitEnemyChar =! nullptr
	if (!HitEnemyChar) return;

	// Setting Hit Enemy's HitLevelOfDamage property
	HitEnemyChar->SetHitLevelOfDamage(LevelOfDamage);

	// Plays Sound & Effect
	PlayEffects(HitActor->GetActorLocation(), HitActor->GetActorRotation());

    // Creating OwnerConroller & checking if not nullptr  
	AController* OwnerController = GetOwnerController();
    if (!PlayerChar || !OwnerController) return;

    // CALING TAKE DAMAGE FUNCTION ON PLAYER
    float Damage = PlayerChar->GetCurrentAttack().Damage;
	FPointDamageEvent DamageEvent(Damage, HitResult, FVector(0), nullptr);
	HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);

    // Setting timer to se player's bIsHit property to false
	HitEnemyChar->SetIsHitFalseTimer(PlayerChar->GetCurrentAttack().ShockTime);



    // Checking if hit enemy is dead (Health <= 0)
	if (HitEnemyChar->GetIsDead())
	{
		HitEnemyChar->HandleDeath();
	}	
}
