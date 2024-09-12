# image-editor

# OpenCV Integration in Visual Studio Project

## Prerequisites

- Visual Studio installed
- CMake installed
- OpenCV library downloaded

## Steps to Integrate OpenCV

### 1. Download OpenCV

Download 4.10.0 version of OpenCV from the [official OpenCV website](https://opencv.org/releases/) and extract it to a location of your choice.

### 2. Configure OpenCV with CMake

1. Open CMake and set the source path to the directory where you extracted OpenCV.
2. Set the build path to a new directory where the build files will be stored.
3. Click on "Configure" and select your Visual Studio version.
4. Click on "Generate" to create the project files.

### 3. Add OpenCV to Visual Studio

1. Open your Visual Studio project.
2. Go to `Project > Properties`.
3. Under `VC++ Directories`, add the following paths:
   - **Include Directories**: Path to `opencv/build/include`
   - **Library Directories**: Path to `opencv/build/x64/vc15/lib` (or corresponding to your Visual Studio version)

### 4. Add OpenCV Libraries

1. Go to `Project > Properties > Linker > Input`.
2. Add the following libraries under `Additional Dependencies`:
   - `opencv_world<version>.lib` (e.g., `opencv_world455.lib`)

### 5. Copy OpenCV DLLs

Copy the corresponding DLL files from `opencv/build/x64/vc15/bin` to the directory where your executable is located.
