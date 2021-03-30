#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"
#include <EntityProject/entity.h>
#include "composite_factory.h"
#include "package_factory.h"
#include "customer_factory.h"
#include "drone_factory.h"
#include "package.h"
#include "customer.h"

#include <iostream>

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
  compositeFactory_ = new CompositeFactory();
}

DeliverySimulation::~DeliverySimulation() {}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
  IEntity* newEntity = compositeFactory_->CreateEntity(val);
  if (newEntity) {
    return newEntity;
  } else {
    std::cout << "The newEntity is null in deliverySimulation CreateEntity" << std::endl;
  }
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {}

void DeliverySimulation::AddEntity(IEntity* entity) {
  entities_.push_back(entity);
  Drone* maybe_drone = dynamic_cast<Drone *>(entity);
  if (maybe_drone) {
    drones_.push_back(maybe_drone);
  }
  // TODO: also add any robots to a robots vector

  Customer* maybe_customer = dynamic_cast<Customer *>(entity);
  if (maybe_customer) {
    customers_.push_back(maybe_customer);
  }
  Package* maybe_package = dynamic_cast<Package *>(entity);
  if (maybe_package) {
    packages_.push_back(maybe_package);
  }
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
  systemGraph = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
  /**
  This function tells the simulation that the IEntity* package should be delivered
  to the IEntity* dest (which is likely a customer). How the delivery takes place
  is entirely dependent on how you design your code, but it should involve a drone
  navigating to the package, picking it up, and then moving to the customer and
  dropping the package.
  */
  std::cout << "Scheduling the delivery" << std::endl;

  Package* actual_package = dynamic_cast<Package*>(package);
  Customer* actual_customer = dynamic_cast<Customer*>(dest);
  actual_package->SetCustomer(*actual_customer);

  Drone* actual_drone = drones_.at(dronesIndex);
  if(actual_drone) {
    actual_drone->AddAssignedPackage(*actual_package);

    if (actual_drone->GetNumAssignedPackages() == 1) {
      // assign the curPackage if it's the first one assigned to the drone
      actual_drone->UpdateCurPackage();
      // get the path and set it to the delivery simulation's curRoute
      std::vector<float> drones_position = actual_drone->GetPosition();
      std::vector<float> packages_position = actual_package->GetPosition();
      std::vector<std::vector<float>> anotherRoute = systemGraph->GetPath(drones_position, packages_position);
      actual_drone->SetNewCurRoute(anotherRoute);
      actual_drone->SetOnTheWayToPickUpPackage(true);
      actual_drone->SetOnTheWayToDropOffPackage(false);
    }
  }
  dronesIndex = dronesIndex + 1;
  if (dronesIndex > drones_.size()) {
    dronesIndex = 0;
  }
  // TODO: if it's a robot, do the same thing as above here
  std::cout << "Done with schedule delivery" << std::endl;
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
  // std::cout << "This is dt in DeliverySimulation::Update: " << dt << std::endl;
  if (GetEntities().size() > 0 ) {
    for (Drone* actual_drone : drones_) {
      actual_drone->Update(systemGraph, dt);
      // print out the drone's positions at each time step
      std::vector<float> theCurPos = actual_drone->GetPosition();
      Print(theCurPos);
    }
    // TODO: also do for robot
  }
}

void DeliverySimulation::Print(std::vector<float> &vectorOutput)
{
  std::cout << "{";
  for (int i = 0; i < vectorOutput.size(); i++)
  {
    std::cout << vectorOutput.at(i);
    if (i != vectorOutput.size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << "}" << std::endl;
}

void DeliverySimulation::PrintPath(std::vector<std::vector<float>> &vectorOutput)
{
  std::cout << "This is the path:" << std::endl;
  for (int j = 0; j < vectorOutput.size(); j++)
  {
    std::cout << "{";
    std::vector<float> intermediateVector = vectorOutput.at(j);
    for (int i = 0; i < intermediateVector.size(); i++)
    {
      std::cout << intermediateVector.at(i);
      if (i != intermediateVector.size() - 1)
      {
        std::cout << ", ";
      }
    }
    std::cout << "}" << std::endl;
  }
}

// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
        std::cout << "pkg_index=" << pkg_index << std::endl;
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
        std::cout << "dest_index=" << dest_index << std::endl;
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
          if (pkg) {
            std::cout << "pkg exists in scheduleDelivery" << std::endl;
          } else {
            std::cout << "pkg does not exist in scheduleDelivery" << std::endl;
          }
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
              std::cout << "I'm actually going to schedule the delivery" << std::endl;
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
