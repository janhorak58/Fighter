// © Jan Horák 2021


#include "WinterFighter/Characters/CharacterBase.h"
#include "WinterFighter/Sword.h"
#include "Components/CapsuleComponent.h"
#include "WinterFighter/EnemyAIController.h"
#include "WinterFighter/FighterPlayerController.h"



// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called by other sword when hits this character
float ACharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetIsHit(true);

	// Decreasing health (Never could be under 0)
	Health -= FMath::Min(Health, DamageToApply);

	return DamageToApply;
}

// Get booleans functions

bool ACharacterBase::GetIsAttacking() 
{
	return bIsAttacking;
}

bool ACharacterBase::GetIsHit() 
{
	return bIsHit;
}

bool ACharacterBase::GetIsDead() 
{
	return Health <= 0.f;
}

// Get int functions

int ACharacterBase::GetLevelOfDamage() 
{
	return GetCurrentAttack().LevelOfDamage;
}

int ACharacterBase::GetHitLevelOfDamage() 
{
	return CurrentHitLevelOfDamage;
}

// Other Get functions

FAttackTemplate ACharacterBase::GetCurrentAttack() 
{
	FAttackTemplate AttackTemplate;
	return AttackTemplate;
}

// Void Functions
// Setters

// Sets bIsHit variable
void ACharacterBase::SetIsHit(bool IsHitParam = false) 
{
	bIsHit = IsHitParam;
}

bool ACharacterBase::GetCanMove()
{
	return bCanMove;
} 
void ACharacterBase::SetCanMove(bool CanMoveParam) 
{
	bCanMove = CanMoveParam;
}

// Sets timer after attack shocktime to set the bIsHit variable to false
void ACharacterBase::SetIsHitFalseTimer(float ShockTimeAfterHit)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
    TimerDel.BindUFunction(this, FName("SetIsHit"), false);
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, ShockTimeAfterHit, false);
} 

// Sets bIsAttacking
void ACharacterBase::SetIsAttacking(bool IsAttackingParam = false) 
{
	UE_LOG(LogTemp, Error, TEXT("%i"), IsAttackingParam);
	bIsAttacking = IsAttackingParam;
}

// Sets timer to set bIsAttacking back to false
void ACharacterBase::SetAfterAttackTimer() 
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
    TimerDel.BindUFunction(this, FName("SetIsAttacking"), false);
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, GetCurrentAttack().AttackDuration, false);
}

// Set Level of damage applied to this character
void ACharacterBase::SetHitLevelOfDamage(int LevelOfDamage) 
{
	CurrentHitLevelOfDamage = LevelOfDamage;
}

// Makes mesh unvisible
void ACharacterBase::DisableVisibility() 
{
	GetMesh()->SetVisibility(false, true);
}

// Do something when ... methods

// Called When character decides to attack
void ACharacterBase::Attack() 
{
	bIsAttacking = true;

	SetAfterAttackTimer();
}

// Called when health is <= 0
void ACharacterBase::HandleDeath() 
{
	// Sets Collision Disabled - so Character could not be hit by anything
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// If AI Sets in Behavior tree to die
	if (AEnemyAIController* EnemyController = Cast<AEnemyAIController>(GetController())) EnemyController->SetBlackboardIsDead(true);

	// If Player Calls method on FighterPlayerController called GameHasEnded
	if (AFighterPlayerController* PlayerController = Cast<AFighterPlayerController>(GetController())) PlayerController->GameHasEnded();

	DetachFromControllerPendingDestroy();

	// Sets timer to method that makes character unvisible
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACharacterBase::DisableVisibility, DisappearTimeAfterDeath, false);
}










