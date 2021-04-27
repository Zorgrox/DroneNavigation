# 3081 Lab03 C++ The Build Process and Makefiles

## What You Will Learn
1. Reviewing how to retrieve new class material and merge them.
2. Basic commands for compiling and linking a C++ program to build the executable.
3. How Makefiles compile and link C++ programs.
4. How to build a Makefile to automate the build process.

## Getting the Code
As you continue to use git and GitHub, you might want to learn some good branching habits. Since you already have a **support-code** branch, navigate to your repo and checkout to your **support-code** branch. Additionally, we want to pull from the remote that we set up in lab 01.
```
$ git checkout support-code
$ git pull upstream support-code
```

As a result, your **support-code** branch should have the most recent files from the shared-upstream that we provided you. Feel free to update your repo on GitHub by adding, committing, and pushing these new files to your repo.

**IMPORTANT:** From here and until said otherwise, we want to do our labs on the **master** branch, so in order to do that we want to merge your **support-code** branch with the **master** branch. In order to do that, we want to checkout to our **master** branch, then use the merge command. The merge command takes a parameter that allows you to choose which branch you want to merge into your current branch.
```
$ git checkout master
$ git merge support-code
```

As a result, we should have successfully merged the **support-code** branch into our **master** branch.
> Note: If an inline editor opens with a merge message, you should be able to exit by pressing the escape key, then typing **:wq** to exit it. Some other inline editors may require a different key combination.

**Please make sure you are working on your master branch because this is where the grading bot will check!**

### What's in labs/lab03_build_process?

This file:

 - `README.md`

Other files to be used and not modified:

 - `decoy_duck.h/.cc`
 - `duck.h/.cc`
 - `main.cc`
 - `mallard_duck.h/.cc`
 - `mute_quack.h/.cc`
 - `quack_quack.h/.cc`
 - `quack_behavior.h/.cc`
 - `rubber_duck.h/.cc`
 - `squeak_quack.h/.cc`

Review these files, especially if you're looking for more examples of how the "has-a" relationship works, handling pointers and using delete, or just general C++ class syntax.

### Understanding the Build Process

The build process is the combination of compiling and linking to build your executable. Each source file is individually compiled to create an object file. Then all object files are linked together, whereby all symbols are resolved and the executable is created. We will first look at the commands to complete this process, then begin the real work of this lab which is to build a Makefile to automate it.

Navigate to the `lab03_build_process` directory. Compile a couple of the source files to create object files.

```
$ g++ -c -o decoy_duck.o decoy_duck.cc
$ g++ -c -o main.o main.cc
$ g++ -c duck.cc
```

__What does all that mean?__
- `g++` : call the gnu c++ compiler
- `-c` : a flag to indicate compilation only, as opposed to linking
- `-o` : a flag stating to output to the filename that this precedes
- `main.cc` : the last filename is the one to be compiled

- If `-c` is not provided, both compilation and linking will occur.
- If `-o` is not provided, the compiler will use the filename from the `.cc` file. Notice that `duck.o` was created in that way.

### __A side note: CAREFUL, do not follow the -o with `main.cc` because then you will be indicating to output a file named '`main.cc`' and you will overwrite your original `main.cc`!__

Notice that each file is independently compiled, even though there are interdependencies among them. If you look in the .cc file, there will be a `#include <filename>.h` statement which essentially inserts the text of `<filename>.h` at the location of the `#include` statement. Compilation will create symbol tables for all classes, variables, functions declared within those header files, but with no associated address for the definition of those elements. When the files are linked, those dependencies will be resolved and the definitions of the various objects will be included in the complete program.

Just from these few lines of compilation commands, you can see that you really do not want to use the command line for building your executable, especially when there are many files. Before venturing on to the Makefile to automate this, let us look at the command for linking and running our executable.

```
$ g++ -o duck *.o
$ ./duck
```

This takes all object files in the directory and links them together to make the executable `duck`. If no file were provided, it would name the executable `a.out`. Executables are run with `./<executable_name>`.

> **Why doesn't it work?:** If you run the first command now, with only the three `.o` files we manually created earlier, there will be an error about `undefined references`. This makes sense since the `.o` files for all of the dependencies needed to build the program haven't been generated yet.

### Getting Started with Makefile

A Makefile is a form of script, similar to a shell script, but with some interesting additional features. The most important difference is that  Makefiles track file dependencies and will create new object files only for those source files whose dependencies have been modified. As long as you list the dependency, the Makefile will track it. You can imagine that this makes the build process much faster.

Start by creating a Makefile in the current lab directory using your favorite editor (e.g. xemacs, vim, atom, etc.).

> In this course, we require you to name your file "Makefile". When you type `make` on the command line, it will first search for the file "Makefile" then "makefile". The `make` command will not recognize any other filename.

### Compile and Link Directly

> Makefiles can get very sophisticated and complex, but for these labs, we will create very basic ones. Once we get to the project, we will be using the tool "cmake" to make the Makefile.

The standard, basic structure of a makefile is to define variables at the top that set compilation and linking flags, define libraries, and store the filenames that will be used in the build process. This is followed by a collection of commands that specify a target (i.e. the file that should be made), the file dependencies, and the compilation or linking command.

These three elements must appear in the following format:

```
target: dependencies
[tab]command
```

For example, building a compiled object for the `MallardDuck` class would look like this:

```
mallard_duck.o: mallard_duck.h mallard_duck.cc
	g++ -c mallard_duck.cc
```

**__Note__** : Some editors replace tabs by spaces when you copy+paste the code from this readme. Ensure that the command is always preceded by a tab and not a series of spaces! For vim users who use spaces instead of tabs, pressing `Ctrl+V` before `Tab` will insert a tab when in insert mode instead of spaces.

Add the above example to your Makefile. Then run `make`.

```
$ make
```

The `make` command searches for the first target listed in the makefile and executes that command. In this case, it finds the `mallard_duck.o` target, which depends on the files `mallard_duck.h` and `mallard_duck.cc`. It will first look to see if `mallard_duck.o` exists and if not, will execute the command. If the file does exist, then it will check if any of the dependency files listed have changed since the last time it created `mallard_duck.o`. If there are no changes, then nothing will happen. If there were changes, it will execute the command and echo the command in your terminal.

Now, list the directory contents with `ls`. You should now see that `mallard_duck.o` exists on your system. This is the compiled version of your `MallardDuck` class. It is ready for linking.

Let's try that again to see what happens.

```
$ make
```

Nothing happened! It states that the file is up to date, Which is correct because nothing changed. Go ahead and add a space or change a comment in one of the files, run `make` again and see that it executes the compilation command again to create a new object file.

Let's add another target to our Makefile. Place this AFTER the `mallard_duck.o` target.

```
rubber_duck.o: duck.h rubber_duck.h rubber_duck.cc
	g++ -c rubber_duck.cc
```

This target will build the `RubberDuck` class. Notice that we've included a secondary dependency, `duck.h`. If that interface changes, we want to recompile `rubber_duck` to use the correct version of `duck.h` and to insure that everything is still compatible.

Let's run make again.

    $ make

**What just happened?** Make responded that `mallard_duck.o` is up to date. That's true, it is. We didn't make any changes to the dependencies of `mallard_duck.o`, so there was no need to recompile it. But, what about `rubber_duck.o`?

The default target for make is the first target listed in the Makefile, and it will only run one target at time. We can get around this by specifying which target to make, like this:

    $ make rubber_duck.o

That's better. Now, the `rubber_duck.o` object has been created. A little further along, we will show you how to use `.PHONY` targets to run all the commands.

### Building Projects

We could continue, adding each target/dependency/command into the Makefile one at a time for our ducks. But, that isn't very efficient, especially for large projects. We need a shortcut!

We can create a single command that uses wildcards to match to any target that we provide. Replace the two targets above with this single target.

```
%.o: %.cc
	g++ -c $^ -o $@
```

**What's happening here?** You can get a sense of what all those symbols are representing by comparing to the above commands.

- `%`  : The `%` symbol is the wildcard. It matches to any `<filename>.o` target that you want to make, and it uses that matching filename in the dependency list as well.

- `$^` : is a synonym for the slightly longer shortcut `$(inputs)`, which is just the list of all dependencies listed after the target.
    > e.g. all the `.cc` files listed as dependencies

- `$@` : is a shortcut meaning the name of the target without the .o extension.

Now, we can use this to build any number of object files. Give it a try.

```
$ make squeak_quack.o
$ make quack_quack.o
$ make mute_quack.o
```

Ultimately, we want to build an executable from all of the compiled objects. You can see that typing `make <target>` is not so great, but thankfully, we can create a single target that will build the executable and make any necessary object files. We can do this by listing object files as dependencies of our target executable.

Place this new target at the **_top_** of your Makefile, so that it is the default target to be built if `make` is called without arguments. Do not put any returns in the list of dependencies.

```
ducks: duck.o mallard_duck.o decoy_duck.o rubber_duck.o quack_behavior.o mute_quack.o quack_quack.o squeak_quack.o main.o
	g++ $^ -o $@
```

Now, let's run `make` to build our application.

    $ make

Note it builds any objects that weren't already built, ending with the creation of `ducks`. Now execute it:

    $ ./ducks

### Cleaning your Project Using PHONY Targets

Sometimes dependencies are not listed properly, and even though changes were made to a file, the make command does not generate a new object file or executable. And sometimes the directory is cluttered with `.o` files that you want to get rid of. You can clean up all these files with one simple make command that uses a _phony_ target. It is _phony_ because it is not a file that we want to create, rather it is a keyword that we use to get `make` to execute the corresponding command. 
> `clean` is probably the most often used _phony_ target and typically is used to remove all object files and the executable.

Let's add this to our Makefile now.

```
clean:
	rm *.o ducks

.PHONY: clean
```

**What's .PHONY?** Targets are nearly always tied to actual files on the system. Since there is no '`clean`' file, we make sure that make is aware that this is a command we wish to be able to invoke.

You can clean your directory, check that everything is gone, and rebuild.

```
$ make clean
$ ls
$ make
$ ls
```

### Try to Modify and Rebuild

Let's now see how `make` checks on dependencies and only builds what's necessary. Open `squeak_quack.cc` and add a third exclamation point (or remove one) in the _`Quack()`_ method.

    In squeak_quack.cc:  
        cout << "SQUEAK!!!" << endl;

Now, run `make` again to see what happens.

```
$ make
```

**What just happened?** Assuming all the compiled objects and executable already existed, `make` should recognize that `squeak_quack.cc` has changed. Based on this change, it should rebuild the `squeak_quack.cc` compiled object and then rebuild the executable (since it depends on `squeak_quack.o`).

### Macros

Macros in Makefiles are variables that are used in the target commands. It allows for the specifics of your application to be primarily at the top of the file, and the targets to remain mostly unchanged regardless of the project. For example, in making the executable above, you had to type out a long list of dependencies, but if instead you saved this list in a variable, you could use the same command for every project.

### __Before you start, please create a directory to store your header files called *headers*__
This will give you a good place to store your header files to make your project more organized.

#### __Place these variables at the TOP of your Makefile, above your targets.__

```
EXEFILE = ducks
CXXFLAGS = -c -Wall
SOURCES = duck.cc mallard_duck.cc decoy_duck.cc rubber_duck.cc quack_behavior.cc mute_quack.cc quack_quack.cc squeak_quack.cc main.cc
OBJECTS = $(SOURCES:.cc=.o)
INCLUDES = -Iheaders
```

And if you really do not want to type all those filenames and you know that every source file in your directory needs to be compiled, use this instead:

```
SOURCES = $(wildcard *.cc)
```

> **What are these?** We are giving a name to the executable to be created and defining the g++ compiler flags we will use in our compile (but not linking) commands.

We need to make a few changes in our Makefile to use these Macros. First, in the `ducks` target, replace the target name with our macro `EXEFILE`:
> Do the same with the dependency list `OBJECTS`
```
$(EXEFILE): $(OBJECTS)
	g++ $^ -o $@
```

In the `%.o` target, replace the '`-c`' flag in the current command with '`$(CXXFLAGS)`'. Notice the `-Wall` that was added. This means show all warnings, which you should always use and pay attention to. The compiler is usually trying to tell you something important that is likely to cause problems during execution!

Additionally, the '`-I`' flag will tell the compiler to look in the directories that are appended to it. In our case, it will look at the `headers` directory for our headers.

```
%.o: %.cc
	g++ $(CXXFLAGS) $(INCLUDES) $^ -o $@
```

And, finally, update our clean target:

```
clean:
	rm *.o $(EXEFILE)
```

Now, let's make sure our Macros are being used. Check the output to be sure that the new compiler flags are being utilized.

```
$ make clean
$ ls
$ make
$ ls
```

This will create an executable '`ducks`'. Finally, check if the application runs  without errors.

      $ ./ducks

Did the output match your expected results? If so, you are ready to push your changes to your remote repository for automated feedback.

### Pushing Results

Make sure no additional files are being pushed.

    $ git status

This should list all of the files that have changed and/or are untracked. You may notice that there are other files also listed as being ready to stage for commit that you do not want to push (e.g. `.o`, `ducks`, `duck`). **If you have not already created a second `.gitignore` file, you should follow the Lab01 directions and create another `.gitignore` to make sure we don't push those files.**

> For those wanting to play around with terminal commands, a quick way to get the same file you created before is to _copy_ it: `$ cp <path to lab01 folder> <path to lab03 folder>`. The general form of a _copy_ command is `$ cp <path to src> <path to dest>`.

### Add Changes to Repo both Locally and On the Server

You need to _stage_ all changes to the repository, which prepares those items to be permanently part of the repository. When you _commit_ those changes, they are saved to your local repository, which lives in your cselabs account (or your personal computer if that is what you are working on). When you _push_ those changes, they will be copied to the repo on the server. The difference between _commit_ and _push_ is what separates git from centralized version control systems.

    $ git status
    $ git add -A
    $ git commit -m "add(lab03_build): Adding lab03_build deliverables"
    $ git push

**_What just happened?_** Double-checking the files to be staged using the _git status_ command. All of the tracked changes are staged with `git add -A`. Those staged changes were committed to your local repository and tagged with the message that follows `-m`, then pushed to the server in your remote repository.

__A side note: Notice the format of the commit message. We will discuss this more, but it is important that you commit with meaningful messages that help you track changes, and importantly, communicate changes to the project team. When we get to the project, you will be graded on the quality of your commit messages.__

### Reading the Feedback

Pushing to the server triggers the automated grading system (if all is working!). Soon your repo will contain a feedback file, letting you know if you have passed a _majority_ of our tests for the assignment. In order for the feedback to be triggered, it must detect a change in the folder for the lab that you are working on (e.g., lab03_build_process for this lab). __Take note that from this lab onwards the Assessment will contain _more_ tests than the Feedback. Passing all of the Feedback tests will assure you _most but NOT ALL_ of the points for the Assessment.__

    $ git pull

Make sure you complete this pull once the report is posted so that you don't run into merge conflicts for your next lab.

THIS LAB IS COMPLETE.

Congratulations!
