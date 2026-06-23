// JoystickPlugin is licensed under the MIT License.
// Copyright Jayden Maalouf 2026. All Rights Reserved.

#pragma once

#if WITH_EDITOR

#include "IPropertyTypeCustomization.h"

struct FJoystickInformation;

class FJoystickInformationCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FJoystickInformationCustomization);
	}

	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	bool IsConnectedDeviceArrayItem(const TSharedRef<IPropertyHandle>& StructPropertyHandle) const;
	FText GetConnectedDeviceDisplayName(const TSharedRef<IPropertyHandle>& StructPropertyHandle) const;
	const FJoystickInformation* GetJoystickInformation(const TSharedRef<IPropertyHandle>& StructPropertyHandle) const;
};

#endif
