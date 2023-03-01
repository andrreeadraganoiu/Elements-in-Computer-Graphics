#include "lab_m1/tema1/duck.h"
#include <iostream>
#include "lab_m1/tema1/constants.h"
using namespace std;

	Duck::Duck()
	{
		alive = true;
		escaped = false;
	}

	float Duck::calculateArea(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3)
	{
		return 0.5 * abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
	}


	bool Duck::isKilled(float x, float y)
	{
		float area = 0;
		area = area + calculateArea(glm::vec3(x, y, 0), p1, p2) + calculateArea(glm::vec3(x, y, 0), p2, p3) 
			        + calculateArea(glm::vec3(x, y, 0), p3, p4) + calculateArea(glm::vec3(x, y, 0), p1, p4);

		if (fabs(area - (BODY_LENGTH + 2 * HEAD_RADIUS) * BODY_WIDTH) < 0.01)
		{
			return true;
		}
		return false;
	}

