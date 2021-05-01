/*! \mainpage Claire Yang, David Johnson, Casey Connell, Iteration Three Submission

* Getting Started
* ===================
* 1) Run `git clone git@github.umn.edu:umn-csci-3081-s21/repo-iter2-01-28.git`

* 2) Build the environment in Docker by going to the `project` directory, and running `bin/build-env.sh`

* 3) Run the actual environment by running `bin/run-env.sh`

* 4) Run the delivery simulation by going to the project directory in Docker, `make`, and running `./bin/run.sh`

* 5) Open the 127.0.0.1:8081 in your browser to view the simulation


* Running Tests
* ==================
* 1) In the `project` directory in Docker, run `make test` to make the tests

* 2) Then, run `./bin/test.sh` to run the tests and view the results


* Generate Doxygen documentation
* ==================
* 1) Navigate to `project/docs` and run `doxygen Doxyfile`.

* 2) Then open `project/docs/html/index.html` in your web browser to view the documentation.



* Iteration 3 Team Documentation
* ==================
Iteration 3 Deliverable Meetings:

* Casey Connell - Development Lead
* David Johnson - Scheduler
* Claire Yang - Project Manager


*1) April 26th, 2021 -- David Johnson, Claire Yang, Casey Connell

*Casey and David were assigned to work together on creating the decorated_entity classes, while Claire was assigned with updating the UML and creating the decorated_entity_test.cc

*2) April 27th, 2021 -- David Johnson, Claire Yang, Casey Connell

*Casey and David figured out several bugs with the color values that were being passed into the json file, and Claire found several bugs in the implementation of the decorator pattern while writing tests.

*3) April 30th, 2021 -- David Johnson, Claire Yang, Casey Connell

*We all worked together on finishing up the documentation and addressing Iteration 2 feedback.

*Casey Connell created the decorated_entity.h class, and the logic for changing colors based on the battery life of the drone/robot using the decorator pattern.

*David Johnson helped with the implementation of colors, notifying observers, and debugging.

*Claire Yang worked on the Google tests, the debugging, UML and the documentation, and addressing the feedback from Iteration 2.


* Designing and Implementing the routes
* ==================
* Using the Strategy Pattern to implement different flight routes gives our program a wider range of functionality, allowing us to apply different flight algorithms to our drones, and to easily swap them out, implement new ones, or extend the existing ones.
* This is possible because the flight routes are mostly calculated from the same data, the drone's starting position and the position of the target. For only the Smart Route, the IGraph object was necessary in order to use its method to compute the shortest path of graph nodes between the drone and its destination.
* Each flight strategy can be implemented to update each step of the flight using the same data, making them interchangeable in both setting up their algorithms and executing each step. For this we created the two methods SetFlightDetails and FlightUpdate, SetFlightDetails needs to be called initially, and then FlightUpdate will be called with each timestep.
* Additionally, each flight strategy is implemented with two methods to create and to return a route for the observers to draw in the scene.

* We successfully implemented the strategy pattern to allow each Drone to use their own flight algorithm to create and execute a delivery. This required creating a strategy interface (FlightBehavior class) that defined pure virtual methods that would be implemented by the various flight strategy classes (BeelineFlight, ParabolicFlight, PathFlight). These flight classes are used by Drone, which contains a pointer to an object of the strategy interface that allows us to easily set or change the algorithms used by the drone.
* Currently, the drone checks if the picojson object passed into its constructor includes a specific "path" or route to use. If that detail is specified, it uses the specified route. Otherwise, it will cycle through the three types of routes whenever it updates to a new route. The three different routes are described below. The implementation details are discussed in even greater detail after the description of the different routes.

* The Smart Route is implemented via the A-star/Djikstra shortest path algorithm. It generates a graph of all the nodes and vertices in the scene, and then when given a position and destination, it calculates the shortest path and returns that vector of path nodes.
* A drone or robot will use a Vector3D direction vector to point at each successive node in the path, and it will fly towards that specific node until the node's position is within the entity's radius before targeting the next node. Once the entity is within radius of the last path node, it will stop moving until it is given another new route to follow.
* The Smart Route defines and uses the internal member functions SetCurRoute and CheckWhenToIncrementPathIndex to keep track of the correct node to fly to.

* The Beeline Route is implemented to first make the drone rise to a set height (280 in our simulation) in order to avoid building collisions, then fly in a straight line from the current position to the target, and lastly descend to either pick up the package or finish the delivery.
* It uses Vector2D to compute the direction unit vector and apply the speed and time offset to update the drone's position in each time step.

* The Parabolic Route is implemented to create a parabolic flight plan, creating a parabola than spans the drone's starting position and it's destination, with the height set to 15% of the flight distance to create a shallow, efficient parabolic flight. It uses Vector2D functions to implement a beeline path that ignores the y-axis, and instead applies a y-axis offset calculated from the equation of the parabola that was calculated.
* It uses the equation:
 y offset = -ax^2+bx+c where x is the distance from the flight midpoint, c is the parabola height, b is zero, and a is some small decimal computed:
 a = c / (initial x / 2)^2
* This y offset is applied to the initial y value to calculate the drone's intended hight and it is applied at each update. The direction's y-value is also zeroed because it looks more accurate to how a drone flies.
* The Parabolic Route implements a single helper function, CalculateDistance, to return the x,z distance between the current position and the target.
* The UML diagram of our flight route implementation is shown here:

* \image{inline} html strategy-pattern.png "Strategy Pattern Flight Route Implementation UML Diagram"

* Discussion of Observer Pattern Design
* ==================
We successfully implemented the observer pattern to send notifications to the observers regarding the entities' status when a change occurs.


DeliverySimulation will first notify the observers that an entity has been assigned to a package, and that it is on its way.
The rest is then handled within the Robot and the Drone class.
After a Drone or a Robot has been scheduled, it will notify the observers that it is now moving.
When it gets to the package it will notify the observers that it has been picked up.
When the package is dropped off it will announce that it has been delivered to its destination.
The Robot and the Drone will announce that they have stopped moving if the package is delivered and there are no more deliveries left, or if they have run out of battery.


In the observer pattern tests, we specifically test the observer's OnEvent notification to see if it prints out the correct type of notification. We do not test the pattern itself because that requires a mock system. If we were to test it however, we would plan on setting up a mock DeliverySystem and hardcoding a scheduled delivery between a drone and a package. This would trigger a notification to the observers about the package being scheduled, which would show that our pattern is working in that case.


* Discussion of Implemented Composite Factory
* ==================
* For Iteration One, I (Claire Yang) implemented a composite factory pattern for the creation of the three entities (Drone, Customer, and Package).
* Each of these entities has their own factory that solely handles the creation of that respective entity. The Drone object is created by the DroneFactory, the Customer object is created by CustomerFactory, and the Package object is created by PackageFactory.
* The management and creation of the three factories mentioned above happen in the CompositeFactory. When the delivery simulation wants to add an entity, it will pass the JSON object to the CompositeFactory to create the correct type of entity.

* An advantage of using the composite factory pattern is that the logic of adding the entity within the delivery simulation is simplified. Without the composite factory, we would require conditional statements that would have to be modified every time we add a new entity type to the simulation (e.g. Robot or Truck).
* This violates the open/closed principle, as it makes the code hard to extend. Additionally, it also means that the DeliverySimulation class would have more than a single responsibility, and the code would be less cohesive.
* With the composite factory, we can easily describe the delivery simulation in one line (e.g. "Schedules the deliveries and updates the overall simulation"). This follows the Single Responsibility Principle. However, if we had to include the logic for creating the entities within delivery simulation, then that simple description would become more convoluted. The Single Responsibility Principle would be violated.
* Lastly, the composite factory pattern makes use of different classes to create different entities and keeps them all in one place. This makes it easy to potentially extend this pattern to subclasses with different behaviors. For example, if we wanted to create a RedDrone and a BlueDrone subclass entities that carry different package weights, then it'd be easy to create RedDroneFactory and BlueDroneFactory classes that inherit from the DroneFactory. The creation logic for which subclass to create could then be handled within the DroneFactory class. We would not need to update CompositeFactory, since it already knows of DroneFactory.

* A disadvantage of using the composite factory pattern is that it still requires a for loop to figure out which factory we want to invoke to create the correct entity. Although this is more elegant than a bunch of conditional statements, we still have to put in a check to make sure that the correct factory is being called when creating an entity within CompositeFactory.
* The composite factory pattern is also unecessary if there aren't any hierarchical relationships between the entities that the factory are creating. It works for our delivery simulation because Drone, Customer, and Package all inherit from EntityBase. However, if we wanted factories to create a different type of entity that does not have any hierarchical relationship with EntityBase, then CompositeFactory would have to be modified, which defeats the principle of the class being closed to modification.
* Lastly, this pattern would also be too complicated if we only had one type of factory, or if the creation logic is very simple. In those cases, one could just use a concrete factory, or abstract factory.

* Concrete factory pattern vs. abstract factory pattern vs. composite factory pattern
* ==================
* The diagrams of the different factory patterns, along with discussions about their pros and cons are below.

* \image{inline} html concrete-factory.png "Concrete Factory Pattern UML Diagram"

* The concrete factory pattern is the simplest factory pattern, in which there is one factory that handles the creation of the different entities. Its simplicity is its advantage, as it is very easy to understand, and it serves the core purpose of a factory in separating the creation logic from the delivery simulation. However, its disadvantage is that we must use conditional statements (see the pseudocode in the diagram) to figure out which entity object we want to create within the EntityFactory. Thus, in order to extend it with another entity, we would need to modify the EntityFactory class.

* \image{inline} html abstract-factory.png "Abstract Factory Pattern UML Diagram"

* The abstract factory pattern solves the conditional statement problem presented by the concrete factory by pushing the creation logic to subclasses. Thus, in order to extend the code, we would just need to create another type of EntityFactory, and add it to the DeliverySimulation. It does not fully remove the necessity for a conditional statement, however, since the DeliverySimulation still requires logic to choose which factory it wants to call. Thus, the program is tightly coupled with the types of factories, and so we would need to modify the DeliverySimulation methods in order to extend the entity types.

* \image{inline} html composite-factory.png "Composite Factory Pattern UML Diagram"

* The composite factory pattern removes the necessity for a conditional statement in DeliverySimulation, which makes the code more cohesive. It does this by collecting all of the different factories into a CompositeFactory that manages which factory it should call through a for loop. The delivery simulation just has to call createEntity on the CompositeFactory in order to get back the correctly created entity. A con of this pattern is that it can be overly complicated if there are no hierarchical relationships between the entities that the factory is creating, and is unecessary for simple creation logic of entities.

* Colored Entities Based off of Battery Charge
* ==================
* For this iteration, our team chose to use the Decorator Pattern to Color Entities that have Batteries
* Which in this case would be Drones and Robots. The way this works is there is now a decorated_entity
* which contains a robot or a drone. When its update function is called, it looks at the battery contents
* of what it holds, assigns it the appropriate color, and then calls the update function of the Drone or Robot.
* We opted to use 15 different colors as the batteries decrease, as this allowed an easy way to determine what color should be used next
* and creates a relatively smooth transition. Some of the issues that occured with implementing this was Determining whether or not
* to write anything back to the details_, or simply determine it by its charge. Whether to use this switch statement or try to go for more of a gradient.
* How to determine the next color, the erroneous belief at it being in hex at first, where it is not, and finally
* on how to construct the notification for the observers. However now that these problems have been dealt with, it would be
* reasonably simple to create other types of decorated entities.


*/
