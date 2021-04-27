#include <EntityProject/project_settings.h>
#include <string>
#include "../../include/delivery_simulation.h"

extern "C" {
  entity_project::IEntitySystem* GetEntitySystem(const std::string& id) {
        return new csci3081::DeliverySimulation();
  }
}
