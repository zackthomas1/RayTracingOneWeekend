#pragma once
#include <iostream>

class Utility
{
private:
	 
public:
	Utility()
	{
	}

	~Utility()
	{
	}

	static bool DoubleEquality(double v01, double v02)
	{
		const double EPSILON = 0.0001;
		if (abs(v01 - v02) < EPSILON)
			return true;
		else
			return false;
	}
};
