// JoystickPlugin is licensed under the MIT License.
// Copyright Jayden Maalouf 2026. All Rights Reserved.

#pragma once

#include "ForceFeedbackConfigurationBase.h"

#include "ForceFeedbackComponentConfiguration.generated.h"

USTRUCT(BlueprintType)
struct JOYSTICKPLUGIN_API FForceFeedbackComponentConfiguration : public FForceFeedbackConfigurationBase
{
	GENERATED_BODY()

	FForceFeedbackComponentConfiguration()
		: UseNativeAsyncPhysicsTick(false)
		  , UsePhysicsCallbackTick(false)
		  , OverrideEffectTick(true)
	{
	}

	FForceFeedbackComponentConfiguration(const FForceFeedbackConfigurationBase& BaseConfiguration, const bool bOverrideEffectTick)
		: Super(BaseConfiguration)
		  , UseNativeAsyncPhysicsTick(false)
		  , UsePhysicsCallbackTick(false)
		  , OverrideEffectTick(bOverrideEffectTick)
	{
	}

	FForceFeedbackComponentConfiguration(const bool bAutoInit, const bool bAutoStartOnInit, const bool bOverrideEffectTick)
		: Super(bAutoInit, bAutoStartOnInit)
		  , UseNativeAsyncPhysicsTick(false)
		  , UsePhysicsCallbackTick(false)
		  , OverrideEffectTick(bOverrideEffectTick)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joystick|Force Feedback|Tick",
		meta=(EditCondition="UsePhysicsCallbackTick == false", ToolTip="Adds the component to the native async physics tick callback. This runs on the physics thread, so ReceivedTick implementations must not touch game-thread-only state."))
	bool UseNativeAsyncPhysicsTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joystick|Force Feedback|Tick",
		meta=(EditCondition="UseNativeAsyncPhysicsTick == false", ToolTip=
			"Ticks the component from Chaos physics substeps using a PreIntegrate sim callback. This runs on the physics thread, so ReceivedTick implementations must not touch game-thread-only state."))
	bool UsePhysicsCallbackTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Joystick|Force Feedback",
		meta=(ToolTip="Uses the component tick to drive the Effect tick, rather than the effect ticking itself. Useful if you want to control the Tick Interval and Tick Group of the effects."))
	bool OverrideEffectTick;
};
