#include "delivery_simulation.h"
#include <EntityProject/entity_factory.h>
#include "composite_factory.h"
#include "drone_factory.h"
#include "customer_factory.h"
#include "package_factory.h"
#include <iostream>
#include "json_helper.h"
#include "robot_factory.h"

namespace csci3081
{
  CompositeFactory::CompositeFactory() {
    DroneFactory* droneFactory = new DroneFactory();
    RobotFactory* robotFactory = new RobotFactory();
    CustomerFactory* customerFactory = new CustomerFactory();
    PackageFactory* packageFactory = new PackageFactory();

    AddFactory(*droneFactory);
    AddFactory(*robotFactory);
    AddFactory(*customerFactory);
    AddFactory(*packageFactory);
  }

  CompositeFactory::~CompositeFactory() {
    for (IEntityFactory* factory : factories) {
      delete factory;
    }
    // delete[] factories;
  }

  IEntity*CompositeFactory::CreateEntity(const picojson::object &val) {
    std::string type = JsonHelper::GetString(val, "type");
    std::cout << "This is the type we want created: " << type << std::endl;
    int i = 0;
    for (IEntityFactory* factory : factories) {
      if(types_list.at(i) == type) {
        IEntity* newEntity = factory->CreateEntity(val);
        if (newEntity) {
          std::cout << "This is the " << type << "'s id in CreateEntity: " << newEntity->GetId() << std::endl;
          return newEntity;
        } else {
          std::cout << "The newEntity is null" << std::endl;
        }
      }
      i = i + 1;
    }
    std::cout << "The Entity was not actually created in CompositeFactory CreateEntity" << std::endl;
    return NULL;
  }

  void CompositeFactory::AddFactory(IEntityFactory &factory) {
    factories.push_back(&factory);
  }
}
