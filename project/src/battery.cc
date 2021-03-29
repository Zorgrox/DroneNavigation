#include "battery.h"
#include <vector>
#include <string>

namespace csci3081
{
  Battery::Battery(float maxCharge) {
    if (maxCharge > 0) {
      maxBatteryCharge = maxCharge;
      currentCharge = maxCharge; }
    else
    {
    maxBatteryCharge = 10000;  // Default value
      currentCharge = maxCharge;
    }
    if (currentCharge > 0) {
      isEmpty = false;
    } else {
      isEmpty = true;
    }
  }

  Battery::Battery(float maxCharge, float currentCharg) {
    if (maxCharge > 0) {
      maxBatteryCharge = maxCharge;
    }
    else
    {
    maxBatteryCharge = 10000;  // Default value
    }

    if (currentCharg > 0) {
	    currentCharge=currentCharg;
      isEmpty = false;
    } else {
	    currentCharge=currentCharg;
      isEmpty = true;
    }
  }



  float Battery::GetMaxCharge() const {
    return maxBatteryCharge;
  }

  float Battery::GetCurrentCharge() const {
    return currentCharge;
  }

  void Battery::DecrementCurrentCharge(float decrAmount) {
    if (currentCharge>0) {
	    currentCharge = currentCharge - decrAmount;
    }
	  if (currentCharge == 0) {
      isEmpty = true;
    }
  }

  bool Battery::GetIsEmpty() const {
    return isEmpty;
  }

} // namespace csci3081
