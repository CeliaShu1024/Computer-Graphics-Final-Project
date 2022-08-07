OP# Computer-Graphics-Final-Project
This is a course final project of computer graphics. I used Visual-Studio + GLUT to complete generating models.

## Output Results of This Project
![output result](https://github.com/LizLewis1024/Computer-Graphics-Final-Project/blob/main/result.png)

## Visual-Studio Configuration Example
### Step 1: Create Console App
Open `Visual Studio`, choose `Create a new project`>> `Console App`>> name it as "OpenGL Project" and set path to your desktop>> `Create`.

### Step 2: Paste Codes
Copy the contents in `final.cpp` of my `main` branch and paste them into the generated cpp file `OpenGL Project.cpp`.

### Step 3: Download Resources & Put Them in Your `.../Desktop/OpenGL Project/OpenGL Project`
The resources include 6 bmp files and `glut-tools` folder.

### Step 4: Create Project Debug Property Sheet
Back to `Visual Studio`, click `View`>> `Property Manager` in the top-menu-bar.

In left-side `Property Manager - OpenGL Project`, right click `Debug|x64` and choose `Add New Project Property Sheet` and name it as "glut-debug".

Double click `glut-debug` to open the property sheet.

Choose `VC++ Directories` and make the following changes:

In `Include Directories`, add folder `.../Desktop/OpenGL Project/OpenGL Project/glut-tools/glut/include`.

In `Library Directories`, add folder `.../Desktop/OpenGL Project/OpenGL Project/glut-tools/glut/debug/lib`.

Choose `Linker`>> `Input`, add `freeglut.lib` in `Additional Dependencies`.

### Step 5: Run the Project
After doing these settings, press `F5` to run and compile the OpenGL project.
