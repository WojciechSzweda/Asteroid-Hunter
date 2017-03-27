#pragma once

class IMovable
{
public:
	virtual ~IMovable() {}
	
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Move() = 0;
	virtual void OffScreenControl() = 0;
private:

};

