# Universe1

Universe1 is an experimental **C++ / Qt** project focused on **3D simulations and visual experiments**
inspired by simplified physical and mathematical ideas.

The project does **not** aim to be a scientifically accurate model of the universe.
Instead, it serves as a sandbox for exploring motion, interaction, visualization,
and alternative ways of thinking about complex systems.

---

## Platform Support

This project is currently **developed and tested only on Ubuntu Linux**.

Other operating systems may work, but they are **not officially supported**
and have not been tested yet.

---

## Features

- 3D simulations implemented in C++
- Qt-based application architecture
- Optional GPU acceleration using CUDA
- External audio and text-to-speech processing via system tools
- Experimental and exploratory design

---

## Technology Stack

- **C++17**
- **Qt framework**
- **STL**
- **GoogleTest** (unit testing)
- **CUDA** (optional, for GPU acceleration)

---

## External Tools

Some functionality relies on external tools executed as separate processes
using Qt's `QProcess` class:

- ffmpeg
- sox
- wget
- eSpeak / pico2wave
- (optional) LaTeX, dvipng

These tools are **not bundled** with the project and must be installed separately.

---

## System Dependencies

The following packages are required or recommended to build and use this project
on Ubuntu.

They can be installed using:

```bash
sudo apt install \
  ffmpeg \
  sox \
  espeak \
  libttspico-utils \
  clang \
  clang-format \
  clang-tools \
  doxygen \
  doxygen-latex \
  graphviz \
  ghostscript \
  texlive-full \
  texlive-latex-extra \
  texlive-latex-base \
  build-essential \
  wget \
  libglu1-mesa-dev \
  freeglut3-dev \
  mesa-common-dev \
  nvidia-open \
  cuda-drivers \
  cuda-toolkit-13-1
