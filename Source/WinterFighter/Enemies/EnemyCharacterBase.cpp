// © Jan Horák 2021


#include "WinterFighter/Enemies/EnemyCharacterBase.h"
#include "WinterFighter/EnemySword.h"

// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyCharacterBase::BeginPlay() 
{
	Super::BeginPlay();
	SetSword();

}


void AEnemyCharacterBase::WasHitWithoutDamage() 
{
	SetIsHit(true);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
    TimerDel.BindUFunction(this, FName("SetIsHit"), false);
    GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, GetCurrentAttack().AttackDuration, false);
}

FAttackTemplate AEnemyCharacterBase::GetCurrentAttack() 
{
	return AttackTemplate;
}


// Sets sword
void AEnemyCharacterBase::SetSword() 
{
	Sword = GetWorld()->SpawnActor<AEnemySword>(SwordBlueprintClass);
	if (!Sword) return;

	// Attach the sword to the sword's socket
	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);

	Sword->SetOwner(this);
}

