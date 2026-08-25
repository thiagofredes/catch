// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchAnimNotify_Footstep.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimInstance.h"
#include "../PlayerCharacter.h"

UCatchAnimNotify_Footstep::UCatchAnimNotify_Footstep()
{
}

void UCatchAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp || !Animation) return;

	const FString AnimationName = Animation->GetName();

	if (APlayerCharacter* Character = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		Character->PlayFootstepSound(AnimationName);
	}
}
