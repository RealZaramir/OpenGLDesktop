#include "myVec3d.h"



myVec3d::myVec3d()
{
	x = 0;
	y = 0;
	z = 0;
}

myVec3d::myVec3d(float compX, float compY, float compZ)
{
	x = compX;
	y = compY;
	z = compZ;
}


float myVec3d::dist(myVec3d v)
{

	return sqrt(pow(this->x - v.x, 2) + pow(this->y - v.y, 2) + pow(this->z - v.z, 2));
}

float myVec3d::dist_sq(myVec3d v)
{
	return pow(this->x - v.x, 2) + pow(this->y - v.y, 2) + pow(this->z - v.z, 2);
}

float myVec3d::distLine(myVec3d a, myVec3d b)
{
	myVec3d v = b - a;
	myVec3d w = *this - a;
	float t = v.dot(w) / (v.dot(v));

	return this->dist((a + v * t));
}

float myVec3d::dot(myVec3d v)
{
	return x * v.x + y * v.y + z * v.z;
}

float myVec3d::getMag()
{
	return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

float & myVec3d::getComp(int index)
{
	switch (index) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}
}

bool myVec3d::inBox(myVec3d min, myVec3d max)
{
	if (this->x > min.x && this->x < max.x &&
		this->y > min.y && this->y < max.y &&
		this->z > min.z && this->z < max.z)return true;
	else return false;
}

bool myVec3d::inBox(myVec3d max)
{
	if (this->x > 0 && this->x < max.x &&
		this->y > 0 && this->y < max.y &&
		this->z > 0 && this->z < max.z)return true;
	else return false;
}

bool myVec3d::inSphere(myVec3d center, float radius)
{
	if (this->dist(center) < radius)return true;
	else return false;
}

bool myVec3d::nearLine(myVec3d a, myVec3d b, float dist)
{
	return this->distLine(a, b) < dist; 
}

myVec3d myVec3d::operator+(myVec3d v)
{
	return myVec3d(this->x + v.x, this->y + v.y, this->z + v.z);
}

myVec3d myVec3d::operator-(myVec3d v)
{
	return myVec3d(this->x - v.x, this->y - v.y, this->z - v.z);
}

myVec3d myVec3d::operator*(float f)
{
	return myVec3d((this->x * f), (this->y * f), (this->z * f));
}


myVec3d myVec3d::operator/(float f)
{
	return myVec3d((this->x / f), (this->y / f), (this->z / f));
}

myVec3d myVec3d::cross(myVec3d v)
{
	return myVec3d((y * v.z - z * v.y), (z * v.x - x * v.z), (x * v.y - y * v.x) );
}

void myVec3d::abs()
{
	x = std::fabs(x);
	y = std::fabs(y);
	z = std::fabs(z);
}

void myVec3d::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
}

void myVec3d::operator+=(myVec3d v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void myVec3d::operator-=(myVec3d v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void myVec3d::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
}

void myVec3d::operator=(myVec3d v)
{
	setComp(v.x, v.y, v.z);
}

bool myVec3d::operator==(myVec3d v)
{
	if (v.x == this->x &&
		v.y == this->y &&
		v.z == this->z)return true;
	else return false;
}

void myVec3d::setComp(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

void myVec3d::set(myVec3d v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void myVec3d::setRandom(float l, float h)
{
	x = l + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (h - l)));
	y = l + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (h - l)));
	z = l + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (h - l)));

}

void myVec3d::setRandom(float h)
{
	x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / h));
	y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / h));
	z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / h));
}

void myVec3d::setRandomByMag(float mag)
{

	float phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2*PI) ));
	float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2* PI) ));

	x = mag * sin(theta) * cos(phi);
	y = mag * sin(theta) * cos(phi);
	z = mag * cos(theta);
	
}

void myVec3d::setRandom(myVec3d v)
{
	x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / v.x));
	y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / v.y));
	z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / v.z));
}

void myVec3d::setRandom(myVec3d min, myVec3d max)
{
	x = min.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.x - min.x)));
	y = min.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.y - min.y)));
	z = min.z + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max.z - min.z)));
}



std::bitset<30> myVec3d::hash(myVec3d space)
{
	std::bitset<30> hash;
	hash.reset();
	int h_size = hash.size(), index;
	space *= 0.5;
	myVec3d delta = space * 0.5;

	for (int i = h_size - 1; i >= 0; i--) {
		index = i % 3;

		if (this->getComp(index) >= space.getComp(index)) {
			hash.set(i);

			space.getComp(i % 3) += delta.getComp(index);
		}
		else space.getComp(index) -= delta.getComp(index);
		
		if (index == 0)delta *= 0.5;
	}

	return hash;
}

string myVec3d::toString()
{
	stringstream s;
	s << "[" << x << "," << y << "," << z << "]";
	return s.str();
}

myVec3d::~myVec3d()
{
}
