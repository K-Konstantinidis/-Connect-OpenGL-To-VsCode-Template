# Connect-OpenGL-To-VsCode-Template

This is a template to connect OpenGL to your Visual Studio Code, linking to GLFW & GLAD.

This is a forked repo from: https://github.com/vkphillia/opengl-cpp-template

## Requirements

- Must have `GCC C++ compiler` (preferably download it with the help of MinGW)
- Must have `C/C++ extension` for VS Code

For more help check: https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites

Also to be **_100%_** sure you should probably:
- Download and install the GLFW <a href="https://www.glfw.org/download.html">X-bit binaries</a> depending on your OS & system
- Extract the files, **copy** the `libglfw3.a` file and **paste** it in the `lib` folder of your MingW (Path will be something like this: `C:\MinGW\lib`)

## How to run

- Clone this repo `git clone https://github.com/K-Konstantinidis/Connect-OpenGL-To-VsCode-Template.git`
- Open it as a folder in Visual Studio Code
- In Visual Studio Code menu select Run -> Run Without Debugging (`Ctrl + F5`)

## More Help 
- Using Git with Visual Studio Code: https://www.youtube.com/watch?v=i_23KUAEtUM
- Remember to change each PATH to yours:
https://github.com/K-Konstantinidis/Connect-OpenGL-To-VsCode-Template/blob/0e62a51704ad774e59f74ce038f04b6da8091d62/.vscode/c_cpp_properties.json#L14
https://github.com/K-Konstantinidis/Connect-OpenGL-To-VsCode-Template/blob/0e62a51704ad774e59f74ce038f04b6da8091d62/.vscode/launch.json#L19
https://github.com/K-Konstantinidis/Connect-OpenGL-To-VsCode-Template/blob/0e62a51704ad774e59f74ce038f04b6da8091d62/.vscode/tasks.json#L11

## Main.cpp
Create a simple window and draw a triangle.
