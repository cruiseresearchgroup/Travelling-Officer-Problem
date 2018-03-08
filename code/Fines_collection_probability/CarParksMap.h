//
// CarParksMap.h
//
// Created on: NOV 25, 2014
// Author: wshao
//
#ifndef CAR_PARKS_MAP_H_
#define CAR_PARKS_MAP_H_



#include "Point.h"
#include "Ant.h"

static bool SortByVioTime(record& v1, record& v2)
{
	return v1.vioTime < v2.vioTime;
}


class CarParksMap
{
public:
	CarParksMap()
	{
		m_rho = 0.3;
	}
	~CarParksMap(){}

	void iniMap(const string filename);
	int m_readDisMat(const string filename);
	void m_readRecords(const string filename);


	double m_getDistance(const Point start, const Point end);
	void m_iniPheromoneValues();
	void m_iniAnt(const int nAnt);
	void m_iniAntBySearchSpace(vector<string>& m_searchSpace);
	void m_getBestACOPath(vector<string>& best,double bestTime);
	void m_updatePheromone();

	vector<record> signals;

	map<string, map<string, weights>> edges;
	vector<Point> nodes;

	vector<Ant> m_ants;
	double m_q;
private:
	double TtoD(string time);
	double m_rho;
};



#endif