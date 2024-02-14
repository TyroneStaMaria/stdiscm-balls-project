# Balls is life

STDISCM Problem Set # 1

Authors: Faith Griffin and Tyrone Sta. Maria

## Prerequisites

- TODO: ayusin to
- opengl
- freeglut

## Step 1: Clone the Repository

`git clone https://github.com/TyroneStaMaria/stdiscm-balls-project.git`

or download as zip

## Step 2: Open the Project

1. Navigate to the `Balls/` directory
2. Open `Balls.sln`

OR

1. Open with visual studio TODO: add more steps here

## Step 3: Build and Run

1. Ctrl + F5 TODO: add steps to build

## How to use the program

TODO: link to the demo video

## Setup and Installation

1. Download freeglut 3.0.0 MSVC Package https://www.transmissionzero.co.uk/software/freeglut-devel/

2. Follow the steps indicated in the Readme.txt from freeglut

3. For the step on configuring the "lib\" folder in freeglut's Readme.txt, do "lib\x64\" instead to prevent errors.

4. Add the following under Linker -> input `opengl32.lib;glu32.lib;freeglut.lib;` in the project properties

5. You do not need to follow the steps after `However, it shouldn’t be necessary to explicitly state these dependencies...`

6. Go to the bin folder in the freeglut msvc package and go to the x64 folder and copy freeglut.dll

7. Paste the freeglut.dll under C:\Windows\System32

8. Build and Run the project in Visual Studio `Ctrl + F5`
