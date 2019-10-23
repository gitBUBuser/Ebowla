#include "MathFunctions.h"



MathFunctions::MathFunctions()
{
}


MathFunctions::~MathFunctions()
{
}

bool MathFunctions::Timer(float& someMaxTime, float& someCurrentTime, float &someDeltaTime) {
	someCurrentTime += someDeltaTime;
	if (someCurrentTime > someMaxTime) {
		someCurrentTime = 0;
		return true;
	}
	return false;
}
