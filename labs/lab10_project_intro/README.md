# Base Version of the Package Delivery System Project for 3081W and using Git for software development

This lab provides you with the base code (Initial Version) of the Package Delivery System project for 3081W this semester. The objective of this lab is to get you oriented with the visual version of the Package Delivery System and how to effectively use github for software development. You will be working on the project for the majority of the semester.

---
## Git for Development of the Project: Merging, Branching, and GitHub Issues

In this portion of the lab, you will prepare the iteration1 code (in the _project_ folder) and learn about how to develop code using best practices. The project base code will be added to your repo and you will establish a system for using Github _issues_ and creating branches to track and address those issues.

### Git usage document

There is an informative guide on the use of git and branching that was developed by John Harwell, a former teaching assistant for this course. Please review this because, as part of project assessment, we will be looking at your use of _issues_, branching, and commit messages. This guide can be found in **_git-usage.pdf_** in the lab10_project_intro folder.

### Branching Philosophy

When working on a software project, it's important to follow similar workflows so everything can run smoothly with no conflicts. Here we will outline the roles of the `master` and `devel` branches.

- **`master`**: Always contains 100% functional, working code. Push to this branch only for "releases," or in our case the submission of a complete iteration. Any time someone clones your repository and gets your master branch, they should *always* get a working version of code (even if it is not the most up-to-date, which could live on your _devel_ branch). For this class moving forward, the __master__ branch will be limited to the submission of project iteration items.

- **`devel`**: Devel should **ALSO ONLY HAVE WORKING CODE**. It will be used as the base branch for _feature_ branches, which are introduced in a moment. If you break `devel` and it no longer compiles, you will hinder the rest of your project development until you fix the bug. The general workflow should be: create feature branch from `devel`, add feature/fix bug, merge feature branch into `devel`. As such, you shouldn't be working/committing directly to `devel` at all.

- **Feature branches**: These are the branches that should contain the actual development work. They should be named something specific (i.e. not just feature/phase2, but feature/phase2-widgetA-scaffolding). Keep your commits on these branches focused on the issue and make relatively few, unless the complexity of the feature warrants more. Resist the temptation to follow multiple paths and address multiple issues on a single feature branch. Instead, open an issue in github to track what you have found/want to do (See [Github Issues](https://guides.github.com/features/issues/)), and continue on with the work of the feature branch.

### Getting Started with devel

**Start preparing your repo.**  If your local repo differs from the server, you should commit and push before starting this process. In your `repo-<username>` repo:

```
git checkout master
git checkout -b devel
git push --set-upstream origin devel
```

`git checkout` is the command to change your local directory/repo to reflect the code in the branch you are checking out. By adding the flag `-b`, you are creating a new branch with the name that follows. This will be an exact copy of whatever is currently in your local repo. Now any modifications that you make in this new branch will stay in the branch until you merge it with another one.

Branches have to be pushed to the repo to be available to others (and to you on another machine). For the first push, you have to specify where the branch needs to go. (If you do `push` without the added flag "--set-upstream", git will tell you exactly what you need to type to push to the server.) Once you have done this initial command, only `git push` will be needed.

After you have pushed the branch, you can move between branches using checkout without the -b flag. You can seamlessly move between branches in your local repo.

To confirm which branch you are currently working on and to see a list of all branches use `git branch`.


<hr>

### Feature branch naming format:

```bash
<issue_label>/<issue_number>-descriptive-title
```

When you create your first issue below, you'll learn how to label it. When creating a feature branch you should use the above format where <issue_label> is replaced with the label of the issue the feature branch addresses. Additionally, each issue will have a number, which you should use in place of <issue_number>. Then the rest of the feature branch name is a descriptive title, separated with dashes.

Here is a diagram depicting the branching philosophy visually. In our case, the far right blue branch is our `master` branch, yellow is our `devel` branch, and pink are our Feature branches.

<p align="center"> <img src="branching_model.png" alt="github issues" width="70%"> </p>

The following are git resources for you to reference. The first resource lets you see a graphical representation of a git sandbox where you can model the workflow outlined above. The second link is a commonly referenced git branching philosophy resource which has been linked in at least one previous lab. The diagram above is also from that link. Feel free to check out either in more depth if you feel so inclined.

https://learngitbranching.js.org/

http://nvie.com/posts/a-successful-git-branching-model

# GitHub Issues

As you develop your code, you will encounter a range of modifications that need to be made to the code, whether you are adding functionality, fixing it, or refactoring. More specifically, you might categorize the needed modifications as such:

| Category | Description |
|----------|-------------|
| Feature | An actual feature (i.e. adding new functionality to the code).
| Refactor | Refactoring existing code. Does not change behavior.
| Bug Fix | Fix a bug that was found in the code.
| Style | Updating/fixing code style (i.e. making it Google style compliant, for example).
| Doc | Adding/updating documentation for the code.
| Chore | Doing miscellaneous grunt work, such as file moving, renaming, etc.

You can mainly use the default labels if you wish, but you need to at least add the label `core`. This is specified [here](#individual_grades)

Github provides a convenient and integrated method for keeping track of the needed modifications using **_Issues_**. As part of the development requirements of iteration1, we expect that you will be using these Github issues to track bugs, keep a list of feature enhancements, and needed refactorization.

Below is an example using issues to track bugs in a project:

<p align="center"> <img src="issues.jpg" alt="github issues" width="30%"> </p>

**The process of significant code modification should start with the creation of an issue that has an appropriate label attached to it** (in the example above, the label "bug" was used). The next step is to create a branch in which to address the issue.

> Note that you should probably only make one branch at a time so that you aren't trying to merge multiple branches into one. Create as many issues as is needed to track everything, but try to address only 1 at a time.

# Creating your first GitHub Issue

The first deliverable of this lab is the creation, assignment, and resolution of your repo's first few issues.

## Create your issue

To walk through the process we will create a simple issue. In this case, you must add your x500 to the README in your repository. Create your issue by using the GitHub browser. Click on the `Issues` tab next to the code tab near the top of the website. Then click the green `New Issue` button. Next type a descriptive title and description. Before you submit your issue, Label it with the Labels option on the right, you can choose whatever label you think it appropriate. Then use the Assignees tab on the right to assign yourself the issue.



## Create and push a feature branch to address your issue

Create a branch **with the specified name format**. **Remember** it should be branched off `devel`. Add your change, then review the below commit message guidance.

## Commit Messages

Refer to the _git usage_ pdf in the `shared-upstream` repo, which is a document put together by John Harwell, a former TA for this course.

As part of good documentation, it is important to record how the code was modified from the last commit. The git usage document outlines a template and offers a few examples. When making a substantial commit, you need to **NOT** use the `-m` flag so that your configured editor opens for you to edit. This allows you to add more detail than you would be able to with the `-m` flag.

>The default editor is vim. If you want another editor, see the git usage document for how to change that.
>Make sure to let your TA know if you reach a dead end.

When you do this, you will notice a series of lines preceded by \# that include very useful information about the status of your repo. A little further down in the document there are directions on how to take the template in the git usage document and add that to the text that appears when your editor opens.

Now you want to add the short message at the top, as well as some more extensive comments underneath that.

```text
fix(files): fix #1 <short description of commit>

- Multiple lines of description
- Lists all the important elements that have been changed
- etc.
```

The template provided in the git usage document can be added to git so that when the editor opens, you will see that content. To add the template, save the text preceded by '#' in the pdf as a file (_~/.gitmessage_ is the convention) and add to your git configuration:

```bash
git config --global commit.template ~/.gitmessage
```

The general style is to list the type of modification, in parentheses list the impacted files, then provide a short description of the change. The lines that follow provide specifics. Notice the \#1 in the message. When you use the issue number in the message, Github recognizes and adds the commit message as a comment to the issue creating a link between the issue and any related commits and branches. More on this [here](https://help.github.com/articles/closing-issues-using-keywords/).

## Commit your change

Decide on a reasonable commit message and commit your change. Also push your new branch at this point. (Refer to previous labs or google if you don't remember the exact command. Being able to look up tool usage is an important skill.)

### Merge with devel

If you are satisfied with the results (for this lab, this means that the project builds successfully after the renaming is complete), you want to merge this branch with _devel_ (not with _master_). You can do this in 2 ways. If you want to take a trial run or if someone else is in control of merging branches, you can submit a _pull request_. This is a request to pull in your position branch into the devel branch. You can do this from the Github interface under Pull Requests. Then you can _accept_ the pull request to merge the branches. **Make sure your pull request is into the _devel_ branch - select from the pulldown menus.**

Command line is easier and faster, although the pull request will give you more information about the impact of the merge.
```
git checkout devel
git merge --no-ff fix/01-<short description of bug>
git push
```

The _--no-ff_ option tells git not to do a fast forward merge, and actually create a merge object, which is just a technical way of saying making it easier to roll back changes that break things.

> **Always** branch off of _devel_ and **always** merge back into it.

Go to Github and look at the Issues. Close any issues that have been fixed by clicking on the _Close issue_ button at the bottom.

We would normally suggest that you delete the branch, but then we won't be able to see your history of using branches. **DO NOT DELETE YOUR BRANCHES!!!**.

# Project Introduction

### Resources

It will be helpful to refer to these C++ style guides as you work on the project. Choose a style and be consistent throughout the project.

- Google Style Guide : https://google.github.io/styleguide/cppguide.html
- McConnell Style Guide : Chapters 31 and 32

### Directory Structure

The directory structure for this lab is identical to that of the project.

- `project`:
   - directory that contains all the project subdirectories. The project subdirectories contain the source code, tests, executables, and documentation for the Package Delivery System.

- `project/docs`: Where all your documentation is typically stored, including your Doxyfile

- `project/src`:
  - Most of the source code (.cc) for the Package Delivery System is located here. Do not save your files with a .cpp extension, use .cc instead.

- `project/include`:
   - Most of the header files (.h) for the Package Delivery System is located here.

- `project/tests` : directory where you will create and build your unit tests using google test.

- `project/web`: HTML / CSS / and JavaScript code used by your browser - When loaded by the browser with the web-server running, it enables you to configure and run the Drone Delivery System from your browser.

- `project/makefile`:
  - Used to create the simulation executable

  - Type `make` to build the system and its executable

  - Type `make test` to make executables that test certain elements within your system

  - Type `make clean` to remove all existing object, executable, and test files
  
- `project/bin`: Contains shell scripts that make your life easier. *These should be executed while in the `project` directory. i.e.: `./bin/run.sh`, not `cd bin && run.sh`*
  - `run.sh` runs the server when on Docker or Vole

  - `setup-server.sh` - Sets up your server on SSH or CSE Lab machines

  - `server.sh` - Runs remote web server on SSH or CSE Lab machines
  
  - `test.sh` - Runs the compiled google tests in `project/tests`

  - Read the Readme.md file located at  https://github.umn.edu/umn-csci-3081-s21/shared-upstream for instructions on executing and running the project.  

---

## Generating the documentation

0. Copy the additional project files from the lab directory to the project directory. `drone.h` should go to `project/include` and `drone.cc` should go to `project/src`.

1. _pull_  new code into your support-code branch on your repo.

2. _merge_ the new lab code into your devel/development branch.

3. _cd_ (change directory) in  to the `project` directory.

4. Open the **README.md** file in the top-level of your repo/shared-upstream, follow the instructions to build your project.

5. _cd_ to the `project/docs` directory and run `doxygen Doxyfile` to generate the documentation

6. View the generated files by opening the `index.html` file in the `docs/html/` directory.

---

## Code Explanation

What we will be providing you with is the base code for the Package Delivery System. The simulation will consist of entities like drones, customers, packages, etc. that you will have to design and implement according to the specifications given.

---

## The Lab Assignment

### Build the Package Delivery System and run it

---

0. (If you haven't already) Copy the additional project files from the lab directory to the project directory. `drone.h` should go to `project/include` and `drone.cc` should go to `project/src`.

1. Open the **README.md** file in the top-level of your repo/shared-upstream

2. Follow the instructions to run the Drone Delivery System

3. Take a look at the system in a browser

## 4. Kill the server by clicking the kill button or `ctrl + C`
###  - Please do kill the server, or it may take unexpected computer resources and you might get an email from CSE staff if you leave it running.

5. Make the tests via the Makefile and run them with `bin/test.sh`. View the results.

## Coding exercise

By now you should have successfully seen the simulation running (albeit with no entities) and seen the tests execute (and fail). We will now add 
code to the project so that we can see a drone in the simulation, and pass the google test.

The method that we will go over in the following section is the fastest way to get the simulation to display a drone, and may not be the most extensible or well designed. Feel free to refactor any/all of your code at a later date. And keep in mind that this lab is complete **when you get the simulation to display a drone and pass the google test, however you accomplish that*.

## Creating a Drone class

In the lab10 folder, you have been given a skeleton for both `drone.h` and `drone.cc`, however neither is complete. Review them now, paying close attention to the comments `//TODO for lab10`.

The Drone class inherits from the EntityBase class, and declares/defines all the functions from the IEntity interface that is needs in order to be a concrete class. A few things are missing however. The Drone class needs some member variables, at least a string for the name of the entity, and two std::vector<float>s for the position and orientation. Additionally, the Drone class needs GetName(), GetPosition(), and GetDirection() return values defined. Finally, the Drone constructor needs an additional few lines of code, in order to save the input position and orientation vectors, as well as assigning a default name (this can be anything you want).
   
If you have addressed all of the `//TODO for lab10` comments, then you are ready to move to the next section.

## Using the Drone class in DeliverySimulation

The last step in order to view the Drone class is defining a couple of the functions in `delivery_simulation.cc`. For your project, you will need to implement a composite factory which offloads the creation logic of your entities. In this lab, we will directly create and return a Drone in the CreateEntity method of DeliverySimulation. View that function now and read the `//TODO` comment.

We only want CreateEntity to return a Drone if the type as defined in the json is "drone". If that is the case, then we want to extract the position and direction from the json and use those to create the Drone that we then return. Pay attention to how JsonHelper is used in this function, you will need to use it more later.

Review the documentation (or `delivery_simulation.h`) to figure out what each string of ???'s should be. Then check the parameters of the Drone constructor to figure out what order the arguments should be passed in to successfully create a drone. You can view the actual json that will be passed into your function in the file `project/web/scenes/umn.json` lines ~5-18, in the "parameters" field.

Finally, the last step of getting a Drone to appear in the simulation is to define the function AddEntity in DeliverySimulation. In this function, you simply want to add the IEntity* to the entities_ member variable of DeliverySimulation. (Don't overthink this step, it is very simple. Google "how to add element to vector c++" if you don't remember the function you need to use).

## Ensuring your code passes the google test

Refer to the above instructions to make sure your code passes the google test. If it doesn't, your code likely won't display the drone correctly. Take this opportunity to debug, and try to find where something went wrong. If the issue eludes you, ask for help from a TA.

## Ensuring a Drone appears in the simulation

If you have addressed all the `//TODO for lab10:` comments in the given code, and followed the steps above, and passed the google test. Your code should show a drone when you run it using the instructions above. You can left click and drag to rotate the camera, right click and drag to pan, and scroll to zoom in and out. Take a moment to look around the scene for your drone. You can also use the drop down menu in the upper right to help locate the drone. Click on "Select entity..." under "Change View:", then click on "drone". This should center the camera on the drone. If "drone" isn't an option and/or you can't find your drone in the scene, it likely isn't being rendered. Take a moment to double check your code, and if you can't find the issue seek help from a TA.

## Final words regarding the project

You have now created a drone in the simulation, but the project is far from complete. This code will not be the final code, so don't feel bad about refactoring your code. For instance, you *must* change the CreateEntity function at some point to add the composite factory, but you can also think about: using your own Vector3 class for position/orientation representation in the Drone class, implementing some of the IEntity interface functions in EntityBase instead of Drone to avoid duplication, and many others. Work that you put into thinking about the project **now** will make actually programming the project later **easier**.

---

Push your code up to your repository for feedback (don't forget to add the new files and commit before pushing...).

---
# Note on feedback regeneration

## To trigger a feedback regeneration for this lab, you must modify a (any) file in `labs/lab10_project_intro`
The feedback will check your `devel` branch to ensure that your code is compiling.

The feedback server looks for changes in that folder and only regenerates if something within it has changed. Since the work for this lab will be done in `repo/project/`, it will not regenerate automatically when you change files in that directory.

If the feedback does not update after you push, it is either the same as before or the bot is down. Please check to be sure that you think the bot is down before notifying us.

I would recommend that you just make a small change to the this file (e.g. add a word) to trigger the feedback regeneration!


---
## Documentation Requirements
### For this lab:
  - Add detailed Doxygen comments to header files: https://www.doxygen.nl/manual/docblocks.html
    - We recommend that you use the Javadoc Style shown in the given link
    - Recommended commands: @brief, @param, @return
    - Add comments that would be useful to a new programmer joining you in this project. Things like: a few words on HOW the function works, WHEN the function is/should be called, possible modifications for the function, etc.
  - Write self-documenting C++ code according to the guidelines specified in chapters 11 and 32 in McConnell Code Complete.
  - Make sure your code is either Google Style compliant or use the style guidelins in McConnell. Just be consistent throughout the project.

### Project Documentation:
  - For project submissions, you are required to do all the documentation mentioned above to receive full credit on your submission.

### Congratulations, you have started the CSCI3081W project for Spring 2021!!!
