// JoystickPlugin is licensed under the MIT License.
// Copyright Jayden Maalouf 2026. All Rights Reserved.

#include "JoystickPluginEditorModule.h"

#include "ISettingsModule.h"
#include "JoystickInputSettings.h"
#include "JoystickPluginSettingsDetails.h"
#include "PropertyEditorDelegates.h"
#include "PropertyEditorModule.h"
#include "ToolMenus.h"
#include "Customization/JoystickInformationCustomization.h"
#include "Customization/JoystickInputDeviceConfigurationCustomization.h"
#include "Customization/JoystickInstanceIdCustomization.h"
#include "Data/Settings/JoystickInputDeviceConfiguration.h"
#include "Menus/JoystickInputViewer.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "JoystickPluginEditor"

static const FName JoystickViewerTabId(TEXT("JoystickInputViewer"));

void FJoystickPluginEditorModule::StartupModule()
{
	RegisterSettings();
	RegisterPropertyLayout();

	FGlobalTabmanager::Get()
		->RegisterNomadTabSpawner(
			JoystickViewerTabId,
			FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& SpawnTabArgs) -> TSharedRef<SDockTab>
			{
				const TSharedRef<SDockTab> DockTab =
					SNew(SDockTab)
					.TabRole(NomadTab);

				const TSharedRef<SJoystickInputViewer> Frontend =
					SNew(SJoystickInputViewer, DockTab, SpawnTabArgs.GetOwnerWindow());

				DockTab->SetContent(Frontend);
				return DockTab;
			})
		)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.PadEvent_16x"))
		.SetDisplayName(FText::FromString("Joystick Viewer"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FJoystickPluginEditorModule::RegisterMenus));

	IModuleInterface::StartupModule();
}

void FJoystickPluginEditorModule::ShutdownModule()
{
	FGlobalTabmanager::Get()->UnregisterTabSpawner(JoystickViewerTabId);

	if (UToolMenus::IsToolMenuUIEnabled())
	{
		UToolMenus::UnRegisterStartupCallback(this);
	}

	UnregisterSettings();
	UnregisterPropertyLayout();

	IModuleInterface::ShutdownModule();
}

void FJoystickPluginEditorModule::RegisterMenus() const
{
	UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
	FToolMenuSection& Section = ToolsMenu->FindOrAddSection("Tools");
	Section.AddMenuEntry(
		"OpenJoystickViewer",
		FText::FromString("Joystick Viewer"),
		FText::FromString("Open the Joystick Input Viewer tab."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "GraphEditor.PadEvent_16x"),
		FUIAction(FExecuteAction::CreateLambda([]
		{
			FGlobalTabmanager::Get()->TryInvokeTab(JoystickViewerTabId);
		}))
	);
}

static FName SettingsSection = TEXT("Joystick Input");

void FJoystickPluginEditorModule::RegisterSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Engine", SettingsSection,
		                                 LOCTEXT("JoystickInputSettingsName", "Joystick Input"),
		                                 LOCTEXT("JoystickInputSettingsDescription", "Configure Joystick Input"), GetMutableDefault<UJoystickInputSettings>());
	}
}

void FJoystickPluginEditorModule::RegisterPropertyLayout() const
{
	if (FPropertyEditorModule* PropertyModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{
		PropertyModule->RegisterCustomClassLayout(UJoystickInputSettings::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FJoystickPluginSettingsDetails::MakeInstance));
		PropertyModule->RegisterCustomPropertyTypeLayout(FJoystickInputDeviceConfiguration::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FJoystickInputDeviceConfigurationCustomization::MakeInstance));
		PropertyModule->RegisterCustomPropertyTypeLayout(FJoystickInformation::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FJoystickInformationCustomization::MakeInstance));
		PropertyModule->RegisterCustomPropertyTypeLayout(FJoystickInstanceId::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FJoystickInstanceIdCustomization::MakeInstance));
	}
}

void FJoystickPluginEditorModule::UnregisterSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Engine", SettingsSection);
	}
}

void FJoystickPluginEditorModule::UnregisterPropertyLayout() const
{
	if (FPropertyEditorModule* PropertyModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{
		PropertyModule->UnregisterCustomClassLayout(UJoystickInputSettings::StaticClass()->GetFName());
		PropertyModule->UnregisterCustomPropertyTypeLayout(FJoystickInputDeviceConfiguration::StaticStruct()->GetFName());
		PropertyModule->UnregisterCustomPropertyTypeLayout(FJoystickInformation::StaticStruct()->GetFName());
		PropertyModule->UnregisterCustomPropertyTypeLayout(FJoystickInstanceId::StaticStruct()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FJoystickPluginEditorModule, JoystickPluginEditor)
