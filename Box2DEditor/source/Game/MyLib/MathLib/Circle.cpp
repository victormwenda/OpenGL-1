#include "Circle.h"

Circle::Circle(Point* origin, float radius)
{
	_origin.x = origin->x;
	_origin.y = origin->y;
	_radius = radius;
}

bool Circle::Contains( float x, float y )
{
	Point p(x, y);

	return Contains(&p);
}

bool Circle::Contains(Point* p)
{
	return (Point::Dist(p, &_origin) <= _radius);
}

bool Circle::IsColliding(Circle* circle)
{
	float d1 = Point::Dist(circle->GetOrigin(), &_origin);
	float d2 = circle->GetRadius() + _radius;

	return (d1 <= d2);
}


float Circle::GetRadius()
{
	return _radius;
}

Point* Circle::GetOrigin()
{
	return &_origin;
}

Circle::~Circle()
{
}