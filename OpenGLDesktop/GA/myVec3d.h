#pragma once
#include <math.h>
#include <sstream>
#include <string>
#include <bitset>
using namespace std;

class myVec3d
{

private:
	const float PI = 3.1415926535897932384626;

public:
	float x, y, z;
	myVec3d();
	myVec3d(float a, float b, float c);

	float dist(myVec3d v);
	float dist_sq(myVec3d v);
	float distLine(myVec3d a, myVec3d b);
	float dot(myVec3d v);
	float getMag();
	float& getComp(int index);
	bool inBox(myVec3d min, myVec3d max);
	bool inBox(myVec3d max);
	bool inSphere(myVec3d center, float radius);
	bool nearLine(myVec3d a, myVec3d b, float dist);
	myVec3d operator+(myVec3d v);
	myVec3d operator-(myVec3d v);
	myVec3d operator*(float f);
	myVec3d operator/(float f);
	myVec3d cross(myVec3d v);
	void abs();
	void operator*=(float f);
	void operator+=(myVec3d v);
	void operator-=(myVec3d v);
	void operator/=(float f);
	void operator=(myVec3d v);
	bool operator==(myVec3d v);
	void setComp(float a, float b, float c);
	void set(myVec3d v);
	void setRandom(float l, float h);
	void setRandom(float h);
	void setRandomByMag(float mag);
	void setRandom(myVec3d v);
	void setRandom(myVec3d min, myVec3d max);

	std::bitset<30> hash(myVec3d space);
	string toString();
	~myVec3d();
};

