## Setup and Installation

1. Download freeglut 3.0.0 MSVC Package https://www.transmissionzero.co.uk/software/freeglut-devel/

2. Follow the steps indicated in the Readme.txt from freeglut

3. For the step on configuring the "lib\" folder in freeglut's Readme.txt, do "lib\x64\" instead to prevent errors.

4. Add the following under Linker -> input `opengl32.lib;glu32.lib;freeglut.lib;` in the project properties

5. You do not need to follow the steps after `However, it shouldn’t be necessary to explicitly state these dependencies...`

6. Go to the bin folder in the freeglut msvc package and go to the x64 folder and copy freeglut.dll

7. Paste the freeglut.dll under C:\Windows\System32

8. Build and Run the project in Visual Studio `Ctrl + F5`
