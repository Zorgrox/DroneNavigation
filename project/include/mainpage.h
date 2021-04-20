/*! \mainpage Claire Yang, David Johnson, Casey Connell, Abdirashid Ahmed's Iteration Two Submission

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


* TODO: Teamwork Documentation
* ==================
TODO: here are the meetings and people in those meetings to work on this...


* TODO: Discussion of Different Route Implementations (Smart Route, Beeline, Parabolic)
* ==================
The Smart Route is implemented via the A-star/Djikstra shortest path algorithm. It generates a graph of all the nodes and vertices in the scene, and then when given a position and destination, it calculates the shortest path.


* Discussion of Observer Pattern Design
* ==================
We successfully implemented the observer pattern to send notifications to the observers regarding the entities' status when a change occurs.


DeliverySimulation will first notify the observers that an entity has been assigned to a package, and that it is on its way.
The rest is then handled within the Robot and the Drone class.
After a Drone or a Robot has been scheduled, it will notify the observers that it is now moving.
When it gets to the package it will notify the observers that it has been picked up.
When the package is dropped off it will announce that it has been delivered to its destination.
The Robot and the Drone will announce that they have stopped moving if the package is delivered and there are no more deliveries left, or if they have run out of battery.


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

*/
