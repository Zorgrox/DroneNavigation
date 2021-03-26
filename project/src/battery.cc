#include "battery.h"
#include <vector>
#include <string>

namespace csci3081
{
  Battery::Battery(float maxCharge) {
    maxBatteryCharge = maxCharge;
    currentCharge = maxCharge;
    if (currentCharge > 0) {
      isEmpty = false;
    } else {
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
    currentCharge = currentCharge - decrAmount;
    if (currentCharge == 0) {
      isEmpty = true;
    }
  }

  bool Battery::GetIsEmpty() const {
    return isEmpty;
  }

} // namespace csci3081
