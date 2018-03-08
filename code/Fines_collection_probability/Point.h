//
// Point.h
//
// Created on: Nov 25, 2014
// Author: wshao
//
#ifndef POINT_H_
#define POINT_H_

#include <map>
#include "Area.h"


struct record{
	string maker;
	double vioTime;
	double depTime;
	bool isCheck;
	bool isSense;
};

class Point
{
public:
	Point()
	{
		x = -1;
		y = -1;
		violation = false;
		m_index = -1;
	}
	Point(double x, double y, bool violation, int index)
	{
		this->x = x;
		this->y = y;
		this->violation = violation;
		m_index = index;
	}
	~Point()
	{}


	bool operator = (const Point &pt);
	bool operator == (const Point &ps);

	string m_Maker;
	double x;
	double y;
	int m_index;
	bool violation;
	double probobality;
	double calP(double time,double updateTime);

	vector<record> records;
private:
	
};

#endif