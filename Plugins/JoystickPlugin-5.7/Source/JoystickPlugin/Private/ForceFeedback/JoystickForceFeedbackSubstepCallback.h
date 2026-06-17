// JoystickPlugin is licensed under the MIT License.
// Copyright Jayden Maalouf 2026. All Rights Reserved.

#pragma once

#include "UObject/WeakObjectPtr.h"
#include "Chaos/SimCallbackObject.h"

class UJoystickForceFeedbackComponent;

class FJoystickForceFeedbackSubstepCallback final
	: public Chaos::TSimCallbackObject<
		Chaos::FSimCallbackNoInput,
		Chaos::FSimCallbackNoOutput>
{
public:
	void Init(UJoystickForceFeedbackComponent* InComponent);

private:
	virtual void OnPreSimulate_Internal() override;
	virtual FName GetFNameForStatId() const override;

	TWeakObjectPtr<UJoystickForceFeedbackComponent> Component;
};
