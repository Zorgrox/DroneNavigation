# Lab 13 : The Process of using Git for Team Development of the Project: Merging, Branching, and GitHub Issues

# Setting up your team structure

| Role | Description |
|----------|-------------|
| Development Lead| Makes all the major decisions for design and implementation. Not everything needs to be the development lead's idea, but this person should decide if there are competing design ideas|
| Scheduler | In charge of scheduling team meetings. https://www.when2meet.com/ is a great application. Also in charge of setting up the shared discussion environment. I.e. Discord, Slack, etc.|
| Reporter | In charge of group work and discussion documentation (part of the mainpage.h). This person should divide up the group documentation work (meeting minutes, design discussions, project calendar/schedule information, etc. ...)|
| Project Manager | Keeps team members on track so that deadlines are being met. Manages the project timeline and plan (Should be part of the mainpage.h documentation)|


# Lab Summary

In this lab you will be introduced to your team git repository for iteration2 and learn about how use github to develop code as a team. You will be able to do a portion of the lab alone, and a portion should be done after some discussion with your partners.

For the solo portion of the lab you will create an issue, make a feature branch to solve the issue, then merge that feature branch back into `devel` using a _pull request_.

For the portion that should include some communication with your group, you will be copying a working iteration1 solution into your team repo. You need to correspond with your team and determine what iteration1 solution you would like to use.

# Introduction to team repo

For iteration2 you have been added to a team which includes your group members as well as a repo for you to work in. The repo is named `repo-iter2-<section_number>-<team_number>` where section number is either 01 or 10, and team number has a leading 0 if your team number is a single digit.

## Setting up your team repo

To set up the repo we want to:
 - Create `devel` and `feedback`.
 - Add `shared-upstream` as a remote.
 - Pull `shared-upstream` to `devel`.
 - Set some options for `devel` and `master`.

If it looks like your repo has already been set up by a teammate, please look through these directions to ensure that everything is correct. If you get stuck on a step please let a TA know.

We are going to be working with mostly just `master` and `devel` branches to start with, though more branches will be made as your group works on the project. `feedback` will be where feedback from tests and the like are pushed.

## Create the `feedback` and `devel` branches

Next just create the 2 other branches you need `feedback` and `devel`. If you do not remember how to do this refer to previous labs or use google.

## Set `shared-upstream` as remote.

To do so, follow the instructions from lab 1. Then pull the shared upstream into `master`

## Finally set some options in `master` and `devel`

Open the repo in your browser, select options in the top right and then branches on the menu that appears on the left.

We want to require _pull requests_ to be reviewed by teammates before they are integrated into your branches.

Click "Add rule" to add a branch rule. Then type the name `master` as the name pattern, and select "require pull request reviews before merging". Set the number required to 2 for `master`. Then do the same thing for `devel`, but this time set the number required to 1.

# Done with setup!
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

You can mainly use the default labels if you wish, but you need to at least add the label `priority`. See section Academic Honesty at the end of this document.

Github provides a convenient and integrated method for keeping track of the needed modifications using **_Issues_**. As part of the development requirements of iteration2, we expect that you will be using these Github issues to track bugs, keep a list of feature enhancements, and needed refactorization.

Refer back to Lab 10 which contains examples of good commit messages for the project.

**The process of significant code modification should start with the creation of an issue that has an appropriate label attached to it** (in the example above, the label "bug" was used). The next step is to create a branch in which to address the issue.

> Note that you should probably only make one branch at a time so that you aren't trying to merge multiple branches into one. Create as many issues as is needed to track everything, but try to address only 1 at a time.

# Creating a GitHub Issue

The first deliverable of this lab is the creation, assignment, and resolution of your repo's first few issues.

## Create your issue

To walk through the process we will create a simple issue. In this case, you must add your x500 to the README in your repository. Create your issue by using the GitHub browser. Click on the `Issues` tab next to the code tab near the top of the website. Then click the green `New Issue` button. Next type a descriptive title and description. Before you submit your issue, Label it with the Labels option on the right, you can choose whatever label you think it appropriate. Then use the Assignees tab on the right to assign yourself the issue.

## Create and push a feature branch to address your issue

Create a branch **with the specified name format**. **Remember** it should be branched off `devel`. Add your change, then review the below commit message guidance.

## Commit Messages

Refer to the _git usage_ pdf from lab 10 in the `shared-upstream` repo, which is a document put together by John Harwell, a former TA for this course.

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

The template provided in the git usage document from lab 10 can be added to git so that when the editor opens, you will see that content. To add the template, save the text preceded by '#' in the pdf as a file (_~/.gitmessage_ is the convention) and add to your git configuration:

```bash
git config --global commit.template ~/.gitmessage
```

The general style is to list the type of modification, in parentheses list the impacted files, then provide a short description of the change. The lines that follow provide specifics. Notice the \#1 in the message. When you use the issue number in the message, Github recognizes and adds the commit message as a comment to the issue creating a link between the issue and any related commits and branches. More on this [here](https://help.github.com/articles/closing-issues-using-keywords/).

## Commit your change

Decide on a reasonable commit message and commit your change. Also push your new branch at this point. (Refer to previous labs or google if you don't remember the exact command. Being able to look up tool usage is an important skill.)

## Submit pull request

Once your branch is pushed, you want to merge it with `devel`. To do this formally, you submit a _pull request_. A _pull request_ is a _request_ that the repo _pulls_ the changes from a branch you modified to a branch that you specify. You can do this from the Github interface under Pull Requests. Then a team member can _accept_ the pull request to merge the branches. **Make sure your pull request is into the _devel_ branch - select from the pulldown menus.** If there are currently pull requests waiting acceptance, you should review those and make sure they add their x500 to the readme. If they look good go ahead and accept them. You can consider yourself to be done with the solo portion of the lab when there are no waiting pull requests, and you have submitted your own pull request.

Go to Github and look at the Issues. Close any issues that have been fixed by clicking on the _Close issue_ button at the bottom.

We would normally suggest that you delete the branch, but then we won't be able to see your history of using branches. **DO NOT DELETE YOUR BRANCHES!!!**.



# IMPORTANT: a note on academic honesty

Only **one** person should be assigned to each `priority` task. 

***Clarification: Assign a single person to be the lead on a priority. This person would be responsible for getting the priority done for your team. This does not mean your other team members cannot assist in the solution.***

Completing work on a `priority` task that you are not assigned to without documenting it is like doing someone else's homework. However we want you to still be able to work together, since peer programming is a very useful skill. Therefore when you work with someone on a `priority` task, that work should be documented with the following format:

Create a file named: `<priority-task-name>-groupwork.txt`

Whenever you work together add:
 - The date.
 - Who you worked with.
 - What you needed help with. (2-3 sentences)

Then that file should be uploaded when you complete the `core` task. If you need to go back and fix or restructure something relating to that task, the person who was originally responsible for the task should do so, and update the document if necessary.

We encourage you to work together, we just need to make sure that everyone is contributing. Thanks!

# Copying Iteration1

For this step, **first contact your groupmates!** Together you need to decide what iteration1 solution you want to use. For the purposes of beginning on Iteration 2, you need a solution to Iteration 1 that _passes all the assessment tests_. So copy a solution that meets that criteria if you have one, otherwise you will need to choose which one to copy and work as a team to fix the bugs.


## Parting Thoughts

Keep in mind that GitHub Issues are there to remind you what needs doing and fixing. This means that you use it like a todo list, writing things down as they occur to you.

It probably took you awhile in this lab to add the issue, make the branch, then merge it back into devel after the changes were made. This will go very quickly once you get in the habit, and we think you will eventually appreciate the documentation of the changes that have been made and the ones that still need to be made.

If you are addressing anything substantial, follow this full process of issues and branching (and it might involve multiple issues and branches). But you don't have to do this _every_ time you make a change! If you have something minor (like fixing a typo) -- skip making an issue, make the change in the devel branch, and use the command line for commit messages. The important part is to be consistent.
