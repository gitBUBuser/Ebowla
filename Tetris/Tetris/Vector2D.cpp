#include "Vector2D.h"



Vector2D::Vector2D(const int& anX, const int& anY)
{
	myX = anX;
	myY = anY;
}

Vector2D::Vector2D()
{
	myX = 0;
	myY = 0;
}

const void Vector2D::SetX(const int& anX) {
	myX = anX;
}

const void Vector2D::SetY(const int& anY) {
	myY = anY;
}

Vector2D& Vector2D::operator=(const Vector2D& aVector) {
	myX = aVector.myX;
	myY = aVector.myY;
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& aVector) {
	myX = aVector.myX + myX;
	myY = aVector.myY + myY;
	return *this;
}

bool Vector2D::operator==(const Vector2D& aVector) const {
	if (myX == aVector.myX && myY == aVector.myY) {
		return true;
	}
	return false;
}