#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "Controller_input_Header.h"
using namespace std;

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

int main(void)
{
    GLFWwindow* window;

    //library
    if (!glfwInit())
    {
        return -1;
    }
    
    // Create a windowed mode window and its OpenGL context
    
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Controller Input", NULL, NULL);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    
    // Loop until  closes the window
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
     
        int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
        cout << "Controller status :"<<present <<endl;

        if (1 == present)
        {
            int axesCount;
            const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            int buttonCount;
            const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
            
            LeftXAxis(axes);
            LeftYAxis(axes);
            LeftYAxis(axes);
            RightXAxis(axes);
            RightYAxis(axes);
            LeftTrigger(axes);
            RightTrigger(axes);
            ButtonA(buttons);
            ButtonB();
            ButtonX();
            ButtonY();
            ButtonLB();
            ButtonRB();
            ButtonB7();
            ButtonB8();
            ButtonLA();
            ButtonRA();
            ButtonUp();
            ButtonRight();
            ButtonDown();
            ButtonLeft();
            

            const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
            cout << name << endl;
        }



        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
    
    }
    
    glfwTerminate();

    return 0;
}