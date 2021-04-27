# Scene Descriptions

## Note: Recharge stations are not required for iteration 2

## umn.json

Identical to the umn.json provided for iteration 1. It has one customer, package, and drone.

## recharge.json

Identical to umn.json, with the addition of an entity of type "recharge_station" near the customer. This scene does not need to work for iteration 2.

## robot.json

Identical to umn.json, with the replacement of the drone for a robot.

## parabolic_drone.json

Identical to umn.json, but the drone specifies its path type as parabolic.

## beeline_drone.json

Identical to umn.json, but the drone specifies its path type as beeline.

## smart_drone.json

Identical to umn.json, but the drone specifies its path type as smart.

## two_packages_two_drones.json

This scene has two packages at different locations and two drones at different locations, both packages should be delivered to the same customer. One drone is the Beeline path type, and one is the Smart path type (getting a path using IGraph::GetPath)

## two_customers.json

This scene is the same as the above, except there are two customers, and one package goes to each customer.

## drone_and_robot.json

This scene is the same as the above, except one drone is instead a robot.

## drone_low_battery_a.json

This scene has one customer, one package, and two drones. One of the drones has low battery, so if it picks up the package and dies on the way to the customer, the other drone should take over.

## drone_low_battery_b.json

This scene is the same as the above, but the two drones are swapped. Your simulation should work for both of the above.

## drone_and_robot_many_deliveries.json

This scene has one customer, six packages, and a robot and drone. The robot and drone should each deliver at least one package to the customer, and all the packages should be delivered customer by the end.

## all_features.json

This scene has two customers, 4 packages, two drones, two robots, and a recharge station. One of the drones and one of the robots are at medium battery, and might die before the end of the simulation. The simulation doesn't need to implement the recharge station.

## all_features_no_recharge_station.json

This scene is identical to `all_features.json` with the removal of the recharge station since that is not required for iteration 2.

