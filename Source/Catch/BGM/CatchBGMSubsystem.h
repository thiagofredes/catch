// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CatchBGMSubsystem.generated.h"

class UAudioComponent;
class USoundBase;


/**
 * 
 */
UCLASS()
class CATCH_API UCatchBGMSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Catch|Audio")
	void PlayBGM(USoundBase* NewMusic, float FadeDuration = 1.0f);

	UFUNCTION(BlueprintCallable, Category= "Catch|Audio")
	void StopBGM(float FadeDuration = 1.0f);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Catch|Audio")
	float DefaultFadeDuration = 1.0f;

	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioSlots[2];

	int32 ActiveSlotIndex;

	UPROPERTY()
	TObjectPtr<USoundBase> CurrentMusicAsset;

	void OnFadeOutCompleted(UAudioComponent* CompletedAudioComponent);
};
