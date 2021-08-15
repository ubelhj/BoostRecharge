#include "pch.h"
#include "BoostRecharge.h"

std::string BoostRecharge::GetPluginName() {
	return "Boost Recharge";
}

void BoostRecharge::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> BoostRecharge
void BoostRecharge::RenderSettings() {
	ImGui::TextUnformatted("Custom boost recharge per team!");

	CVarWrapper enableCvar = cvarManager->getCvar("boost_enable");
	if (!enableCvar) { return; }
	bool enabled = enableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable Plugin", &enabled)) {
		gameWrapper->Execute([this, enableCvar, enabled](...) mutable { enableCvar.setValue(enabled); });
	}

	ImGui::NewLine();

	CVarWrapper blueRateCvar = cvarManager->getCvar("boost_rate_blue");
	if (!blueRateCvar) { return; }
	float blueRate = blueRateCvar.getFloatValue();

	CVarWrapper blueDelayCvar = cvarManager->getCvar("boost_delay_blue");
	if (!blueDelayCvar) { return; }
	float blueDelay = blueDelayCvar.getFloatValue();

	CVarWrapper orangeRateCvar = cvarManager->getCvar("boost_rate_orange");
	if (!orangeRateCvar) { return; }
	float orangeRate = orangeRateCvar.getFloatValue();

	CVarWrapper orangeDelayCvar = cvarManager->getCvar("boost_delay_orange");
	if (!orangeDelayCvar) { return; }
	float orangeDelay = orangeDelayCvar.getFloatValue();
	
	ImGui::Separator();
	ImGui::Columns(2);

	ImGui::TextUnformatted("Blue Team");

	if (ImGui::Button("No Recharge##blue")) {
		gameWrapper->Execute([this, blueDelayCvar, blueRateCvar](...) mutable { 
			blueDelayCvar.setValue((float) 0.0); 
			blueRateCvar.setValue((float) 0.0);
			});
	}

	ImGui::SameLine();

	if (ImGui::Button("Slow Recharge##blue")) {
		gameWrapper->Execute([this, blueDelayCvar, blueRateCvar](...) mutable {
			blueDelayCvar.setValue((float)2.0);
			blueRateCvar.setValue((float)0.0666);
			});
	}

	ImGui::SameLine();

	if (ImGui::Button("Fast Recharge##blue")) {
		gameWrapper->Execute([this, blueDelayCvar, blueRateCvar](...) mutable {
			blueDelayCvar.setValue((float)2.0);
			blueRateCvar.setValue((float)0.1666);
			});
	}

	if (ImGui::SliderFloat("Boost Delay##blue", &blueDelay, 0.0, 5.0)) {
		gameWrapper->Execute([this, blueDelayCvar, blueDelay](...) mutable { blueDelayCvar.setValue(blueDelay); });
	}

	if (ImGui::SliderFloat("Boost Rate##blue", &blueRate, 0.0, 0.5)) {
		gameWrapper->Execute([this, blueRateCvar, blueRate](...) mutable { blueRateCvar.setValue(blueRate); });
	}

	ImGui::NextColumn();

	ImGui::TextUnformatted("Orange Team");

	if (ImGui::Button("No Recharge##orange")) {
		gameWrapper->Execute([this, orangeDelayCvar, orangeRateCvar](...) mutable {
			orangeDelayCvar.setValue((float)0.0);
			orangeRateCvar.setValue((float)0.0);
			});
	}

	ImGui::SameLine();

	if (ImGui::Button("Slow Recharge##orange")) {
		gameWrapper->Execute([this, orangeDelayCvar, orangeRateCvar](...) mutable {
			orangeDelayCvar.setValue((float)2.0);
			orangeRateCvar.setValue((float)0.0666);
			});
	}

	ImGui::SameLine();

	if (ImGui::Button("Fast Recharge##orange")) {
		gameWrapper->Execute([this, orangeDelayCvar, orangeRateCvar](...) mutable {
			orangeDelayCvar.setValue((float)2.0);
			orangeRateCvar.setValue((float)0.1666);
			});
	}

	if (ImGui::SliderFloat("Boost Delay##orange", &orangeDelay, 0.0, 5.0)) {
		gameWrapper->Execute([this, orangeDelayCvar, orangeDelay](...) mutable { orangeDelayCvar.setValue(orangeDelay); });
	}

	if (ImGui::SliderFloat("Boost Rate##orange", &orangeRate, 0.0, 0.5)) {
		gameWrapper->Execute([this, orangeRateCvar, orangeRate](...) mutable { orangeRateCvar.setValue(orangeRate); });
	}

	ImGui::Columns(1);

	ImGui::Separator();

	ImGui::TextUnformatted("Plugin commissioned by Lethamyr");
	ImGui::TextUnformatted("youtube.com/c/Lethamyr");
	ImGui::TextUnformatted("Plugin made by JerryTheBee#1117 - DM me on discord for custom plugin commissions!");
}

/*
// Do ImGui rendering here
void BoostRecharge::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string BoostRecharge::GetMenuName()
{
	return "BoostRecharge";
}

// Title to give the menu
std::string BoostRecharge::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void BoostRecharge::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool BoostRecharge::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool BoostRecharge::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void BoostRecharge::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void BoostRecharge::OnClose()
{
	isWindowOpen_ = false;
}
*/
