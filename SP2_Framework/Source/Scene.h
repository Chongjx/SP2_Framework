/******************************************************************************/
/*!
\file	Scene.h
\author Chuk Yih Jou
\brief
Base scene class
*/
/******************************************************************************/
#ifndef SCENE_H
#define SCENE_H

/******************************************************************************/
/*!
		Class Scene:
\brief	Polymorphism 
*/
/******************************************************************************/
class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif