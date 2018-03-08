//
// CarPoint.cpp
//
// Created on: NOV 25, 2014
// Author: wshao
//

#include"Point.h"

bool Point::operator = (const Point &ps)
{
	this->x = ps.x;
	this->y = ps.y;
	this->m_Maker = ps.m_Maker;
	this->violation = ps.violation;

	this->records = ps.records;
	this->probobality = ps.probobality;
	return true;
}

bool Point::operator == (const Point &ps)
{
	if (this->m_Maker == ps.m_Maker)
		return true;
	else
		return false;

}

double Point::calP(double time,double curTime)
{
	vector<record>::iterator itRecord = records.begin();

	for (; itRecord != records.end(); itRecord++)
	{
		if (curTime < itRecord->vioTime || itRecord->isCheck == true || curTime> itRecord->depTime)
			continue;
		else
			return Area::pLeave[int(time - itRecord->vioTime)];
	}
	return 0.0;
}