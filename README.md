# MasterEars

[![Build Status](https://travis-ci.com/jatinchowdhury18/MasterEars.svg?token=Ub9niJrqG1Br1qaaxp7E&branch=master)](https://travis-ci.com/jatinchowdhury18/MasterEars)

MasterEars is a listening test application for desktop (maybe someday for mobile) designed
for mixing and mastering engineers to help train their ears.

## Installing
TODO

## Using
To use MasterEars simply load a song (currently only supports .wav files),
configure your test, and press "Start".

## Modes
Currently MasterEars only supports one mode: "EQTest".
If you have an idea for a new test to add, please create
a [GitHub issue](https://github.com/jatinchowdhury18/MasterEars/issues)
with your idea!

### EQTest Mode
The EQ test mode applies an EQ to your audio file, boosting or cutting
a single frequency band by a certain dB amount. Your task is to guess
which band is being altered. You can configure the test to use either
boosting or cutting, as well as to use 3 dB, 6 dB, or 9 dB amounts.

## Building
MasterEars was developed using the [JUCE](https://github.com/WeAreROLI/JUCE)
framework, aided by the [FRUT](https://github.com/McMartin/FRUT) tool,
which allows JUCE projects to be built using `cmake`.

To build MasterEars from scratch, download and install both JUCE and FRUT.
Next, edit `CMakeLists.txt` to configure the correct path to your installation
of FRUT. Finally, you can build MasterEars with `cmake` as follows:

```bash
$ cd MasterEars/
$ mkdir build/ && cd build/
$ cmake .. -G <cmake generator>
$ cmake --build .
```

## Background
I created this app since I used to do a similar test when I was learning
to master, as well as when I was working as a mastering engineer at NoLava
Studios in Los Angeles. Now that I have some programming skills, I figured
it could be cool to automate the process with my own little desktop app.
Enjoy!
