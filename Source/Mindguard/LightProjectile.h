// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "LightProjectile.generated.h"

class UNiagaraComponent;
UCLASS()
class MINDGUARD_API ALightProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	// Constructor
	ALightProjectile();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Parameter", Meta = (ExposeOnSpawn = "true"))
	TObjectPtr<USceneComponent> HomingTargetComponent;
	
protected:
	// Niagara Component for visual effects
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraComponent* NiagaraEffect;
	
private:
	
	virtual void BeginPlay() override;
};
