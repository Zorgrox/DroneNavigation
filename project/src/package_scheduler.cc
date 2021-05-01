#include "package_scheduler.h"
#include "json_helper.h"

namespace csci3081
{

  PackageScheduler::PackageScheduler() {
  }

  void PackageScheduler::ScheduleDelivery(IEntity* package, IEntity* dest)
  {
    /**
  This function tells the simulation that the IEntity* package should be delivered
  to the IEntity* dest (which is likely a customer). How the delivery takes place
  is entirely dependent on how you design your code, but it should involve a drone
  navigating to the package, picking it up, and then moving to the customer and
  dropping the package.
  */
    std::cout << "Scheduling the delivery" << std::endl;

    Package *actual_package = dynamic_cast<Package *>(package);
    Customer *actual_customer = dynamic_cast<Customer *>(dest);
    actual_package->SetCustomer(*actual_customer);

    int droneCounter = 0;
    bool packageMustNotBeDrones = false;
    while (std::count(dead_drones_indices.begin(), dead_drones_indices.end(), dronesIndex))
    {
      // while the dronesIndex is in the dead_drones_indices, increment the dronesIndex
      dronesIndex = dronesIndex + 1;
      if (dronesIndex == drones_.size())
      {
        dronesIndex = 0;
      }
      droneCounter = droneCounter + 1;
      // we want to avoid an infinite loop, if all of the drones are out of battery
      if (droneCounter >= drones_.size())
      {
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

    if (!packageMustNotBeDrones && !packageMustNotBeRobots)
    {
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
      }
      else if (drones_.size() > 0 && robots_.size() == 0)
      {
        assignPackageToDrone = true;
      }
      else if (drones_.size() == 0 && robots_.size() > 0)
      {
        assignPackageToDrone = false;
      }
    }
    else if (packageMustNotBeDrones && !packageMustNotBeRobots)
    {
      // the package must be assigned to a robot
      assignPackageToDrone = false;
    }
    else if (!packageMustNotBeDrones && packageMustNotBeRobots)
    {
      // the package must be assigned to a drone
      assignPackageToDrone = true;
    }
    else
    {
      std::cout << "WARNING: none of the drones or robots have battery. The package cannot be scheduled" << std::endl;
    }

    if (assignPackageToDrone)
    {
      std::cout << "Assigning to Drone\n"
                << std::endl;
      Drone *actual_drone = drones_.at(dronesIndex);
      if (actual_drone)
      {
        actual_drone->AddAssignedPackage(*actual_package);
        do
        {
          if (actual_drone->GetNumAssignedPackages() == 1)
          {
            // assign the curPackage if it's the first one assigned to the drone
            actual_drone->UpdateCurPackage();
            // get the path and set it to the delivery simulation's curRoute
            std::vector<float> drones_position = actual_drone->GetPosition();
            std::vector<float> packages_position = actual_package->GetPosition();
            actual_drone->SetFlightBehavior(drones_position, packages_position, const_cast<IGraph *>(systemGraph));
            //SetFlightBehavior now sets the route for the drone
            actual_drone->SetOnTheWayToPickUpPackage(true);
            actual_drone->SetOnTheWayToDropOffPackage(false);
          }
        } while (actual_drone->GetNumAssignedPackages() == 0);
      }
      dronesIndex = dronesIndex + 1;
      if (dronesIndex == drones_.size())
      {
        dronesIndex = 0;
      }
    }
    else
    {
      std::cout << "Assigning to Robot\n"
                << std::endl;
      Robot *actual_robot = robots_.at(robotsIndex);
      if (actual_robot)
      {
        actual_robot->AddAssignedPackage(*actual_package);
        std::cout << "num assigned packages: " << actual_robot->GetNumAssignedPackages() << std::endl;
        if (actual_robot->GetCurPackage() == NULL)
        {
          std::cout << "nopackage_____\n";
        }
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

    for (IEntityObserver *obs : observers_)
    {
      obs->OnEvent(val, *package);
    }
  }
}
