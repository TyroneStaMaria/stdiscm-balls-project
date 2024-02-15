# Balls is life

STDISCM Problem Set # 1

Authors: Faith Griffin and Tyrone Sta. Maria

This project is a particle simulator that utilizes concurrent programming alongside C++ and OpenGL.

## Prerequisites

Before you begin, ensure you have the following installed on your system:

- OpenGL: A cross-language, cross-platform application programming interface (API) for rendering 2D and 3D vector graphics. Typically included with your operating system or can be updated via your graphics card driver.
- FreeGLUT: The OpenGL Utility Toolkit, a free-software/open-source alternative to the OpenGL Utility Toolkit (GLUT) library. FreeGLUT allows the creation of interactive programs that use OpenGL.
- Visual Studio: An integrated development environment (IDE) from Microsoft. This project was developed using Visual Studio 2019, but it should be compatible with newer versions. Ensure you have the C++ development tools and the latest Windows SDK installed. Download Visual Studio from [the official Microsoft website](https://visualstudio.microsoft.com/).

## Step 1: Clone the Repository

```
git clone https://github.com/TyroneStaMaria/stdiscm-balls-project.git
```

or download as a ZIP file and extract it

## Step 2: Open the Project

Using Visual Studio

1. Navigate to the `Balls/` directory.
2. Double-click on `Balls.sln` to open the project in Visual Studio.

If you prefer not to use the solution file:

1. Open Visual Studio.
2. Select `File > Open > Project/Solution` and navigate to the `Balls/` directory.
3. Choose `Balls.sln` to load the project.

## Step 3: Build and Run

To build and run the project:

1. In Visual Studio, set the build configuration to "Release" or "Debug" depending on your needs.
2. Press `Ctrl + F5` to build and run the project without debugging.

Alternatively, you can use `F5` to run with debugging enabled if you need to troubleshoot or develop the project further.

## How to Use the program

Here is a demonstration of how to use the particle simulator.

https://drive.google.com/file/d/1Z4VnUZCtM8h1md4B7-Ggk-xIhArg5P0S/view?usp=drive_link

## Setup and Installation

1. Download freeglut 3.0.0 MSVC Package from [Transmission Zero](https://www.transmissionzero.co.uk/software/freeglut-devel/).

2. Follow the steps indicated in the Readme.txt from freeglut.

3. For the step on configuring the "lib\" folder in freeglut's Readme.txt, do "lib\x64\" instead to prevent errors.

4. Add the following under Linker -> input `opengl32.lib;glu32.lib;freeglut.lib;` in the project properties.

5. You do not need to follow the steps after `However, it shouldn’t be necessary to explicitly state these dependencies...`.

6. Go to the bin folder in the freeglut msvc package and go to the x64 folder and copy freeglut.dll.

7. Paste the freeglut.dll under C:\Windows\System32.

8. Build and Run the project in Visual Studio `Ctrl + F5`.
