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
#include "entity_base.h"
#include "robot_factory.h"
#include "robot.h"
#include "decorated_entity.h"

#include <iostream>

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
  compositeFactory_ = new CompositeFactory();
}

DeliverySimulation::~DeliverySimulation() {
  delete compositeFactory_;
  for (IEntity* e : entities_) {
    delete e;
  }
  entities_.clear();
  for (Drone* d : drones_) {
    delete d;
  }
  drones_.clear();
  for (Robot* r : robots_) {
    delete r;
  }
  robots_.clear();
  for (Customer* c : customers_) {
    delete c;
  }
  customers_.clear();
  for (Package* p : packages_) {
    delete p;
  }
  packages_.clear();
  for (IEntityObserver* o : observers_) {
    delete o;
  }
  observers_.clear();
  for (Drone* d : dead_drones_with_remaining_packages_) {
    delete d;
  }
  dead_drones_with_remaining_packages_.clear();
  for(Robot* r : dead_robots_with_remaining_packages_) {
    delete r;
  }
  dead_robots_with_remaining_packages_.clear();
  for (Package* p : packages_to_be_scheduled_) {
    delete p;
  }
  packages_to_be_scheduled_.clear();

}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
  IEntity* newEntity = compositeFactory_->CreateEntity(val);
  if (newEntity) {
	  dynamic_cast<EntityBase*> (newEntity)->SetId(DelivIDs);
	  //Provides the entity with a unique ID
	  DelivIDs = DelivIDs + 1;
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
  Robot* maybe_robot = dynamic_cast<Robot *>(entity);
  if (maybe_robot) {
    robots_.push_back(maybe_robot);
  }
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

  int droneCounter = 0;
  bool packageMustNotBeDrones = false;
  while (std::count(dead_drones_indices.begin(), dead_drones_indices.end(), dronesIndex)) {
    // while the dronesIndex is in the dead_drones_indices, increment the dronesIndex
    dronesIndex = dronesIndex + 1;
    if (dronesIndex == drones_.size()) {
      dronesIndex = 0;
    }
    droneCounter = droneCounter + 1;
    // we want to avoid an infinite loop, if all of the drones are out of battery
    if (droneCounter >= drones_.size()) {
      // we've already looped through them all, so none of the drones have battery, set assignPackageToDrone to false and break
      packageMustNotBeDrones = true;
      break;
    }
  }

  int robotCounter = 0;
  bool packageMustNotBeRobots = false;
  while (std::count(dead_robots_indices.begin(), dead_robots_indices.end(), robotsIndex))
  {
    robotsIndex = robotsIndex + 1;
    if (robotsIndex == robots_.size())
    {
      robotsIndex = 0;
    }
    robotCounter = robotCounter + 1;
    // we want to avoid an infinite loop, if all of the robots are out of battery
    if (robotCounter >= robots_.size())
    {
      // we've already looped through them all, so none of the robots have battery
      packageMustNotBeRobots = true;
      break;
    }
  }

  if (!packageMustNotBeDrones && !packageMustNotBeRobots) {
    // there is at least one drone and one robot that has battery
    if (drones_.size() > 0 && robots_.size() > 0)
    {
      if (drones_.at(dronesIndex)->GetNumAssignedPackages() <= robots_.at(robotsIndex)->GetNumAssignedPackages())
      {
        assignPackageToDrone = true;
      }
      else
      {
        assignPackageToDrone = false;
      }
    } else if (drones_.size() > 0 && robots_.size() == 0) {
      assignPackageToDrone = true;
    } else if (drones_.size() == 0 && robots_.size() > 0) {
      assignPackageToDrone = false;
    }
  }
  else if (packageMustNotBeDrones && !packageMustNotBeRobots) {
    // the package must be assigned to a robot
    assignPackageToDrone = false;
  }
  else if (!packageMustNotBeDrones && packageMustNotBeRobots) {
    // the package must be assigned to a drone
    assignPackageToDrone = true;
  }
  else {
    std::cout << "WARNING: none of the drones or robots have battery. The package cannot be scheduled" << std::endl;
  }

  if (assignPackageToDrone) {
    std::cout << "Assigning to Drone\n" << std::endl;
    Drone* actual_drone = drones_.at(dronesIndex);
    if(actual_drone) {
      actual_drone->AddAssignedPackage(*actual_package);
      do {
        if (actual_drone->GetNumAssignedPackages() == 1) {
          // assign the curPackage if it's the first one assigned to the drone
          actual_drone->UpdateCurPackage();
          // get the path and set it to the delivery simulation's curRoute
          std::vector<float> drones_position = actual_drone->GetPosition();
          std::vector<float> packages_position = actual_package->GetPosition();
		      actual_drone->SetFlightBehavior(drones_position, packages_position, const_cast<IGraph*>(systemGraph));
		      //SetFlightBehavior now sets the route for the drone
          actual_drone->SetOnTheWayToPickUpPackage(true);
          actual_drone->SetOnTheWayToDropOffPackage(false);
        }
      } while (actual_drone->GetNumAssignedPackages() == 0);
    }
    dronesIndex = dronesIndex + 1;
    if (dronesIndex == drones_.size()) {
      dronesIndex = 0;
    }
  }
  else {
    std::cout << "Assigning to Robot\n" << std::endl;
    Robot *actual_robot = robots_.at(robotsIndex);
    if (actual_robot)
    {
      actual_robot->AddAssignedPackage(*actual_package);
      std::cout << "num assigned packages: " << actual_robot->GetNumAssignedPackages() << std::endl;
      if (actual_robot->GetCurPackage() == NULL) {std::cout << "nopackage_____\n";}
      if (actual_robot->GetNumAssignedPackages() == 1)
      {
        // assign the curPackage if it's the first one assigned to the drone
        actual_robot->UpdateCurPackage();
        // get the path and set it to the delivery simulation's curRoute
        std::vector<float> robots_position = actual_robot->GetPosition();
        std::vector<float> packages_position = actual_package->GetPosition();
        std::vector<std::vector<float>> anotherRoute = systemGraph->GetPath(robots_position, packages_position);
        actual_robot->SetNewCurRoute(anotherRoute);
        actual_robot->SetOnTheWayToPickUpPackage(true);
        actual_robot->SetOnTheWayToDropOffPackage(false);
      }
    }
    robotsIndex = robotsIndex + 1;
    if (robotsIndex == robots_.size())
    {
      robotsIndex = 0;
    }
  }
  std::cout << "Done with schedule delivery" << std::endl;

  // Notify the observers that the package has been scheduled
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "notify");
  JsonHelper::AddStringToJsonObject(obj, "value", "scheduled");
  picojson::value val = JsonHelper::ConvertPicojsonObjectToValue(obj);

  for (IEntityObserver* obs : observers_) {
    obs->OnEvent(val, *package);
  }
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
  observers_.push_back(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
  observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
  if (GetEntities().size() > 0 ) {
    int drone_idx = 0;
    for (Drone* actual_drone : drones_) {
      if (actual_drone->GetBattery()->GetIsEmpty() == false) {
        DecoratedEntity* decorated_drone = new DecoratedEntity(dynamic_cast<EntityBase*>(actual_drone));
        decorated_drone->Update(systemGraph, observers_, dt);
        if (actual_drone->GetBattery()->GetIsEmpty() == true) {
          // add the drone with empty battery to the list of dead drones in the delivery simulation
          dead_drones_with_remaining_packages_.push_back(actual_drone);
          dead_drones_indices.push_back(drone_idx);
        }
      }
      drone_idx = drone_idx + 1;
    }
    int robot_idx = 0;
    for (Robot* actual_robot : robots_) {
      if (actual_robot->GetBattery()->GetIsEmpty() == false) {
	DecoratedEntity* decorated_robot = new DecoratedEntity(dynamic_cast<EntityBase*>(actual_robot));
        decorated_robot->Update(systemGraph, observers_, dt);
        if (actual_robot->GetBattery()->GetIsEmpty() == true) {
          // add the robot with empty battery to the list of dead robots in the delivery simulation
          dead_robots_with_remaining_packages_.push_back(actual_robot);
          dead_robots_indices.push_back(robot_idx);
        }
      }
    }
    // check the two different dead drones/robots are of length > 0
    if (dead_drones_with_remaining_packages_.size() > 0) {
      // iterate through the packages carried by this drone in order to schedule it to a different entity
      // first check which packages are remaining
      for (Drone* dead_drone : dead_drones_with_remaining_packages_) {
        std::vector<Package*> drone_packages_to_be_scheduled = dead_drone->GetRemainingAssignedPackages();
        drone_packages_to_be_scheduled.push_back(dead_drone->GetCurPackage());
        packages_to_be_scheduled_.insert(packages_to_be_scheduled_.end(), drone_packages_to_be_scheduled.begin(), drone_packages_to_be_scheduled.end());
      }
    }
    if (dead_robots_with_remaining_packages_.size() > 0) {
      // iterate through the packages carried by this drone in order to schedule it to a different entity
      for (Robot *dead_robot : dead_robots_with_remaining_packages_)
      {
        std::vector<Package *> robot_packages_to_be_scheduled = dead_robot->GetRemainingAssignedPackages();
        packages_to_be_scheduled_.insert(packages_to_be_scheduled_.end(), robot_packages_to_be_scheduled.begin(), robot_packages_to_be_scheduled.end());
      }
    }
    if (packages_to_be_scheduled_.size() > 0) {
      // now reschedule these packages
      for (Package * reschedule_package : packages_to_be_scheduled_) {
        IEntity* reschedule_customer = dynamic_cast<IEntity*>(reschedule_package->GetCustomer());
        ScheduleDelivery(reschedule_package, reschedule_customer);
        std::cout << "I'm rescheduling the dropped package!" << std::endl;
      }
      // now clear the packages_to_be_scheduled_ vector
    }
    packages_to_be_scheduled_.clear();
    // clear it since we just check the size of this list when determining whether to add dead_packages
    // later, if we add in battery checking stations, this logic will have to be changed
    dead_drones_with_remaining_packages_.clear();
    dead_robots_with_remaining_packages_.clear();
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
