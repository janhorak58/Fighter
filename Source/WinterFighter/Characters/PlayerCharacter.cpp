// © Jan Horák 2021


#include "WinterFighter/Characters/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "WinterFighter/PlayerSword.h"




// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// hand mesh
	// RoboticHand = CreateDefcaultSubobject<USkeletalMeshComponent>(FName("Mesh Component"));
	//RoboticHand->SetupAttachment(RootComponent);
}

void APlayerCharacter::BeginPlay() 
{
	Super::BeginPlay();

	SetSword();

	SetMaxAttackIndex();

	Mana = MaxMana;

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Mana +  ManaIncrease * DeltaTime >= MaxMana) return;
	Mana += ManaIncrease * DeltaTime;
}

// MOVEMENT & INPUT & CONTROLL

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("ChangeAttack"), this, &APlayerCharacter::ChangeAttackIndex);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Attack);

}

void APlayerCharacter::MoveForward(float AxisValue) 
{
	if (!bIsAttacking && !bIsHit && bCanMove)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue);
	}
}

void APlayerCharacter::LookUp(float AxisValue) 
{
	if (bCanMove) AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue) 
{
	if (!bIsAttacking && !bIsHit && bCanMove)
	{
		AddMovementInput(GetActorRightVector() * AxisValue);
	}
	
}

void APlayerCharacter::LookRight(float AxisValue) 
{
	if (bCanMove) AddControllerYawInput(AxisValue);
	
}

// OTHER FUNCTIONS

// Sets sword
void APlayerCharacter::SetSword() 
{
	Sword = GetWorld()->SpawnActor<APlayerSword>(SwordBlueprintClass);
	if (!Sword) return;

	// Attach the sword to the sword's socket
	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);

	Sword->SetOwner(this);
}

// Sets MaxAttackIndex Variable
void APlayerCharacter::SetMaxAttackIndex() 
{
	MaxAttackIndex = 0;
	for (FAttackTemplate Attack : AttackTemplates)
	{
		if (Attack.bCanBeDone) MaxAttackIndex += 1;
	}
}

// Handles attack if is unlocked
void APlayerCharacter::Attack() 
{
	
	FAttackTemplate Attack = GetCurrentAttack();
	if (Mana < Attack.ManaValue) return;
	if (Attack.bCanBeDone)
	{
		Mana -= Attack.ManaValue;
		bIsAttacking = true;
		SetAfterAttackTimer();
	}
}

// Changes Attack index
void APlayerCharacter::ChangeAttackIndex(float AxisValue) 
{
	AxisValue = FMath::Clamp(AxisValue, -1.f, 1.f);
	AxisValue = FMath::RoundHalfToZero(AxisValue);
	if (AxisValue != 1 && AxisValue != -1) return;
	if (AttackIndex + AxisValue < 0) 
	{
		AttackIndex = MaxAttackIndex - 1;	
	} 
	else if (AttackIndex + AxisValue >= MaxAttackIndex)
	{
		AttackIndex = 0;
	}
	else
	{
		AttackIndex += AxisValue;
	}
	//UE_LOG(LogTemp, Error, TEXT("Index: %i"), AttackIndex);
}

// Returns Health / MaxHealth
float APlayerCharacter::GetHealthPercent() 
{
	return Health/MaxHealth;
}

// Returns Mana / MaxMana
float APlayerCharacter::GetManaPercent()
{
	return Mana/MaxMana;

}

// Returns CurrentAttackIndex / MaxAttackIndex
float APlayerCharacter::GetSelectedAttackInPercent() 
{
	return UKismetMathLibrary::Conv_IntToFloat(AttackIndex)/UKismetMathLibrary::Conv_IntToFloat(MaxAttackIndex - 1);
}

// Returns Attack index
int APlayerCharacter::GetAttackIndex() 
{
	return AttackIndex;
}

// Returns Current Attack Name as FName
FName APlayerCharacter::GetCurrentAttackName() 
{
	return GetCurrentAttack().AttackName;
}

bool APlayerCharacter::GetAttackUnlockedByIndex(int Index) 
{
	return AttackTemplates[Index].bCanBeDone;
}

int APlayerCharacter::GetCurrentAttackIndex() 
{
	return AttackIndex;
}
void APlayerCharacter::SetCurrentAttackIndex(int Index) 
{
	AttackIndex = Index;
}

// Returns CurrentAttack
FAttackTemplate APlayerCharacter::GetCurrentAttack() 
{
	return AttackTemplates[AttackIndex];
}




