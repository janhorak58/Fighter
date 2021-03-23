// © Jan Horák 2021


#include "Sword.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root Component
	SceneComp = CreateDefaultSubobject<USceneComponent>(FName("Scene Component"));
	SetRootComponent(SceneComp);



	// Collider
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(FName("CapsuleCollider"));
	CapsuleComp->SetupAttachment(SceneComp);

}

// Returns Owner's Controller
AController* ASword::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;
	return OwnerPawn->GetController();
}

void ASword::PlayEffects(FVector Location, FRotator Rotation) 
{
	if (HitSound && HitFlash)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Location, Rotation);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, Location, Rotation);
	}
}


