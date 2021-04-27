# Lab 3081 Lab02 Docker & Compiling C++

# Getting Started
## Retrieve class materials and merge into your personal repository

Navigate to your repository.

    $ cd <path_to_your_repos_root_folder>

Now, we want to get the new class materials from the shared-upstream repository. Ensure you are in the _support-code_ branch by executing the _git status_ command.
```
$ git status
On branch <branch name>
Your branch is up to date with 'origin/<branch name>'

nothing to commit, working tree clean
```

The output should begin with the branch you are currently on. If it says _On branch support-code_, you are all set. (NOTE: If your status output does not look like above and instead this message is displayed "Changes not staged for commit", you will _not_ be able to change branches. Follow the instructions given by git to _add_ and to _commit_ these changes.)

Another way to check which branch you are actively editing is to run the _git branch_ command.

    $ git branch

A list of all local branches associated with your repository will be output. The branch name with a star * next to it is the active branch. If you are still in _master_, checkout the _support-code_ branch.  

    $ git checkout support-code

__What just happened?__ If you run the above command, you "switch" into the support-code branch. This means that git changes the filesystem to represent the state of files under the support-code branch. This could mean deleting files, adding files, or changing files, depending on how different the files in master are from the files in support-code. Since you were working in master on your first lab deliverable, there should be some minor changes when we switch to support-code. The code in your master branch is not changed, and it will be accessible again when you switch (i.e. _checkout_) the master branch.

Pull any updated materials into your _support-code_ branch.

    $ git pull upstream support-code

__What just happened?__ You pulled the files from our csci3081-shared-upstream repository's support-code branch into your local repository's support-code branch. Anything new in the shared-upstream repo is now a part of your local repo in this branch.

__Why didn't we do git pull?__ The default command in the Git workflow would indeed be _git pull_. However, that command uses the default target _origin_. For our work, origin is the target for your remote repository, repo-<your_id> residing on the github.umn.edu server. We set up csci3081-shared-upstream as a secondary remote target repository, with the name of upstream. To complete the pull action for that repo, we need to add the target name to the git pull command.

Now that we have the updates from our shared-upstream, let's add them into our own work in the master branch.

```
$ git checkout master
$ git merge support-code
```

> Note: If an inline editor opens with a merge message, you should be able to exit by pressing the escape key, then typing **:wq** to exit it. Some other inline editors may require a different key combination.

__What just happened?__ You changed back to having the master branch as your working project. You then merged the file contents and commit history from support-code to master. This adds the changes to our shared-upstream repo into your working branch master.

__Why do we have support-code?__ Technically, we could issue a command that takes these changes and merges them directly into master, without having to deal with our own local support-code branch. That's true, and we could do that. But, we wanted to A) make sure that students maintain a clean copy of the provided code on their local machine. If you make a mistake in your master branch, having the clean copy may be beneficial. B) give you practice in handling merges, since that will be a beneficial skill to have when we start making more complex branching structures during the project.

> Merge Conflicts?  
If you encounter any errors during the pull or merge steps above, you may need to resolve a merge conflict. Git will tell you which files have merge conflicts.  
It is recommended that you use a merge tool to help you handle these conflicts. The editor 'atom' has been recommended by the TAs for [resolving conflicts](https://flight-manual.atom.io/using-atom/sections/github-package/#resolve-conflicts)

# How to Run My Code?

Unlike some other programming languages, like Java & Python, C++ is not very OS agnostic.
This means that what kind of operating system you run the project in will force you to take different steps at times.
Because we recognize that everyone is working at home this semester, with a large variety of different types of machines, we've worked to make this project compatible with a number of different setups.
We will list the options below:

## *Vole3D* 
UMN provides Vole as a service [here](https://vole.cse.umn.edu/). 
Make sure you choose the 3D option so that you can see the results of your program running. 
This will open a remote control version of a CSELabs machine in your browser.
 
**Pros:** This is the most stable option, we will make sure that we always support this configuration, and there are a lot fewer things that can go wrong in this environment.

**Cons:** Sometimes laggy, requires a network connection. You are also limited by the network administrators regarding what you can do.

## Linux & MacOS
If you are running a Linux or a Mac machine, you can likely run most of this code with minimal setup.
However, we can't control what you have done on your machine, so it's possible that some things may not be compatible.

**Pros:** Native, basically no work involved.

**Cons:** May have compatibility issues if you've changed things.

## Windows: Git Bash w/ WSL2 backend
Windows machines are not Unix-based, so you will have a bit more set-up.
One option that you can follow is described below, using WSL2 for compatibility but running commands inside of Git Bash.

**Pros:** Least laggy Windows set-up, minimal difficulty

**Cons:** Git Bash isn't *exactly* bash, so commands you find online may not always work. You will sometimes run in to weird problems with line-endings as well.

## Windows: WSL2
After installing WSL2, you can open the wsl program as a command line, which will allow you to emulate a linux environment.

**Pros:** Comfortably emulates Linux

**Cons:** ***You MUST keep your files that you use in WSL and in Windows separate.*** You can get very nasty errors & slow run times if you don't. This limits what programs you can use with this set up.

### Any: SSH

On any machine, you can ssh in to the cselabs machines.

Doing so will provide you terminal access to the CSELabs machines, which will allow you to remotely execute all of your commands there.
The general syntax is `ssh yourx500@computer_name`, where a list of computer names can be found [here](https://cseit.umn.edu/computer-classrooms/cse-labs-unix-machine-listings).

You should enter the above command in to your terminal or command line (note that, on Windows, you may need to install additional tools like [PuTTY](https://putty.org/)).

If you're feeling adventurous, you can combine ssh with various programs on your computer to make it very powerful, but we are not explicitly supporting that in this class.

One such useful workflow involves using VS Code with SSH. This will allow you to edit files that reside on the CSELabs machines while using VS Code (a text editor) on your computer. To do this, download VS Code. On the left-hand side, click on the building blocks and search from 'Remote Development'. Install the first package you find, then restart VSCode.  

You can now use SSH inside of VSCode by clicking on the green arrows that should appear in the lower-left corner of VS Code. Select `Remote SSH: Connect Current Window to Host` in the dialog that appears. The first time you do this, you will have to type in the SSH command to connect to the computer, but in the future you will be able to select your computer from a dropdown.  

Note that if you follow this set-up, you will need to have an internet connection to get any work done, file navigation may be slightly laggy, and you will need to undergo (minor) additional set-up to view graphics for the project later in the semester.  


**Pros:** Basically no set-up right now, highly extensible if you want to get fancy. Can seamlessly switch between this and Vole3D.

**Cons:** Terminal only, will require additional steps to visualize the project later in the semester.

## Any: Virtual Machine or Dual-Boot

If you are so inclined, you can install an Ubuntu 18.04 dual boot or virtual machine on any computer you have.
This will likely take a lot of disc space either way. 
If you use a virtual machine, you might experience some lag while in the machine.
If you dual boot, you will need to restart your computer to switch to linux.

**Pros:** You can create a very clean environment this way, with minimal difficulties.

**Cons:** We're not supporting the set-up for these methods, which can be difficult

If you're a pro at networking, you can also set up various other workflows using ssh tunneling.

# Docker

NOTE: You only need to worry about installing Docker for yourself if you are using your own system (i.e. not Vole/SSH)!

Docker is a convenient tool for saving and loading virtual container.
When you write programs, these programs may have complex dependencies that need to be installed for your code to work.
What's more, the dependencies from one project may even conflict with one another.
Docker lets you isolate these dependencies in containers.

## Installing Docker

### *Installing WSL2 [Windows Only]*

*NOTE* : If you are running Windows 10 Pro or Windows 10 Educational, you can try skipping this section and the next section.
You can find which version of Windows you are running by typing typing 'About your PC' in your search bar (and hitting enter).
Your windows edition can be found under the 'Windows Specifications' heading.

The code in these projects is built off of Unix dependencies, which Windows doesn't have by default (MacOS & Linux should have no problems though).

Instructions for downloading WSL2 (and Ubuntu) can be found [here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
[This video](https://www.youtube.com/watch?v=ilKQHAFeQR0&list=RDCMUCzLbHrU7U3cUDNQWWAqjceA&start_radio=1&t=7) may also be helpful.

***Note that you will need Windows 10 for this - it's not supported on earlier versions of Windows. 
If you have an earlier version and cannot upgrade, it's recommended that you use Vole instead.***

### Installing Ubuntu [Windows Only]

After you have WSL installed, you can install Ubuntu from the Microsoft store. 
We recommend Ubuntu 18.04 ([here](https://www.microsoft.com/en-us/p/ubuntu-1804-lts/9n9tngvndl3q?rtc=1&activetab=pivot:overviewtab)), but other versions should work as well. Installation should be straight forward, make sure to follow the directions.

### Installing Docker

You can install docker [here](https://docs.docker.com/get-docker/).
Follow the installation directions on Docker website for your operating system.
**Once docker has been installed, you may need to restart your terminal (just close it and reopen it).
You can double check that it's installed by entering `docker` after the restart. 
This should print out a long stream of documentation.**

### Getting Started with Docker

The core component of docker is its containers, which are environments for you to run your code in.

Containers are constructed from images, which can be thought of like prototype containers.
You can create your own images or pull them offline.

In general, you can download a image using syntax similar to git:

```
$ docker pull <image_name>
```

You should download `busybox` this way now.
You can see all of your downloaded images using `docker images`.
Executing this should show `busybox` as your only image, unless you've used docker before.

To run a container, you use `docker run <image_name> <CMD>`.
This will create a new container based off of the image `<image_name>` and run the command you supplied in `<CMD>` inside of that container.
For instance, try running the command `echo "hello from busybox"` inside of a container created from the `busybox` image. 
What does it output?

Most of the time, you'll probably want to run the container in *interactive mode*, which will let you run commands inside of the container just like a normal terminal.

To do this, you simply write 

```
$ docker run -it <image_name> sh
```

### Using docker for this class

**The instructional team has put most of the heavy lifting with docker in a script that you can use for this course!**

To use it, `cd` in to the root directory of your repository that you created during the last lab. 

Once there, type the following command :

```
$ bin/build-env.sh
```
If you get a "bad interpreter error" when running this command, make sure to install the dos2unix command and run it on the build-env.sh file.
you can install dos2unix using 'sudo apt-get install dos2unix'.

This will run the `build-env.sh` script that is in the `bin` folder of your current directory - it may take some time to complete.

After that completes, run the `run-env.sh` script in the same folder as `build-env.sh` using similar syntax.

In general, you should only need to run `build-env.sh` once, ***but you should run `run-env.sh` before doing any work for this class each time.***
To exit the docker container, simply type `exit` in to the command line.

### Possible Error: Windows

*NOTE:* if either command gives you a cryptic error saying that the system cannot find the file specified on windows, open Powershell as an administrator and type the following lines 
```
Net stop com.docker.service
Net start com.docker.service
```

## C++

In this class, you will want to run all of the C++ commands inside of the docker environment in your github repository.
This helps us make our project compatible with the wide range of devices that everyone is working on.

The code provided for Lab02_docker will create an executable by compiling the provided C++ files using a makefile. Running the executable will generate 2 files that will be added to your Labs directory. A makefile manages the compilation process, which will be explored further in the next lab, so don't worry about the contents of the file right now.
```
$ cd labs/lab02_docker
$ make
$ ls
```

What just happened? You made lab02_docker your working directory with cd. You executed the makefile (named makefile) with make, which created object files with the extension .o, and the executable lab02.out. These files are displayed with ls.

```
$ ./lab02.out
$ ls
```

What just happened? You ran the executable with ./lab02.out, which generated 2 files private.pvt and shared.md.

Because we want private.pvt to stay private, we need to add a gitignore to this directory. You can either make a new gitignore which should ignore the same file extensions as the gitignore from the last lab, or you can copy your old gitignore to this lab's direction. A command you could use to do this would look like this:

```
$ cp ../lab01_git_basics/.gitignore .gitignore
```

Which copies the file specified as the first argument to the location and name specified in the second argument. Or you can accomplish this through any other means.

### Getting credit for this lab

Once you have completed the steps in this lab, you should have generated a .pvt and a .md file in your directory.
Push your changes to your repository (repo-<your_x500_here>) the same way that you did for lab 1, and, similar to lab 1, you will see a feedback file with your score.
You may upload multiple times.
