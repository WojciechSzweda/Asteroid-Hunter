#pragma once
//#include "Lib.h"
#include "GameObject.h"
class ShipWreck : public GameObject 
{
private:
	float Angle;
	float rotationSpeed;
public:
	ShipWreck();
	ShipWreck(Vector2 position, float r);
	~ShipWreck();

	void Render();
	void Update();
};

