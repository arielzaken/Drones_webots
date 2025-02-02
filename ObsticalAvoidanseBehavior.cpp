#include "ObsticalAvoidanseBehavior.h"

ObsticalAvoidanseBehavior::ObsticalAvoidanseBehavior(DistanceSensor_I** distanceArray)
{
	for (int i = 0; i < 8; i++){
		distanseArray[i] = distanceArray[i];
	}
}

Velocity ObsticalAvoidanseBehavior::calcBehavior()
{
	Vector2f res = {0, 0};
	Vector2f front = { 0, 1 };
	Vector2f side = { 0.984807, 0.1736481 };

	res += distanseArray[0]->read() * front;
	res += distanseArray[1]->read() * side;
	res += distanseArray[2]->read() * front;
	res += distanseArray[3]->read() * front;
	res += distanseArray[4]->read() * front;
	res += distanseArray[5]->read() * front;
	res += distanseArray[6]->read() * front;
	res += distanseArray[7]->read() * front;

	return { 0,0,0,0 };
}

void ObsticalAvoidanseBehavior::setup()
{
}
