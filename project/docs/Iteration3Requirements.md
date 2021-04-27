# Iteration Three: Enhancing and Extending the Package Delivery System -- Part Two

## Iteration 3- VERSION 2, April 19, 2021 - Stricter unit testing requirements. 

## Iteration 3 - VERSION 1, April 19, 2021  - **NOTE, THE REQUIREMENTS IN THIS DOCUMENT ARE SUBJECT TO CHANGE. THERE WILL BE A CANVAS ANNOUNCEMENT WHEN THERE IS A CHANGE TO THIS DOCUMENT.**<hr>

| Date | Item | Description of Verification and Validation of Deliverable(s) |
|:----:|:-----|:------------|
| FRi, April 30 , 11:55pm | Incorporate a single feature in your package delivery system | inspection |

### Introduction

The purpose of Iteration Three is to extend the package delivery system and develop a useful optimizations or features. Your team will decide the feature to implement for this iteration. You will present your features as a final presentation for the course.  Below is a list of possible feature for your team to choose to implement. Contact the 3081 instructional team for approval if you would like to implement your own feature.  Please review the suggested features below:


|Feature | Description | Relevant Patterns (Suggestions) |
|:------:|:-----------:|:-------------------------------:|
|Entity Color Decorator|Use the decorator pattern to add color to any entity based on some feature (e.g. battery life, distance to destination, weight, etc…)|Decorator|
|Porch Thieves|Create a new entity that disguises itself as a different type of entity.  When a package is close enough, the porch thief steals the package and takes it home.|Decorator|
|Collision Avoidance|Make sure drones do not hit each other.  If drones are sharing the same graph, they should find alternate paths.  If drones must be on the same path, they should use the vertical dimension.|Strategy|
|New Scenario |Create a new scenario.  Verify that all functionality works in this new world, and add new actions (e.g. trolly car carrying passengers in San Francisco).  Create new entity types that are relevant to the new location.|Factory |
|Customers that Move |Allow the drone to deliver to moving customers.|Strategy, Observer |
|Drone Statistics | Collect drone delivery statistics based on the simulation (e.g. delivery time, packages delivered, distance travelled).  Store these in a CSV file or other mechanism (e.g. database).  Analyze the data and share how to better optimize the system. | Singleton |
|Remote Control | Add a way to control drones / customers / packages using the Command Pattern.  Perhaps create another interface (web based or console) for moving drones, scheduling packages, creating new entities.  (e.g.  keyboard arrow keys /  WASD) | Command |
| Recharge Stations / Drones | Add a way for drones to gain battery life.  They can either go to a recharge station or be given battery power from a recharge drone. A recharge drone is one that delivers power to a drone. | Factory |
| Internet Emulation | Break packages up into many pieces (packets) and allow a large number of drones to carry them to their destination over different paths (perhaps based on route congestion).<br> Store the calculated route information at each node in the graph to avoid recalculation. <br>For example, each node would store a map of destination (as key) to the next node (as value).  The tables are built whenever a route is calculated. <br>The packets will store the destination (not the route) and will be routed through the nodes based on the information at the nodes. Each customer will reassemble the package once the packets have arrived. | Composite, Flyweight, Strategy |
|Drone/Robot Pool | Allow for many drones/Robots in your simulation and each drone / robot can have different properties (weight, capacity, max speed, acceleration, etc…). See the included CSV files. <br> Add a model number for each drone / robot when creating it.  An example of JSON passed into create entity is as follows:<br>Set all the appropriate variables for your drone (notice that speed has been replaced with max speed and acceleration).<br>{ “type”: “drone”, “name”: “T-800”,***“model”:”Q36-01”***, “position”: [0,0,0], “direction”: [1,0,0] }<<br>Be sure to look up the specific model’s traits based on the included CSV files.  We encourage you to cache the results in a data structure so that you can look up the model attributes by model number when you create drones.| Strategy, Factory, Composite |
|Drone / Robot Functionality | Drones/Robots now have the following realistic limitations: <br>Carrying capacity (kg)<br>Maximum speed (meters/sec)<br>Drones/Robots can carry multiple packages, but the sum of the package weights cannot exceed the drone’s maximum carrying capacity.<br>Drones/Robots cannot exceed their maximum speed.|
|FAA Enforcement | Create another entity that enforces the limitations of the drone, in particular the speed of the drone. | |
|Other | Choose your own feature to implement.  Please check with the instructional team to verify that your extension is adequate or feasible through email. | |


### Team 

You will work with your team to complete this iteration. Iteration 3 team repos have already been created. Use the previous lab from iteration two to set up your iteration 3 team repo (including the settings regarding pull requests). ***Do not change anything in your iteration 2 team repo since it will be graded while you are working on iteration three.*** At the end of the iteration everyone on the team will evaluate the performance of each team member. The evaluation process will be used in determining the grade of each team member. 

### Final Deliverable --- Due Friday April 30th by 11:59 PM

### Make sure to have at least one scene file that your simulation works on, and put the name of that file somewhere in the mainpage so we don't miss it.

1. Implementation of a feature from the above list. 
       
2. Add a section in your Doxygen mainpage titled with the feature you implemented. A description of the feature you implemented and any design patterns used in the implementation and include pictures where applicable and possible. **Note which parts of the design and implementation were most difficult for you, and include any tips or advice on how to understand and implement the feature..** 

3. In your Doxygen mainpage add a section named: **Iteration 3 Team Documentation** that includes summaries of team meetings (minimum of three) and who was assigned a task to complete. 

4. Ensure all new classes and methods you have written are properly documented. All header files must document the classes and their methods using Doxygen, and all implementation (that is, \*.cc) files must have self-documenting code. **You do not need to document the web server code base.** 

5. Correct and update your UML class diagram from Iteration 2 to include the changes to your code including all classes you added to complete the iteration 3 requirements and their relationships to each other and the classes that previously existed in the simulation.

## Deliverables and Submission Process

>You will submit all your deliverables via GitHub according to the process specified lab 10. We will tag and pull your repository at the specified due dates and grade them according to the contents at that time.

>#### You must verify that your submission compiles on a cselabs machine and it is complete. You will receive zero or be heavily penalized if your code does not compile and/or we cannot generate documentation using Doxygen as specified in Lab 8 upon submission.

The schedule is very tight, and it is important that you keep up with the project. The project will continue to build throughout the semester, and if you get behind, it will be very difficult to catch up. For this reason, **late assignments will will receive the following penalities: 1 day late -- 10% deduction, 2 days late -- 20% deduction. A day is defined as a regular day of the week, thus if your submission is due on Friday at 11:59 PM and it is submitted on Saturday it is one day late. Submissions after two days will not be accepted**, but you will receive partial credit for partial completion of the requirements - so **ALWAYS MAKE SURE TO SUBMIT SOMETHING - SOME POINTS ARE BETTER THAN NONE**.

You can convert this requirements document to pdf using this tool: http://www.markdowntopdf.com/

<hr>

### Overview

In this iteration, you do the following development including:

- adding a feature to the simulation
- formulating unit tests with Google Test
- adding to the simulation class structure 
- ensuring coding style compliance
- augmenting the design discussion in your doxygen mainpage to include a discussion on your design and implementation of the feature your team implemented.
- augmenting the design discussion in your doxygen mainpage to include a discussion to include a section on your teamwork for this iteration
- modify/update your iteration UML design documentation to include the classes and methods you add or refactor in iteration 2.
- using Doxygen to document and generate documentation.
- Use git, and produce self-documenting code (i.e. good organization and naming conventions). 

Teaching staff (Undergraduate TA's, Graduate TA's, and Instructors)  will also be working diligently to provide the structure and support for development, testing, and documentation. Automation in unit testing, style compliance, in-house github testing, and documentation will make this an easier process, however it means that you will have to develop within the constraints of these systems. **Often there is a learning curve and a lot of systems trouble-shooting to get it all working, so start early!**

## Documentation and Code Implementation Requirements

**REQUIREMENTS you need to fulfill**

> This is just functionality. Along the way, make sure to document the code using Doxygen syntax in the header files, and self documenting code (as discussed in McConnell's text in Chapter 32) in your class implementation (\*.cc) files. and the main function.  

### Unit Testing with Google Test

https://github.com/google/googletest

Unit tests are essential in a large-scale project, because the entire code base can be tested regularly and automatically as it is being developed. In the strictest application of Test-Driven Development (TDD), the tests are written _before_ the code, which helps solidify requirements and write testable code.

A sample test file is provided in the /project/tests directory. This directory must be a sibling to your _src_ directory. When you _make_ the tests, they will generate an executable (in build/bin) which, when executed, displays a report of the tests. Use this file as a guide to your own testing. While the requirements for testing in Preliminary Turn-in #2 (more later) are rather light, you can expect a much more robust testing requirement in later iterations. Do not slack on making good tests for your code!

In this iteration, the testing requirements have been made more comprehensive and we have removed the previous exception of - "no need to test functions that overly rely on external classes". All public functions in all the classes require test cases as explained in the lectures and piazza posts. The only exception that will be given is that you don't require to write tests for delivery_simulation.cc. Also note that the SOLID principles will be given more weightage in this iteration, and thus you are advised to move logic from delivery_simulation.cc to appropriate classes. DeliverySimulation should just play the role of a facade and shouldn't be rife with important logic.

### Style Compliance

You may use the style guidelines suggested in McConnell or the following google style guide.

https://google.github.io/styleguide/cppguide.html

Consistency in code organization, naming conventions, file structure, and formatting makes code easier to read and integrate. There are many options with various merits, so it is up to the development team to establish these conventions, or, in the words of Kevin Wendt, an instructor for previous iterations of the course, "The only style guide that really matters is the one your boss uses." 

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

There are many free tools that you can use to create the UML including Doxygen (see: https://inneka.com/programming/cpp/how-to-use-doxygen-to-create-uml-class-diagrams-from-c-source/), and  draw.io (see: https://www.draw.io/). **Submit your UML as a pdf into the design/documentation assignment folder on Canvas.**.

#### Doxygen

Doxygen automatically generates documentation of class and code structure when you follow some simple conventions for commenting within your code (_see_ http://www.doxygen.nl/manual/index.html and https://caiorss.github.io/C-Cpp-Notes/Doxygen-documentation.html). You have had a lab on Doxygen (lab 8) and we will likely cover a bit more in class. To start with, look over the documentation provided with the code base to understand how to document classes, methods, parameters, and even _todo's_ and _bugs_ in your code. In lab 8, you learned how to compile with your Doxyfile and generate web pages. Please look over the generated web pages for missing and incorrect information. The requirements for Doxygen include:

- the file `project/docs/Doxyfile` to generate documentation (after you complete lab 8, you should have this in your `project/docs` directory).

- a _mainpage.h_ file that serves as the homepage of your automated documentation. The information that you added from iteration 1 should remain. You should have a mainpage.h file that you can extend in your `project/src` directory. 

- document all classes, methods, and functions that you add in interation 2 in their header (.h) files. 

-  Add a section in your Doxygen mainpage titled with the feature you implemented. A description of the feature you implemented and any design patterns used in the implementation and include pictures where applicable and possible. **Note which parts of the design and implementation were most difficult for you, and include any tips or advice on how to understand and implement the feature..** 

- In your Doxygen mainpage add a section named: **Iteration 3 Team Documentation** that includes summaries of team meetings (minimum of three) and who was assigned a task to complete

- The /html directory should *not* be in your repo in github.umn.edu - nor should your build directory, executable files, or object files.

> **As part of your fresh clone prior to submission, please also compile the Doxygen and look at the generated webpages.**

All of these elements of documentation will be assessed, accounting for a significant portion of your grade for each iteration (for this iteration - iteration 1, documentation will account for 1/2 of your grade). Think about these two extremes: 1) your code functions perfectly and you have almost no documentation - you will likely fail on this iteration; 2) your code is not functional and will only compile when you comment most of it out, but if you have complete, great documentation - you will likely get a decent grade on this iteration. **Get in the habit of creating the documentation along with the code.**

<hr>

## Assessment

Your software **must compile on a cselabs machine or it will not be graded, and you will recieve a zero for your submission**. We will not grade your project unless it compiles. As long as you provide a version that compiles, we will evaluate those aspects that are partially functional for partial credit. In other words, <u>comment it out if it breaks compilation</u>.

Your software will be assessed manually, following the build/run process described in your mainpage. Therefore you should make it clear how to run your code, and what was implemented in iteration 3 so the grader knows what to pay attention to. We **highly encourage** you too freshly clone your repo on a **cselabs machine** and to then `make clean` and `make`, followed by a run of your tests to confirm all is working well before the deadline.

This is the breakdown for point distribution:

20% : Iteration \#3
- 50% : Final Documentation
- 50% : Final Functionality/Code

### Documentation Assessment ( 50% )

#### Complete Iteration Documentation 

#### Design Document and UML

 A description of the feature you implemented and any design patterns used in the implementation and include pictures where applicable and possible. **Note which parts of the design and implementation were most difficult for you, and include any tips or advice on how to understand and implement the feature..** 
 
In your Doxygen mainpage add a section named: **Iteration 3 Team Documentation** that includes summaries of team meetings (minimum of three) and who was assigned a task to complete. 

Documentation includes a design overview of the the classes you're building provided in mainpage.h in /src and your final updated UML diagram in PDF file format. We will look for a well written and well organized document that clearly articulates the design. It must stand alone in the sense that anyone reading it should not have to look at code to understand the design. **This will likely require UML images and/or snippets of code included.** 

***Your final UML diagram from iteration 2 should be updated to include the class(es), methods, and relationships that you have added or changed during your iteration 3 development activities. The UML syntax you should use is specified and documented here: https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/. We will be looking for general proper use of UML syntax, and a correct depiction of the code structure of the existing project code (code from shared-upstream's support-code branch).*** 

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

Code functionality will be tested manually following your instructions on your mainpage. There should be minimal set up required to see the project at work, this means there should be at least one scene file which demonstrates what creative extensions you've made to the project.

<hr>

## Getting Started

AFTER reading this document, review Lab 13 Working with Teams. 

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



