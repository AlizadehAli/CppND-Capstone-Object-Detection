# CPPND: Capstone

This is a repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

I have implemented an ObjectDetection service using YOLO_V3 and OpenCV. It accepts an image/video as input and outputs a image/video with detections.

The project satisfies the following rubric points:
1. The submission must compile and run.
2. The project demonstrates an understanding of C++ functions and control structures.
3. The project reads data from a file and process the data, or the program writes data to a file.
4. The project accepts user input and processes the input.
5. The project uses Object Oriented Programming techniques.
6. Classes use appropriate access specifiers for class members.
7. Class constructors utilize member initialization lists.
8. Classes abstract implementation details from their interfaces.
9. Classes encapsulate behavior.
10. Classes follow an appropriate inheritance hierarchy.
11. Derived class functions override virtual base class functions.
12. Templates generalize functions in the project.
13. The project makes use of references in function declarations.
14. The project uses destructors appropriately.
15. The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
16. The project uses move semantics to move data, instead of copying it, where possible.
17. The project uses smart pointers instead of raw pointers.
18. The project uses multithreading.
19. A promise and future is used in the project.
20. A mutex or lock is used in the project.
21. A condition variable is used in the project.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac)
  * Linux: make is installed by default on most Linux distros
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)

## Basic Build Instructions

1. Clone this repo.
2. Compile: `cmake . && make`
3. Run it: `./ObjectDetector --image=<your_image.jpg> OR ./ObjectDetector --video=<your_video.mp4>`.

