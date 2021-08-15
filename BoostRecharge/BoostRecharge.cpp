#include "pch.h"
#include "BoostRecharge.h"


BAKKESMOD_PLUGIN(BoostRecharge, "Boost Recharge", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

// no boost recharge   = 0.0
// slow boost recharge = 0.0666
// fast boost recharge = 0.1666
float blueRate = 0.0;
float orangeRate = 0.0;

// no boost recharge   = 0.0
// slow boost recharge = 2.0
// fast boost recharge = 2.0
float blueDelay = 0.0;
float orangeDelay = 0.0;

void BoostRecharge::onLoad()
{
	_globalCvarManager = cvarManager;

	cvarManager->registerCvar("boost_enable", "0", "Enables plugin")
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			if (cvar.getBoolValue()) {
				hookEvents();
			} else {
				unHookEvents();
			}
			});

	cvarManager->registerCvar("boost_rate_orange", "0.0", "Orange team's boost regen rate")
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			orangeRate = cvar.getFloatValue();
			setBoostValues();
			});

	cvarManager->registerCvar("boost_delay_orange", "0.0", "Orange team's boost regen delay")
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			orangeDelay = cvar.getFloatValue();
			setBoostValues();
			});

	cvarManager->registerCvar("boost_rate_blue", "0.0", "Blue team's boost regen rate")
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			blueRate = cvar.getFloatValue();
			setBoostValues();
			});

	cvarManager->registerCvar("boost_delay_blue", "0.0", "Blue team's boost regen delay")
		.addOnValueChanged([this](std::string, CVarWrapper cvar) {
			blueDelay = cvar.getFloatValue();
			setBoostValues();
			});
}

void BoostRecharge::onUnload() {
}

void BoostRecharge::hookEvents() {
	gameWrapper->HookEventPost("Function TAGame.GameEvent_TA.AddCar", [this](...) { setBoostValues(); });
}

void BoostRecharge::unHookEvents() {
	gameWrapper->UnhookEventPost("Function TAGame.GameEvent_TA.AddCar");
}


void BoostRecharge::setBoostValues() {
	ServerWrapper sw = gameWrapper->GetCurrentGameState();

	if (gameWrapper->IsInOnlineGame() || !gameWrapper->IsInGame()) {
		return;
	}

	if (!sw) {
		return;
	}

	auto cars = sw.GetCars();

	for (CarWrapper car : cars) {
		if (!car) {
			return;
		}

		BoostWrapper boost = car.GetBoostComponent();

		if (!boost) {
			return;
		}

		if (car.GetTeamNum2() == 0) {
			boost.SetRechargeDelay2(blueDelay);
			boost.SetRechargeRate2(blueRate);
		} else {
			boost.SetRechargeDelay2(orangeDelay);
			boost.SetRechargeRate2(orangeRate);
		}
	}
}