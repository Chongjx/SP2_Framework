/******************************************************************************/
/*!
\file	main.cpp
\author Chuk Yih Jou
\brief
Main program run loop
*/
/******************************************************************************/

#include "Application.h"

int main( void )
{
	Application app;
	app.Init();
	app.Run();
	app.Exit();
}