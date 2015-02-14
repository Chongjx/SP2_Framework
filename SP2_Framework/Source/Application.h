/******************************************************************************/
/*!
\file	Application.h
\author Chuk Yih Jou
\brief
Initialise window and opengl. Main run loop is here
*/
/******************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

/******************************************************************************/
/*!
		Class Application:
\brief	To store camera position, target and up
*/
/******************************************************************************/

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
    void ToggleFullScreen();

    double windowMidX;
    double windowMidY;
    double g_windowWidth;
    double g_windowHeight;

private:
	//Declare a window object
	StopWatch m_timer;
};

#endif