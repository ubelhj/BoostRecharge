#include "pch.h"
#include "BoostRecharge.h"


BAKKESMOD_PLUGIN(BoostRecharge, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

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

	
	
}

void BoostRecharge::onUnload()
{
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