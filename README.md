# Bubble Warrior Adventures!

[![Gitter](https://badges.gitter.im/bubble-warrior-adventures/Lobby.svg)](https://gitter.im/bubble-warrior-adventures/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## Contents

- [Introduction](#introduction)
- [Motivation](#motivation)
- [Development Environment](#development-environment)
- [Contributors](#contributors)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project was created for our Software Engineering course. We were tasked with
creating a `PowerPoint` presentation detailing what our project was about,
how the work would be split up and a guideline to follow. With the freedom given
to us to choose our programming language and project we settled on using C++ with a
bit of [Python](https://www.python.org) for simple scripting and a
role-playing game. We are using [SFML](http://www.sfml-dev.org/index.php)
to handle window events, graphics and audio, and [TGUI](https://tgui.eu) to
create and render in-game GUI components. We are currently working on the story
to go with the game.

## Motivation

Hmm, we didn't know you needed any motivation to create a game, but here goes!
Video games have always been a passion of ours. They're natural stress relievers
and who doesn't love a good storyline?

## Development Environment

We are using [CMake](https://cmake.org) as our build system, which means, you can use
any environment of your choosing as long as you resolve the dependencies.
The only dependencies you need to find yourself are [SFML](http://www.sfml-dev.org/index.php)
and [TGUI](https://tgui.eu). We also require a local installation of [Python](https://www.python.org) 3.0+
to run our game scripts.

## Contributors

- [Hansel De La Cruz](https://github.com/hanselrd)
- [Kyle Jolicoeur](https://github.com/kjolicoeur)
- [Jennifer Green](https://github.com/goldenapplepie)

## Installation

We assume you know how to build projects using [CMake](https://cmake.org). If not, please take the time now to read
up on how it works.

The following depedencies must be either downloaded/installed using your favorite package manager/browser or compiled
from source.

- [SFML](http://www.sfml-dev.org/index.php)
- [TGUI](https://tgui.eu) (needs to be compiled with the same version of [SFML](http://www.sfml-dev.org/index.php) that is going to used to build the game)
- [Python](https://www.python.org) (development)
- [Boost](https://boost.org/) (headers only)

Once those are resolved open up your favorite terminal and clone the repository

```sh
$ git clone https://github.com/hanselrd/bubble-warrior-adventures.git --recursive
```

We make use of some open-source libraries which are included as submodules so the `--recursive` fetches them all at once.
To build the game on Linux/Mac do the following:

```sh
$ cd bubble-warrior-adventures
$ mkdir build
$ cd build
$ cmake ..
$ make
```

On Windows you can use the [CMake](https://cmake.org) GUI which saves you the trouble of messing with the command line.

## Contributing

Want to help us out? Refer to the
[contribution](CONTRIBUTING.md)
guide.

## License

MIT License

Copyright (c) 2017

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
