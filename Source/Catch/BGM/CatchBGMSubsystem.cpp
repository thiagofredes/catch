// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchBGMSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void UCatchBGMSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ActiveSlotIndex = 0;
	CurrentMusicAsset = nullptr;

	for (int32 i = 0; i < 2; ++i)
	{
		AudioSlots[i] = NewObject<UAudioComponent>(GetWorld(), FName(*FString::Printf(TEXT("AudioSlot_%d"), i)));

		if (AudioSlots[i])
		{
			AudioSlots[i]->bAutoDestroy = false;
			AudioSlots[i]->bAutoActivate = false;
			AudioSlots[i]->bAutoDestroy = false;
			AudioSlots[i]->bIsUISound = true;
			AudioSlots[i]->RegisterComponent();
		}
	}

}

void UCatchBGMSubsystem::Deinitialize()
{
	for (int32 i = 0; i < 2; ++i)
	{
		if (AudioSlots[i])
		{
			AudioSlots[i]->Stop();
			AudioSlots[i] = nullptr;
		}
	}
	Super::Deinitialize();
}

void UCatchBGMSubsystem::PlayBGM(USoundBase* NewMusic, float FadeDuration)
{
	
	if (!NewMusic || CurrentMusicAsset == NewMusic) return;
	
	CurrentMusicAsset = NewMusic;

	UAudioComponent* OldComp = AudioSlots[ActiveSlotIndex];
	ActiveSlotIndex = (ActiveSlotIndex + 1) % 2;
	UAudioComponent* NewComp = AudioSlots[ActiveSlotIndex];
	
	if (OldComp && OldComp->IsPlaying())
	{
		OldComp->OnAudioFinishedNative.Clear();
		OldComp->OnAudioFinishedNative.AddUObject(this, &UCatchBGMSubsystem::OnFadeOutCompleted);
		OldComp->FadeOut(FadeDuration, 0.0f);
	}

	if (NewComp)
	{
		NewComp->OnAudioFinishedNative.Clear();
		NewComp->SetSound(NewMusic);
		NewComp->FadeIn(FadeDuration, 1.0f, 0.0f);
	}
}

void UCatchBGMSubsystem::StopBGM(float FadeDuration)
{
	CurrentMusicAsset = nullptr;

	for (int32 i = 0; i < 2; ++i)
	{
		if (AudioSlots[i] && AudioSlots[i]->IsPlaying())
		{
			AudioSlots[i]->FadeOut(FadeDuration, 0.0f);
		}
	}
}

void UCatchBGMSubsystem::OnFadeOutCompleted(UAudioComponent* CompletedAudioComponent)
{
	const int32 InactiveSlotIndex = (ActiveSlotIndex + 1) % 2;
	UAudioComponent* OldComp = AudioSlots[InactiveSlotIndex];

	if (OldComp)
	{
		OldComp->OnAudioFinishedNative.Clear();
		OldComp->Stop();
		OldComp->SetSound(nullptr);
	}
}
