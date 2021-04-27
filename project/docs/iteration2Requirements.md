# Iteration Two: Enhancing and Extending the Package Delivery System

## Iteration 2 - Version 5, March 28th - Adding priority 4 to the final deliverable requirements and adding delivery of multiple packages to multiple customers in the first deliverable.

## Iteration 2 - VERSION 4, March 26th  - Adding clarification regarding path passed to observers and robot entity.

## Iteration 2 - VERSION 3, March 23rd  - Adding clarification that simulations should be capable of multiple-package simulations.

## Iteration 2 - VERSION 2, March 23rd  - **Changed the due date of the final deliverable from April 12th to April 19th**<hr>

## Iteration 2 - VERSION 1, March 22nd  - **NOTE, THE REQUIREMENTS IN THIS DOCUMENT ARE SUBJECT TO CHANGE. THERE WILL BE A CANVAS ANNOUNCEMENT WHEN THERE IS A CHANGE TO THIS DOCUMENT.**<hr>

| Date | Item | Description of Verification and Validation of Deliverable(s) |
|:----:|:-----|:------------|
| FRI, April 2nd, 11:55pm | Robot also delivers packages and implement the Observer Pattern for observing Packages, Drones, and Robots. Fix your GoogleTests | inspection |
| Mon, April 19 , 11:55pm | Incorporate a strategy for choosing different routes (smart, beeline, parabolic) for the drone and when the battery is depleted the drone or robot will drop the package and become idle. The package must be rescheduled for delivery  | Automated tests and inspection |

In the previous iteration you showed that a drone can deliver a package to a customer either using a predefined route or a beeline route. In this iteration we will be enhancing the functionality of the previous iteration to include a robot that also delivers packages, report when a package is scheduled, in route, and when it has been delivered. Add additional reporting features for the robot and drone to report when they are moving or idle. You will also implement a strategy for routes the drone will take either smart, beeline, or parabolic. (All three routes will be tested). Add the functionality of determining if the battery of either the robot or the drone is depleted the package will be dropped, rescheduled for delivery, and the robot or drone will be idle.

### Team 

You will work with your team to complete this iteration. A lab will be posted describing how this will work for the remainder of the iterations. At the end of the iteration everyone on the team will evaluate the performance of each team member. The evaluation process will be used in determining the grade of each team member. 

### First Deliverable ---- Due Friday April 2nd by 11:59 PM

0. Download the latest support code from the shared upstream. Contains a modification to the jsonhelper and additional scenes for you to test your functionality.

1. Add a robot entity to the simulation that will also deliver packages. The robot cannot fly, but it can follow the routes to deliver the packages to the customer. Create google tests for all the public methods of the new robot class. 

2. Implement the observer pattern to report when a package is scheduled, delivered, or enroute to all of the observers. In addition, report when either entity the drone or the robot are moving or idle. Further details can be found in the section Deliverables and Submission Process. **See: [Observer Pattern]( https://www.geeksforgeeks.org/observer-pattern-set-1-introduction/) and also chapter two in the heads first design book** for an overview of the observer pattern. 

3. **The simulation must show the robot/drone can deliver multiple packages to multiple customers.**

4. Fix your google tests from the first iteration based upon the feedback received. 

### Final Deliverable --- Due Monday April 19th by 11:59 PM

1. The drone will be choosing a route using one of three routes: shortest path algorithm, beeline, or parabolic based upon differing sets of criteria, for example: Time of day and/or route information, etc. Further details can be found in the section Deliverables and Submission Process.
The strategy pattern may be useful for designing and implementing this capability. **See: [Strategy Pattern](https://www.geeksforgeeks.org/strategy-pattern-set-1/)** for an overview of the strategy pattern.  See the following links for examples of implementation of the strategy patten in java and C++:   

a. https://www.geeksforgeeks.org/strategy-pattern-set-2 (in Java)  
b. https://sourcemaking.com/design_patterns/strategy/cpp/1 (in c++)  
         
2. Priority 4 must be implemented in the simulation.

3. In your Doxygen mainpage add a section named: **"Designing and Implementing the different routes"** that discusses the design and implementation of different routes and any design pattern used by the drone to deliver packages. Specify what classes and methods you had to add, where you had to add them, - and include pictures where applicable and possible. **Note which parts of the design and implementation were most difficult for you, and include any tips or advice on how to understand and implement the different routes (for example, what sources of information (documentation, lecture, lab) that helped you understand the routes and enabled you to design and implement it (for example, what sources of information (e.g., links to web sites, books, lecture, lab)).** 

4. In your Doxygen mainpage add a section named: **Team Documentation** that includes summaries of team meetings (minimum of three) and who was assigned a task to complete. 

5. Ensure all new classes and methods you have written are properly documented. All header files must document the classes and their methods using Doxygen, and all implementation (that is, \*.cc) files must have self-documenting code. **You do not need to document the web server code base.** 

6. Correct and update your UML class diagram from Iteration 1 to include the changes to your code including all classes you added to complete the iteration 2 requirements and their relationships to each other and the classes that previously existed in the simulation.
    
**NOTE, if you are unable to complete all or a portion of an implementation item, include a discussion of your PROPOSED design of the observer pattern in your mainpage, and your PROPOSED class design / changes for all your implementation items in your UML and and note that in a paragraph at the top of your mainpage (Tell us what you did not sucessfully implement - success is defined as the functionality compiles and executes) so you recieve credit for your design efforts.**

## Deliverables and Submission Process

>You will submit all your deliverables via GitHub according to the process specified lab 10. We will tag and pull your repository at the specified due dates and grade them according to the contents at that time.

>#### You must verify that your submission compiles on a cselabs machine and it is complete. You will receive zero or be heavily penalized if your code does not compile and/or we cannot generate documentation using Doxygen as specified in Lab 8 upon submission.

The schedule is very tight, and it is important that you keep up with the project. The project will continue to build throughout the semester, and if you get behind, it will be very difficult to catch up. For this reason, **late assignments will will receive the following penalities: 1 day late -- 10% deduction, 2 days late -- 20% deduction. A day is defined as a regular day of the week, thus if your submission is due on Friday at 11:55 PM and it is submitted on Saturday it is one day late. Submissions after two days will not be accepted**, but you will receive partial credit for partial completion of the requirements - so **ALWAYS MAKE SURE TO SUBMIT SOMETHING - SOME POINTS ARE BETTER THAN NONE**.

You can convert this requirements document to pdf using this tool: http://www.markdowntopdf.com/

<hr>

### Overview

In this iteration, you do the following development including:

- writing a robot class that will also deliver packages. 
- formulating unit tests with Google Test
- adding to the simulation class structure 
- ensuring coding style compliance
- augmenting the design discussion in your doxygen mainpage to include a discussion on your design and implementation of the routes used by the drone.
- augmenting the design discussion in your doxygen mainpage to include a section on your teamwork for this iteration
- modify/update your iteration UML design documentation to include the classes and methods you add or refactor in iteration 2.
- using Doxygen to document and generate documentation.
- Use git, and produce self-documenting code (i.e. good organization and naming conventions). 

Teaching staff (Undergraduate TA's, Graduate TA's, and Instructors)  will also be working diligently to provide the structure and support for development, testing, and documentation. Automation in unit testing, style compliance, in-house github testing, and documentation will make this an easier process, however it means that you will have to develop within the constraints of these systems. **Often there is a learning curve and a lot of systems trouble-shooting to get it all working, so start early!**

## Documentation and Code Implementation Requirements

**REQUIREMENTS you need to fulfill**

> This is just functionality. Along the way, make sure to document the code using Doxygen syntax in the header files, and self documenting code (as discussed in McConnell's text in Chapter 32) in your class implementation (\*.cc) files. and the main function.  

Below is a prioritized list of enhancements to our support code to make the simulation realistic. **Complete all functionality in one priority level before moving on to the next.** In this way, if we run out of time, the low priority items will be dropped from the requirements.

#### Priority Level 1:

1. Fix your Google Tests from Iteration 1.

2. Create a Robot class that can deliver packages to a customer. The Robot cannot fly, therefore it will be grounded and will essentially have the same functionality of the drone class. The Robot class should use the "smart" route method, which uses the IGraph::GetPath() function. The Robot entity will be specified in CreateEntity when the json contains "robot" as the value for the "type" key.

#### Priority Level 2:

1. **Allow for multiple packages to be delivered in a simulation**

 * Having only one package scheduled and delivered in a simulation is very constricting. We would like simulations to be capable of delivering multiple packages, utilizing multiple robots/drones.
 
 * Scheduling logic is open-ended and up to you to decide. You can determine which Drone/Robot delivers which package however you want. One simple metric could be choosing whichever Drone/Robot is closest to the package and is not currently making a delivery.
 
 * Drones/Robots should only be capable of delivering one package at a time.
 
 * If a Package is scheduled for delivery at a time when no Drone/Robot is available, the Package should be delivered when one of the Drones/Robots finishing making their delivery.
 
 * Remember to run a specific scene with `./bin/run.sh scenes/<name_of_scene_file>`, there are a few scene files which include multiple packages so you can debug this feature of your simulation. See the file `project/web/scenes/scene_descriptions.md` for a description of each scene file.

2. **Observe Packages**

 * Observers will be added to your simulation through the `AddObserver` method. Any Observers added should be notified by calling their `OnEvent()` method when the described events occur.
 
 * We have already made observers for you: *the WebSceneViewer and the EntityConsoleLogger*.  The teams task is to implement the subject part of the Observer pattern, your team does not need to implement any Observers.

 * When a package has been scheduled, picked up, or delivered, all observers associated with the simulation should have their *OnEvent(...) method* called. This method is part of the front-end code, but you need to pass the correct information to it in regards to the observer in the following situations:

  * **Package scheduled:**</br>
 > observer->OnEvent({“type”: “notify”, “value”: “scheduled” }, package)

  * **Package picked up by drone or robot:**</br>
 > observer->OnEvent({“type”: “notify”, “value”: “en route” }, package)

  * **Package dropped off by drone or robot:**</br>
 > observer->OnEvent({“type”: “notify”, “value”: “delivered” }, package)

  * ***This notification will be displayed as an overlay on top of the visualization.***

  * Packages' notifications should be passed to all observers associated to the simulation.

  * You should be able to remove any observers from the simulation with the removeObserver(...) method.

3. **Observe Drone/Robot**

 * We need to be notified of all drone/robot path changes so we can analyze and keep track of the drones/robots, as well as draw the routes of drones/robots in the simulation.
 
 * When a Drone/Robot begins moving, it should pass the path of its current destination to all observers. (If the Drone/Robot is moving to a Package, it should pass the path to the Package, if it is moving to a Customer, it should pass the path to the Customer).

 * When a drone/robot stops moving or starts moving all observers associated with the simulation should have their *OnEvent(...) method* called. This method is part of the front-end code, but you need to pass the correct information to in regards to the observer in the following situations:

  * **Drone/Robot enters idle state (stops moving):**</br>
 >observer->OnEvent({“type”: “notify”, “value”: “idle” }, drone)

  * **Drone/Robot enters moving state:** (See the JsonHelper for how to encode the path)</br>
 >observer->OnEvent({“type”: “notify”, “value”: “moving” “path”:[[x0,y0,z0],[x1,y1,z1],...,[xn,yn,zn]]}, drone)

  * Drones and robots should notify all observers associated with the simulation.

#### Priority Level 3: Implement a different drone route using the Strategy Pattern

To enhance the simulation even further, the drone will use different routes to deliver the package to the customer. The routes to implement are:
  * smart
  * beeline
  * parabolic
  
The routing strategy that a drone uses will be specified in the details object that is passed into the CreateEntity function, under the key 'path'. The possible values for the 'path' key are 'smart', 'beeline', and 'parabolic'. For example, if a drone has a details object where 'path' = 'smart', it should use the 'smart' pathing strategy.

How to implement this priority will be discussed via lecture and a lab. 

#### Priority Level 4: Drone/Robot Delivery Functionality

Drones and robots will have the following realistic limitation of battery life (in seconds). The following rules will apply for drones and robots:

  * If a 'battery_capacity' key is present in the `details` object passed to `CreateEntity()`, the robot/drone should be initialized with a battery of max capacity equal to the value of the 'battery_capacity' key (which will be a floating point number).
  * When either are moving the battery life starts to drain. Once the battery life is gone, the robot or the drone will switch to idle mode and no longer move. When this occurs the package will be dropped and should be rescheduled. This event needs to be reported to the observer that the package has been scheduled again according to priority 2 requirements. In addition, the robot or drone also need to report to the observer a change in state.
  * If a package is dropped a new drone/robot should be allocated to complete the delivery.
  * Drones/Robots cannot exceed their maximum speed.
  * When Drones/Robots enter idle mode when not moving and the battery does not drain since they are not moving.

### Unit Testing with Google Test

https://github.com/google/googletest

Unit tests are essential in a large-scale project, because the entire code base can be tested regularly and automatically as it is being developed. In the strictest application of Test-Driven Development (TDD), the tests are written _before_ the code, which helps solidify requirements and write testable code.

A sample test file is provided in the /project/tests directory. This directory must be a sibling to your _src_ directory. When you _make_ the tests, they will generate an executable (in build/bin) which, when executed, displays a report of the tests. Use this file as a guide to your own testing. While the requirements for testing in Preliminary Turn-in #2 (more later) are rather light, you can expect a much more robust testing requirement in later iterations. Do not slack on making good tests for your code!

### Style Compliance

You may use the style guidelines suggested in McConnell or the following google style guide.

https://google.github.io/styleguide/cppguide.html

Consistency in code organization, naming conventions, file structure, and formatting makes code easier to read and integrate. There are many options with various merits, so it is up to the development team to establish these
conventions, or, in the words of Kevin Wendt, an instructor for previous iterations of the course, "The only style guide that really matters is the one your boss uses." 

<hr>

## Documentation

- UML diagrams
- Doxygen generated web pages including mainpage.h 
- Self-Documenting code that is style compliant

Code documentation comes in many forms for many audiences. For this project, **your audience is other programmers**, who need to understand class interfaces, function parameters, function behavior, code organization, class organization, and code logic. Self-documenting code (i.e. using good organization and naming conventions) is an efficient means of communicating, since you have to write the code anyway. _Good_ comments - not too much, not too little - help guide others through the logic and class interfaces. For the larger picture of code and class structure, use UML diagrams and Doxygen-generated (automatic) web pages.

#### UML

The UML diagram is a visual aid that helps other programmers better understand the code structure. It should include only those aspects that are essential, otherwise your diagram will get too cluttered and overwhelm the reader. Here are some things to keep in mind as you are designing your UML:

- Make the most important classes prominent in the layout (i.e. your eye tends to focus in that general area when you first look at it).
- Lay out the classes so that the connections have as few crossovers as possible.
- Do not include setters and getters in your methods list unless there is something special about them that you need to communicate.
- You should not include structs or enumerated types unless they add value to the understanding of the overall code structure.
- If a class is composed of another class, you can show that association with a solid line arrow (if there is only 1) or using the _compose_ diamond.
- Include cardinality where appropriate.
- Add comments to classes and/or relationships to clarify the interaction or to point out subtleties that are essential to using the code.

The final diagram you submit for iteration 2 UML should reflect the changes you made while completing the code requirements. We will be looking for proper use of UML components, and a correct depiction of the code structure.

There are many free tools that you can use to create the UML including Doxygen (see: https://inneka.com/programming/cpp/how-to-use-doxygen-to-create-uml-class-diagrams-from-c-source/), and  draw.io (see: https://www.draw.io/). **Submit your UML as a pdf into the assignment folder on Canvas.**.

#### Doxygen

Doxygen automatically generates documentation of class and code structure when you follow some simple conventions for commenting within your code (_see_ http://www.doxygen.nl/manual/index.html and https://caiorss.github.io/C-Cpp-Notes/Doxygen-documentation.html). You have had a lab on Doxygen (lab 8) and we will likely cover a bit more in class. To start with, look over the documentation provided with the code base to understand how to document classes, methods, parameters, and even _todo's_ and _bugs_ in your code. In lab 8, you learned how to compile with your Doxyfile and generate web pages. Please look over the generated web pages for missing and incorrect information. The requirements for Doxygen include:

- the file `project/docs/Doxyfile` to generate documentation (after you complete lab 8, you should have this in your `project/docs` directory).

- a _mainpage.h_ file that serves as the homepage of your automated documentation. The information that you added from iteration 1 should remain. You should have a mainpage.h file that you can extend in your `project/src` directory. 

- document all classes, methods, and functions that you add in interation 2 in their header (.h) files. 

-  add a section named: **"Desiging and Implementing the routes"** that discusses the design and implementation of routes used by the drone, as per the description in the final deliverables above. 

- The /html directory should *not* be in your repo in github.umn.edu - nor should your build directory, executable files, or object files.

> **As part of your fresh clone prior to submission, please also compile the Doxygen and look at the generated webpages.**

All of these elements of documentation will be assessed, accounting for a significant portion of your grade for each iteration (for this iteration - iteration 1, documentation will account for 1/2 of your grade). Think about these two extremes: 1) your code functions perfectly and you have almost no documentation - you will likely fail on this iteration; 2) your code is not functional and will only compile when you comment most of it out, but if you have complete, great documentation - you will likely get a decent grade on this iteration. **Get in the habit of creating the documentation along with the code.**

<hr>

## Assessment

Your software **must compile on a cselabs machine or it will not be graded, and you will recieve a zero for your submission**. We will not grade your project unless it compiles. As long as you provide a version that compiles, we will evaluate those aspects that are partially functional for partial credit. In other words, <u>comment it out if it breaks compilation</u>.

Your software will be assessed through automatic testing and by the TAs. You will receive immediate feedback whenever you push to github (although not now - we will let you know when those scripts are in place). At the deadline, all submissions will be downloaded and the automated testing will no longer be available. Through both automated testing and the TAs, the process for testing will be to `make clean` then `make`. We **highly encourage** you too freshly clone your repo on a **cselabs machine** and to then `make clean` and `make`, followed by a run of your tests to confirm all is working well before submitting your tests and code.

This is the breakdown for point distribution:

20% : Iteration \#2
- 15% : First Deliverable
- 50% : Final Documentation
- 35% : Final Code

### Documentation Assessment ( 50% )

#### Complete Iteration Documentation 

#### Design Document and UML

**"Designing and Implementing the different routes"** that discusses the design and implementation of different routes the and any design pattern used for the drone to deliver packages. Specify what classes and methods you had to add and where you had to add them - and include pictures where applicable and possible. **Note which parts of the design and implementation were most difficult for you, and include any tips or advice on how to understand and implement the different routes (for example, what sources of information (documentation, lecture, lab) that helped you understand the routes and enabled you to design and implement it (for example, what sources of information (e.g., links to web sites, books, lecture, lab)).** 

In your Doxygen mainpage add a section named: **Team Documentation** that includes summaries of team meetings (minimum of three) and who was assigned a task to complete. 

Documentation includes a design overview of the core domain elements (the classes you're building) provided in mainpage.h in /src and your final updated UML diagram in PDF file format. We will look for a well written and well organized document that clearly articulates the design. It must stand alone in the sense that anyone reading it should not have to look at code to understand the design. **This will likely require UML images and/or snippets of code included.** 

***Your final UML diagram from iteration 1 should be updated to include the class(es), methods, and relationships that you have added or changed during your iteration 2 development activities. The UML syntax you should use is specified and documented here: https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/. We will be looking for general proper use of UML syntax, and a correct depiction of the code structure of the existing project code (code from shared-upstream's support-code branch).*** 

**Submit your final version of your UML diagram in a .pdf file via the submission item on Canvas.**


#### Style Compliance

Will be done by inspection.

#### Doxygen Documentation

We will compile the code to generate _Doxygen_ web pages. All classes and major functions must be documented as specified in the _Doxygen_ documentation.

#### GitHub Issues

Your repository must include Issues that communicate to the TAs. If there are no bugs in your code, include a GitHub Issue that states that there are no known bugs to report  and that further verification is necessary (never say that there aren't bugs, because we know that that is typically not the case :-). We anticipate that a few bugs will exist in your project and they will reveal themselves during testing. If you have a few bugs AND you report them, then you will lose fewer points than if you don't report them - provided the bugs aren't preventing the simulation from running to completion. Also, keep in mind that development will continue throughout the semester, and if you can't fix your code this iteration, you *might* have an opportunity in successive iterations to do so(there are no implied guarantees on this though), so keep use github to keep track of all your bugs.

For this iteration, every time you make one single change to your code, you should follow the process documented in lab 10.  Create an issue, a new branch, address the issue (add or fix functionality, etc.), test.  When it works, commit and include a ** meaningful** commit message (what did you fix, add, etc.),  merge the new branch back in with the development branch, and then test again.  We will grade you on your adherence to the process. You should have at LEAST as many issues, branches, commits, and merges as there are updates and new functionality required by the iteration. 

#### Self-Documenting Code

TAs will inspect code for good naming conventions, good code organization, and internal comments to highlight logic. You should not nest conditional statements too deep. Methods should not be more than a screen full, if possible. Names should be descriptive of the variable's or function's purpose. Like elements should be next to each other in the file.  Review Chapter 32 in the McConnell text, available on the Class Canvas site, for more information on how to create self-documenting code. 

### Code Assessment ( 50% )

#### First Deliverable: Fixed Google Tests From Iteration 1, robot delivers packages, and the observer pattern has been implemented ( 15% )  

In the week prior to the due date of the completed iteration, we will confirm that you have submitted work for your first deliverable #1.

Your Google Tests from iteration 1 should be revised and updated based upon the feedback provided to you in the first iteration.

Points you earn in the first deliverable are independent of the 35% points for the final submission.

**Your tests should be in the development branch in your repository on github.umn.edu by the end of the day Friday,  April 2.**  _Remember to GIT ADD, GIT COMMIT and GIT PUSH them before the deadline_

#### Completed Iteration Code ( 35% )

Code functionality will be tested with automated tests through Github, which in turn run the automated unit tests of Google Test. Assessment will also be a visual inspection of the simulation and its output, as well as a visual inspection of the code.

<hr>

## Getting Started

AFTER reading this document, complete Lab 13 Working with Teams that will be assigned this week. This should be completed before Friday March 26. 

<hr>

## Important notes to remember

>Your software is a reflection of your understanding of the requirements as specified in this document. If you do not understand any portion of the requirements or you think that the requirements are underspecified, it is your responsibility to get clarification from the instructor or a TA. Please read this document carefully and review it prior to turning in your iteration for assessment.

>The ONLY supported environment is the CSELabs environment. This is where we will run your code for assessment, and where you should absolutely ensure that your project will compile and run. It is recommended to log onto a CSELabs machine, do a **clean** pull of your repo (i.e., pull into a brand new directory), and then build and test your project.

<hr>

## Additional Resources

Local System and Compilation:
- Repo: https://github.umn.edu/umn-csci-3081-s21/shared-upstream
- Compilation: https://gcc.gnu.org/
- Linux quick reference: https://files.fosswire.com/2007/08/fwunixref.pdf
- Makefile Resources: https://www.cs.bu.edu/teaching/cpp/writing-makefiles/


Testing:
- https://github.com/google/googletest
- Unit Testing: https://martinfowler.com/bliki/UnitTest.html

Style:
- https://google.github.io/styleguide/cppguide.html
- https://github.com/google/styleguide/tree/gh-pages/cpplint
- https://www.python.org/downloads/

Documentation:
- https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

IDEs:
- Xemacs: https://www.xemacs.org/
- vi: http://www.lagmonster.org/docs/vi.html
- Atom: https://atom.io/
- Sublime: https://www.sublimetext.com/
- Eclipse: https://eclipse.org/


