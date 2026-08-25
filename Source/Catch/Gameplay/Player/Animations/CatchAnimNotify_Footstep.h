// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CatchAnimNotify_Footstep.generated.h"

/**
 * 
 */
UCLASS()
class CATCH_API UCatchAnimNotify_Footstep : public UAnimNotify
{
	GENERATED_BODY()

public:

	UCatchAnimNotify_Footstep();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
