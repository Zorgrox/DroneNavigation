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
  // first, find the drone. We currently assume that there is only one of them.
  std::cout << "Scheduling the delivery" << std::endl;
  Drone* actual_drone = NULL;
  Customer* actual_customer = NULL;
  for (IEntity* ent : entities_) {
    actual_drone = dynamic_cast<Drone *>(ent);
    if(actual_drone) {
      break;
    }
  }
  for (IEntity *ent : entities_)
  {
    actual_customer = dynamic_cast<Customer *>(ent);
    if (actual_customer)
    {
      break;
    }
  }
  // if (!actual_drone->GetOnTheWayToPickUpPackage() && !actual_drone->GetOnTheWayToDropOffPackage())
  // {
  // Set the package for the drone
  Package* actual_package = dynamic_cast<Package*>(package);
  actual_package->SetCustomer(*actual_customer);
  actual_drone->SetCurPackage(*actual_package);
  // get the path and set it to the delivery simulation's curRoute
  std::vector<float> drones_position = actual_drone->GetPosition();
  std::vector<float> packages_position = actual_package->GetPosition();
  curRoute = systemGraph->GetPath(drones_position, packages_position);
  std::cout << "I'm done with GetPath" << std::endl;
  PrintPath(curRoute);
  curRouteNextIndex = 1;
  curRouteLength = curRoute.size();
  actual_drone->SetOnTheWayToPickUpPackage(true);
  actual_drone->SetOnTheWayToDropOffPackage(false);
  std::cout << "Done with schedule delivery" << std::endl;

  // Notify the observers that the package has been scheduled
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "notify");
  JsonHelper::AddStringToJsonObject(obj, "value", "scheduled");
  picojson::value val = JsonHelper::ConvertPicojsonObjectToValue(obj);

  for (IEntityObserver* obs : observers_) {
    obs->OnEvent(val, *package);
  }
  // }
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
  observers_.push_back(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
  // int idx_to_erase = -1;
  // int idx = 0;
  // for (IEntityObserver* obs : observers_)
  // {
  //   if (obs == observer) {
  //     idx_to_erase = idx;
  //   }
  //   idx = idx + 1;
  // }

  // if (idx_to_erase != -1) {
  //   observers_.erase(idx_to_erase);
  // }
  observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
  if (GetEntities().size() > 0 ) {
    Drone *actual_drone = NULL;
    for (IEntity *ent : entities_)
    {
      actual_drone = dynamic_cast<Drone *>(ent);
      if (actual_drone)
      {
        break;
      }
    }

    if (actual_drone->GetOnTheWayToPickUpPackage() && !actual_drone->GetOnTheWayToDropOffPackage())
    {
      std::cout << "I'm on the way to pick up the package" << std::endl;
      // The drone is on the way to pick up a package.
      if (actual_drone->CheckReadyToPickUp())
      {
        actual_drone->PickUpPackage();
        // Update the path so that it's now pointed towards the customer's location
        curRoute = systemGraph->GetPath(actual_drone->GetPosition(), actual_drone->GetCurPackage()->GetDestination());
        curRouteNextIndex = 1;
        std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
        actual_drone->CalculateAndUpdateDroneDirection(nextPos);
        std::cout << "This is Drone's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
        actual_drone->SetOnTheWayToPickUpPackage(false);
        actual_drone->SetOnTheWayToDropOffPackage(true);
        std::cout << "Switching over to dropping package off" << std::endl;

        // Notify the observers that the package has been picked up
        picojson::object obj = JsonHelper::CreateJsonObject();
        JsonHelper::AddStringToJsonObject(obj, "type", "notify");
        JsonHelper::AddStringToJsonObject(obj, "value", "en route");
        picojson::value val = JsonHelper::ConvertPicojsonObjectToValue(obj);

        for (IEntityObserver *obs : observers_)
        {
          const IEntity* temp_pkg = actual_drone->GetCurPackage();
          obs->OnEvent(val, *temp_pkg);
        }

      } else {
        if (actual_drone->CheckWhenToIncrementPathIndex(curRoute.at(curRouteNextIndex)))
        {
          // We should only increment the path index when the drone gets close enough to it that we should be going to the next one
          std::cout << "I'M JUST INCREMENTING THE PATH INDEX ON THE WAY TO PICK UP THE PACKAGE" << std::endl;
          curRouteNextIndex = curRouteNextIndex + 1;
          std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
          std::cout << "This is Drone's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
          actual_drone->CalculateAndUpdateDroneDirection(nextPos);
        } else {
          // We don't need to increment the path index yet
          std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
          std::cout << "This is Drone's position to go to next in the path in DeliverySimulation Update: {" << nextPos.at(0) << ", " << nextPos.at(1) << ", " << nextPos.at(2) << "}" << std::endl;
          actual_drone->CalculateAndUpdateDroneDirection(nextPos);
        }
      }
      actual_drone->Update(dt);
    }

    else if (!actual_drone->GetOnTheWayToPickUpPackage() && actual_drone->GetOnTheWayToDropOffPackage())
    {
      std::cout << "I'm on the way to drop off the package" << std::endl;
      if (actual_drone->CheckReadyToDropOff())
      {
        // Move the package out of the simulation to remove it
        curRouteNextIndex = 1;
        actual_drone->DropOffPackage();

        // Notify the observers that the package has been dropped off
        picojson::object obj = JsonHelper::CreateJsonObject();
        JsonHelper::AddStringToJsonObject(obj, "type", "notify");
        JsonHelper::AddStringToJsonObject(obj, "value", "delivered");
        picojson::value val = JsonHelper::ConvertPicojsonObjectToValue(obj);

        for (IEntityObserver *obs : observers_)
        {
          const IEntity* temp_pkg = actual_drone->GetCurPackage();
          obs->OnEvent(val, *temp_pkg);
        }

      }
      else {
        if (actual_drone->CheckWhenToIncrementPathIndex(curRoute.at(curRouteNextIndex)))
        {
          curRouteNextIndex = curRouteNextIndex + 1;
          std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
          actual_drone->CalculateAndUpdateDroneDirection(nextPos);
        } else {
          // We don't need to increment the path index yet
          std::vector<float> nextPos = curRoute.at(curRouteNextIndex);
          actual_drone->CalculateAndUpdateDroneDirection(nextPos);
        }
        actual_drone->Update(dt);
      }
    }

    // print out the drone's positions at each time step
    std::vector<float> theCurPos = actual_drone->GetPosition();
    Print(theCurPos);
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
