#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

using namespace std;



void LeftXAxis(const float* axes) {
    
    cout << "Left Stick X Axis: " << axes[0] << endl; // range -1-1
}

void LeftYAxis(const float* axes) {
    
    cout << "Left Stick Y Axis: " << axes[1] << endl; // range -1-1
}

void RightXAxis(const float* axes) {
    
    cout << "Right Stick X Axis: " << axes[2] << endl; // range -1-1
}

void RightYAxis(const float* axes) {
    
    cout << "Right Stick Y Axis: " << axes[3] << endl; // range -1-1
}

void LeftTrigger(const float* axes) {
    
    cout << "Left Trigger: " << axes[4] + 1 << endl; // range 0-2
}

void RightTrigger(const float* axes) {
    
    cout << "Right Trigger: " << axes[5] + 1 << endl; // range 0-2
}

void ButtonA(const unsigned char* buttons) {
    
    if (GLFW_PRESS == buttons[0])
    {
        cout << "A Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[0])
    {
        cout << "A Released" << endl;
    }
}


void ButtonB() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[1])
    {
        cout << "B Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[1])
    {
        cout << "B Released" << endl;
    }
}

void ButtonX() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[2])
    {
        cout << "X Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[2])
    {
        cout << "X Released" << endl;
    }
}

void ButtonY() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[3])
    {
        cout << "Y Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[3])
    {
        cout << "Y Released" << endl;
    }
}

void ButtonLB() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[4])
    {
        cout << "LB Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[4])
    {
        cout << "LB Released" << endl;
    }
}

void ButtonRB() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[5])
    {
        cout << "RB Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[5])
    {
        cout << "RB Released" << endl;
    }
}

void ButtonB7() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[6])
    {
        cout << "B7 Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[6])
    {
        cout << "B7 Released" << endl;
    }
}

void ButtonB8() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[7])
    {
        cout << "B8 Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[7])
    {
        cout << "B8 Released" << endl;
    }
}

void ButtonLA() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[8])
    {
        cout << "Left Axis Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[8])
    {
        cout << "Left Axis Released" << endl;
    }
}

void ButtonRA() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[9])
    {
        cout << "Right Axis Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[9])
    {
        cout << "Right Axis Released" << endl;
    }
}

void ButtonUp() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[10])
    {
        cout << "Up Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[10])
    {
        cout << "Up Released" << endl;
    }
}

void ButtonRight() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[11])
    {
        cout << "Right Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[11])
    {
        cout << "Right Released" << endl;
    }
}

void ButtonDown() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[12])
    {
        cout << "Down Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[12])
    {
        cout << "Down Released" << endl;
    }
}

void ButtonLeft() {
    int buttonCount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
    if (GLFW_PRESS == buttons[13])
    {
        cout << "Left Pressed" << endl;
    }
    else if (GLFW_RELEASE == buttons[13])
    {
        cout << "Left Released" << endl;
    }
}