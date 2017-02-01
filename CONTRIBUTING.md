# Contributing

When contributing to this repository, please first discuss the change you wish to make via
[issue](https://github.com/hanselrd/bubble-warrior-adventures/issues) or
[Gitter](https://gitter.im/bubble-warrior-adventures/Lobby). 

Please note we have a code of conduct, please follow it in all your interactions with the project.

## Contents
- [Pull Requests](#pull-requests)
- [Coding Style](#coding-style)
    - [General](#general)
    - [File Naming](#file-naming)
    - [Includes](#includes)
    - [Comments](#comments)
    - [Classes](#classes)
    - [Functions](#functions)
    - [Variables](#variables)
- [Code of Conduct](#code-of-conduct)
    - [Our Pledge](#our-pledge)
    - [Our Standards](#our-standards)
    - [Our Responsibilities](#our-responsibilities)

## Pull Requests

1. You should **never** commit anything to *master* no matter how small.
    Instead fork or checkout your own branch and make the appropiate changes and
    submit a Pull Request. This is to preserve the *master* branch
    with *stable* and *peer-reviewed* code.
2. You **may not** merge in your *own* Pull Requests without the approval of another developer.
3. Pull Requests should have a descriptive title and a detailed body explaining
    the issue you set out to fix and how you decided on your changes.
4. If you reject a Pull Request, provide the contributor with a reason and
    offer constructive criticism.

## Coding Style

### General

Everything lives inside the **bwa** namespace

### File Naming

* All file names must be in **snake_case** with the exception of assets and dependencies.
* C++ header files must end in *.hpp*, **not** *.h*, the file extension *.h* should only
    be used when programming in *C*.
* C++ source files must end in *.cpp*
* Lua files must end in *.lua*, even if the Lua interpreter does not enforce this.

### Includes

Header files should be included in the following format in **alphabetical order**
```cpp
/*
    External libraries must be included first.
    Notice how they are in alphabetical order.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <sol.hpp>
#include <TGUI/TGUI.hpp>

...

/*
    C++ standard headers must come after any external
    library headers. Again notice the order.
*/
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

...

/*
    C standard headers must come after any C++
    standard headers. I recommend using the C++
    equivalent. For example ctime instead of time.h
*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

...


/*
    Lastly any header files local to the project must go last.
    Don't forget to include them in alphabetical order.
*/
#include "local_file.hpp"
#include "local_file2.hpp"
#include "local_other.hpp"
```

### Comments

Comments are highly encouraged when developing.
They allow another to developer pick up from where you left off. In the *Industry*,
they are a **must** so they are a **must** here as well. If you submit a
Pull Request with *poorly* documented code, chances are it will be rejected.
Commenting can be achieved in a number of ways. You do not necessarily have
to write comments, instead you should *strive* for descriptive names for your
functions and variables so they comment themselves for you. More on this will be
discussed below.

### Classes
### Functions
### Variables

## Code of Conduct

### Our Pledge

In the interest of fostering an open and welcoming environment, we as
contributors and maintainers pledge to making participation in our project and
our community a harassment-free experience for everyone, regardless of age, body
size, disability, ethnicity, gender identity and expression, level of experience,
nationality, personal appearance, race, religion, or sexual identity and
orientation.

### Our Standards

Examples of behavior that contributes to creating a positive environment
include:

* Using welcoming and inclusive language
* Being respectful of differing viewpoints and experiences
* Gracefully accepting constructive criticism
* Focusing on what is best for the community
* Showing empathy towards other community members

Examples of unacceptable behavior by participants include:

* The use of sexualized language or imagery and unwelcome sexual attention or
advances
* Trolling, insulting/derogatory comments, and personal or political attacks
* Public or private harassment
* Publishing others' private information, such as a physical or electronic
  address, without explicit permission
* Other conduct which could reasonably be considered inappropriate in a
  professional setting

### Our Responsibilities

Project maintainers are responsible for clarifying the standards of acceptable
behavior and are expected to take appropriate and fair corrective action in
response to any instances of unacceptable behavior.

Project maintainers have the right and responsibility to remove, edit, or
reject comments, commits, code, wiki edits, issues, and other contributions
that are not aligned to this Code of Conduct, or to ban temporarily or
permanently any contributor for other behaviors that they deem inappropriate,
threatening, offensive, or harmful.
