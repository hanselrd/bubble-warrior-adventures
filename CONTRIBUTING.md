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
    - [Namespaces](#namespaces)
    - [Classes](#classes)
        - [Methods](#methods)
        - [Members](#members)
        - [Complete Example](#complete-example)
    - [Functions](#functions)
    - [Variables and Parameters](#variables-and-parameters)
- [Code of Conduct](#code-of-conduct)
    - [Our Pledge](#our-pledge)
    - [Our Standards](#our-standards)
    - [Our Responsibilities](#our-responsibilities)

## Pull Requests

1. You **may not** merge in your own Pull Requests without the approval of another developer.
2. Pull Requests should have a descriptive title and a detailed body explaining
    the issue you set out to fix and how you decided on your changes.
3. If you reject a Pull Request, provide the contributor with a reason and
    offer constructive criticism.

## Coding Style

### General

* Curly braces should start on the same line of a declaration
    and end on their own line.

    ```cpp
    void foo() { // curly brace starts on same line
        ...
    } // curly brace ends on its own line.

    class FooBar {
        ...
    };

    if (fooBar) {
        ...
    }
    ```

### File Naming

* C++ header files must end in `.hpp`, **not** `.h`, the file extension `.h` should only
    be used when programming in C.
* C++ source files must end in `.cpp`.

### Includes

Header files should be included using the following format in **alphabetical order**.
Please note a line space was used between each section for readability, however,
in your code, the includes should be listed without any line spaces or comments.

```cpp
/*
    Relative header of the file should be included first.
    The include below is allowed only if we are inside 'Game.cpp'
    which is Game's implementation. Hence the use of the word
    'relative'.
*/
#include "Game.hpp"

/*
    External libraries must be included next.
    Notice how they are in alphabetical order.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <sol.hpp>
#include <TGUI/TGUI.hpp>

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

/*
    C standard headers must come after any C++
    standard headers. I recommend using the C++
    equivalent. For example ctime instead of time.h
*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
They allow other developers to pick up from where you left off.
Documentation can be achieved in a number of different ways.
You do not necessarily have to write comments, instead you should strive for
descriptive names when creating functions or variables.

```cpp
// For single-line comments, use '//' and a space before starting your comment.

/*
    Multi-line comments should have '/*' and '*\/' on their own lines
    and use one tab space before starting your comments.
    Multi-line comments are preferred, but single-line comments can be used
    for small comments within functions.
*/
```

More information on commenting is provided in specific sections below.

### Namespaces

You should **never** include a namespace for global use.
Please note the following snippet of code shows what you should **not** do.

```cpp
#include <map>
#include <string>

/*
    This is what we refer to as 'including a namespace'
    and should never be done.
*/
using namespace std;

/*
    This code offers nothing in terms of where 'map' and
    'string' come from. What if we create our own 'map' and 'string'
    classes? How would we differentiate them? For this reason,
    this is not allowed and any Pull Requests containing code like this
    will be rejected.
*/
map<string, unsigned> map_;
```

You should write out namespaces each and every time. They are usually small
('std::' is only *five* characters) and serve as documentation, letting everyone
know where things come from. The following snippet shows what you **should** do.

```cpp
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

/*
    You might find writing the 'sf::' and 'std::' prefixes tedious,
    but they document for you where that specific code comes from.
    By taking a quick glance you already know 'RenderWindow' is a SFML class,
    'map' is a STL container and 'string' is the STL container for chars.
*/
sf::RenderWindow window;
sf::View view;
std::map<std::string, unsigned> map;
```

### Classes

Classes should be named using **[PascalCase](https://en.wikipedia.org/wiki/PascalCase)**.

```cpp
class SuperAwesomeClass {
    ...
};
```

#### Methods

Class methods should be named using **lower [camelCase](https://en.wikipedia.org/wiki/Camel_case)**.
They should also be named after a specific action. Some acceptable names would be:
`run`, `update`, `loadMap` and etc.

```cpp
class SuperAwesomeClass {
public:
    void doFoo();
    void doBar();
};
```

#### Members

Class members should be named using lower **[camelCase](https://en.wikipedia.org/wiki/Camel_case)**,
except for constants, and prefixed by an `_` (underscore).
Members should always go below methods.

```cpp
class SuperAwesomeClass {
protected:
    static const int _SOME_STATIC_CONST_INT;
    const int _SOME_CONST_INT;
    static int _someStaticInt;
    int _someInt;
};
```

#### Complete Example

```cpp
// SuperAwesomeClass.hpp

class SuperAwesomeClass {
public:
    /*
        Class methods go before any class members.
    */
    void doFoo();
    void doBar();

protected:
    /*
        Take note on the spacing between
        the doBar method and the protected keyword.
    */
    static const int _SOME_STATIC_CONST_INT;
    const int _SOME_CONST_INT;
    static int _some_static_int;
    int _some_int;
};
```

```cpp
// SuperAwesomeClass.cpp

#include "SuperAwesomeClass.hpp"

void SuperAwesomeClass::doFoo() {
    ...
}

void SuperAwesomeClass::doBar() {
    ...
}
```

### Functions

Functions do not belong to any class and are usually referred to as helpers.
They should be named using **[snake_case](https://en.wikipedia.org/wiki/Snake_case)**
and follow the same outline for a class method: descriptive and named after an action

```cpp
void load_data() {
    ...
}
```

### Variables and Parameters

Variable names should be named using lower **[camel Case](https://en.wikipedia.org/wiki/Camel_case)**.
They should be descriptive and self-document their purpose. This also applies to
function and class method parameters.

```cpp
/*
    The purpose of this function is to outline
    how variables and parameters should be named.
    Yes, I know this function is useless.
*/
int compute_result(int num_points) {
    int result = 0;
    return result + num_points;
}
```

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
