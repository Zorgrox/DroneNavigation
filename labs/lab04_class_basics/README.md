# 3081 lab04 C++ Class Basics

## What You Will Learn

1. Create the header and source file for a new C++ class.
2. Create a constructor for a class.
3. Define public methods and private class members.
4. How to execute unit tests against your program using Google Test

### Retrieve Class Materials

Navigate to your repository.

```bash
% cd <path_to_directory_repo-userid>
```

You will again pull and merge the support-code branch from the remote shared-upstream repository. First, orient yourself to the branch that you are on and any uncommitted changes. The command

```bash
% git status
```

will output the branch you are currently working in and indicate if there are any changes locally that need to be committed and pushed. In general, you want to check the following:

1. If you are on your master branch and you have made changes that are not yet committed and pushed, you should probably do that before proceeding.

2. Move to the support-code branch with `git checkout support-code`.

3. `git pull upstream support-code` to grab the latest changes from the shared class repo.

4. `git checkout master` to move back to the master branch for merging.

5. `git merge support-code`

**_What just happened?_** If you run the above command, you "switch" into the _support-code_ branch. This means that git changes the filesystem to represent the state of files under the _support-code_ branch, which is likely to be different than they are in the master branch. This doesn't mean that you have changed the master branch! It simply means that the files currently visible to you on your system reflect what is in the current branch. After pulling the latest shared code into your local support-code branch, you switch back to the master branch exactly as it appeared before, and then you merged what you just pulled down from the csci3081-shared-upstream repo into the master branch. Now the master branch has both the work that you have done and the shared code.

**Why didn't we do _git pull_ when in the support-code branch?** The default command in the Git workflow would indeed be _git pull_. However, that command uses the default target _origin_. For our work, _origin_ is the target for your remote repository, repo-<your_id> residing on the github.umn.edu server. We set up csci3081-shared-upstream as a secondary remote target repository, with the name of_upstream_. To complete the pull action for that shared repo, we need to add the target name to the_git pull_ command.

**Why do we have support-code?** Technically, we could issue a command that takes these changes and merges them directly into _master_, without having to deal with our own local _support-code_ branch. That's true, and we could do that. But, we wanted to A) make sure that students maintain a clean copy of the provided code on their local machine. If you make a mistake in your _master_ branch, having the clean copy may be beneficial. And B) give you practice in handling merges, since that will be a beneficial skill to have when we start making more complex branching structures during the project.

As stated, branches are integral to Git workflow. To this end, the roles of each branch are made very clear below:

- `support-code`: This branch is essentially a landing pad for the support code base that we will be giving to you throughout the course (hence the name). When you want to pull any support code from the `shared-upstream` repo, you want to checkout this branch, pull from upstream with above command, then merge into whichever branch you want to develop on.

- `devel`: An optional branch for development. Here is where you can play around with code, add features, refactor old code, etc.

- `master`: Feedback will be published to this branch, but that's about it on our end. You can either treat it as a development branch, or mostly ignore it. Also, GitHub has decided to rename `master` to `main` for new repositories on Oct 1, 2020. While there is a distinct difference between the system git and the organization/webface GitHub, this should be noted to avoid future confusion.

- Future feature branches: Later on in the course, we will be expanding on the branching philosophy and introducing `feature` branches. These are singular purpose branches created for a single job. Good traits of a feature branch include a descriptive name and very isolated changes. Generally a feature branch will fork off from a development branch then be merged back into the development branch as soon as the feature is complete.

**Optional reading and last thoughts before "real" coding:** The following is a useful link further describing a successful git branching model. Just browsing the figures will give you a good mental picture of an effective git repo, and reading the entire article will give you a leg up on anyone in the industry that just googles whatever git command they need for a particular situation. <https://nvie.com/posts/a-successful-git-branching-model/>. Keep it mind that not all git workflows are the same, but this is a good reference for a traditional git workflow.

### What's in labs/lab04_class_basics

- main.cc:
  - This contains the main function, which creates a random cluster of points.
    - It also has a collection of helper functions to print the cluster and to display some characteristics of the cluster of points.

- Makefile:
  - This makefile is provided to allow you to easily build the executable to run this program, assuming you've created a proper point2.h and point2.cc set of files. It also provides for a _clean_ target, to ease removal of the resulting files generated by the build process.

- Makefile.test:
  - This makefile is used to run the unit tests provided for the class Point2. It should run as is on a cselabs machine. If you are on a personal machine, then you will have to set up Google Test to get it working. Google Test: <https://github.com/google/googletest>

- README.md:
  - You're reading this now.

- point2_unittest.cc:
  - This file is provided in case you'd like to make use of the Google Test framework and execute the unit tests against your code manually. Pushing your code to your remote repository does this for you, through the automated feedback mechanism.

### What You Will Add

- point2.h:
  - The header file for this new class. It should include the declaration of the constructor and the three class methods DistanceBetween, Quadrant, and Print.

- point2.cc:
  - The source file for the class definition.

### Building the Class Point2

<hr>
  **The primary goal of this lab is for you to build a simple C++ class to fulfill the interface as exhibited in the provided main.cc file.**
<hr>

Review _main.cc_ now to see how the class will be used. Notice the class methods DistanceBetween, Quadrant, and Print. A point should have an x and y component, both of which are private to the class, but there is no indication in the unittests or in _main.cc_ of how those are specified or used, thus implementation is up to you.

Notice that the method _DistanceBetween()_ is a class method. It calculates the distance between two points, but only 1 Point2 object is passed in. This means the self-referencing _this_ object is the other Point2 object.

The nominal distance between two points can be calculated using Pythagorean's Theorem. Keep in mind that although the x and y components of a Point2 object are private, they are private only to objects of different types. It means any Point2 object can directly access private components of any other Point2 object!

Quadrants for points are numbered 1 to 4 (as well as 0, for the edge case of a point on the origin [0, 0]), counter-clockwise starting from the upper right quadrant (e.g. point [1,1] is in quadrant 1). This is pretty straight-forward until you consider points on the axes -- which quadrants are those in? These requirements have been defined through the unit tests. Look at TEST_F(Point2Test, QuadrantBorder) in `point2_unittest.cc` and in the Set-Up at the top that defines the points used in that test.

### Executing Lab Code and Pushing Results

The code provided for lab04 will create an executable by compiling the provided
C++ files using the _Makefile_. The resulting executable, _cluster_, should be created if your point2.h and point2.cc files do not cause syntax errors.

If necessary, change directories to the labs/lab04_class_basics directory.

Build the executable using the makefile and run the executable.

```bash
% make
% ./cluster
```

### Use Google Test Framework to Verify Correctness

You may or may not have noticed another directory that was downloaded when you pulled the latest updates from the shared-upstream. The googletest directory includes a variety of files which enables you to build the google test framework and utilize it to execute unit tests against your codebase. These tests are helpful in ensuring that your code is working as expected. This directory, in conjunction with the Makefile.grader and point2_unittest.cc file, can be used to evaluate your program locally, just as the grading script will do on the grading server.

If you wish, you can make use of the framework now. To do so, you need to merely using the test version of the Makefile.

```bash
% make -f Makefile.test
```

**_What just happened?_** Built the Google Test framework objects and ran our unit tests (point2_unittest) against our complied code.

```bash
% ./point2_unittest
```

**_What just happened?_** Executes the unit tests and displays the testing results. If all goes well, you should see the tests run and pass (in green text). Otherwise, you'll see some tests fail and get the dreaded red text.

Again, once you're satisfied in your program's correctness, it's time to submit your work. But, one last task first: making sure no additional files are being pushed.

```bash
% git status
```

This should list all the files that have changed and/or are untracked. As long as the other files listed are the two files you added for the Point2 class (point2.h and point2.cc), you're good to go!  If other files are also listed as being ready to stage for commit, you may need to update your .gitignore to make sure we don't push files that we shouldn't be committing. Once you're ready to commit just point2.h and point2.cc, continue to the next section.

### Add Changes to Repo Locally and On Server

You need to _stage_ all changes to the repository, which prepares those items to be permanently part of the repository. 
When you _commit_ those changes, they are saved to your local repository, which lives in your cselabs account (or your
personal computer if that is what you are working on). When you _push_ those changes, they will be copied to the repo on the server. The difference between
_commit_ and _push_ is what separates git from centralized version control systems.

```bash
% git status
% git add -A
% git commit -m "add(lab04): Adding lab04 deliverables"
% git push
```

**_What just happened?_** Double-checking the files to be staged using the _git status_ command. All of the tracked changes are staged with `git add -A`. Those staged changes were committed to your local repository and tagged with the message that follows `-m`, then pushed to the server in your remote repository.

If you were going through the motions of good git usage and you were working out of a development branch separate from `master`, now is when you would add these changes to `master` for grading:

```bash
% git checkout master
% git merge <development-branch-name>
% git push
```

### Reading the Feedback

Pushing to the server triggers the automated grading system. Soon your repo will contain a feedback file, letting you know if you have passed all tests of the assignment.

```bash
% git pull
```

You are welcome to keep changing and committing this lab up to the deadline. A new feedback will overwrite the previous one after each commit. Don't forget to pull after each feedback file is posted.

THIS LAB IS COMPLETE.

Congratulations!
