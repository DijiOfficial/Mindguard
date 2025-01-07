#include "BaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName("BlockAllDynamic");
	// Set the collision sphere radius to 10
	Collision->SetSphereRadius(10.0f);
	
	Collision->bEditableWhenInherited = true; // Allow editing in derived Blueprints
	RootComponent = Collision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bEditableWhenInherited = true; // Allow editing in derived Blueprints


	// Create a StaticMeshComponent (or use a different mesh type if you need)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->bEditableWhenInherited = true; // Allow editing in derived Blueprints

	// Set the StaticMesh to a Sphere
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMesh.Object);
	}

	// Set the material to "BasicShapeMaterial"
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (Material.Succeeded())
	{
		Mesh->SetMaterial(0, Material.Object);
	}

	// Set the scale of the mesh to 0.2
	Mesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

