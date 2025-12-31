# Third-Party Licenses and Dependencies

This project uses the following third-party libraries and external tools.

---

## Linked Libraries

### Qt

This software is built using the Qt framework.

- License: GNU Lesser General Public License (LGPL), version 3
- Linking: Dynamic
- Modifications: None

Qt website: https://www.qt.io
Qt licensing information: https://www.qt.io/licensing

---

### GoogleTest (GTest)

This project uses GoogleTest for unit testing.

- License: BSD 3-Clause License
- Website: https://github.com/google/googletest

GoogleTest is linked as a library and is license-compatible with the MIT License.

---

### NVIDIA CUDA / CUDA Runtime

This project may use NVIDIA CUDA libraries for GPU acceleration.

- License: NVIDIA CUDA End User License Agreement (EULA)
- Libraries: `cuda`, `cudart`
- Website: https://developer.nvidia.com/cuda

CUDA is a proprietary library distributed by NVIDIA.
Its license does not impose copyleft requirements on this project.

---

## External Tools Executed as Separate Processes

The following tools are **not linked** to this software and are **not part of the distributed code**.
They are executed as **external programs** using Qt's `QProcess` class (`start()`, `waitForFinished()`).

Because these tools run as independent processes, their licenses do **not** apply to this project's source code.

### FFmpeg
- License: LGPL / GPL (depending on build configuration)
- Website: https://ffmpeg.org

### SoX (Sound eXchange)
- License: GPL
- Website: http://sox.sourceforge.net

### wget
- License: GPL
- Website: https://www.gnu.org/software/wget/

### eSpeak / eSpeak NG
- License: GPL
- Website: https://github.com/espeak-ng/espeak-ng

### pico2wave
- License: Apache License 2.0
- Website: https://launchpad.net/pico2wave

---

## Planned External Tools

The following tools may be used in the future as external processes:

### LaTeX
- License: LaTeX Project Public License (LPPL)
- Website: https://www.latex-project.org

### dvipng
- License: GPL
- Website: https://savannah.nongnu.org/projects/dvipng/

---

## Important Notes

- This project does **not** include, embed, modify, or redistribute the source code
  of any external tools listed above.
- External tools must be installed separately by the user.
- The licenses of external tools do **not** apply to this project's source code.

