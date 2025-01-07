#include "LightProjectile.h"
#include "NiagaraSystem.h"  // Include for Niagara System
#include "NiagaraComponent.h" // Include for Niagara Component
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

ALightProjectile::ALightProjectile()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the Niagara component
	NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraEffect->SetupAttachment(Collision);  // Attach it to the collision component
	NiagaraEffect->bEditableWhenInherited = true; // Allow editing in derived Blueprints

	// Set the position of the Niagara component
	NiagaraEffect->SetRelativeLocation(FVector(-320.0f, 0.0f, 0.0f));

	// Set the rotation of the Niagara component (180 degrees on Z-axis)
	NiagaraEffect->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	// Set the scale of the Niagara component to 6
	NiagaraEffect->SetRelativeScale3D(FVector(6.0f, 6.0f, 6.0f));
	
	// Set the scale of the Mesh to 0.3
	Mesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	
	// Set the material to "BasicShapeMaterial"
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/StarterContent/Materials/M_Glass.M_Glass'"));
	if (Material.Succeeded())
	{
		Mesh->SetMaterial(0, Material.Object);
	}
	// Set the Niagara system to NS_Basic_14
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/Mindguard/Art/Imports/Basic_VFX/Niagara/NS_Basic_14.NS_Basic_14'"));
	if (NiagaraAsset.Succeeded())
	{
		NiagaraEffect->SetAsset(NiagaraAsset.Object);
	}


	// Set the default speed of the projectile movement to 2000
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;  // Ensure the max speed matches initial speed

	// Enable homing for the projectile
	ProjectileMovement->bIsHomingProjectile = true;

	// Set the homing acceleration to 10000
	ProjectileMovement->HomingAccelerationMagnitude = 10000.0f;
}

void ALightProjectile::BeginPlay()
{
	if (HomingTargetComponent)  // Check if the HomingTargetComponent is valid
		if (ProjectileMovement)
			ProjectileMovement->HomingTargetComponent = HomingTargetComponent;
}