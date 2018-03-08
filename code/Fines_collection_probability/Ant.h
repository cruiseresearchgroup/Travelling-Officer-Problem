// Ant.h
//
// Created on: Dec 1, 2014
// Author: wshao
//

#ifndef ANT_H_
#define ANT_H_

#include <time.h>
#include<iostream>
#include<string>


#include"Point.h"

struct weights
{
	double distance;
	double pheromone;
	double deltaPheromone;
	double probability;
};

class Ant
{
public:
	Ant(){
		m_dLength = 0;
		m_time = 0;
		alpha = 1.0;
		beta = 2.0;
	}
	~Ant(){}

	void m_moveToNextPoint(const Point start, Point& NPT, vector<Point>& nodes, map<string, map<string, weights>>& edges);
	void m_reIni(vector<string>& searchSpace);
	void m_iniTabu(vector<Point>& nodes);
	void m_iniTabuBySerachSpace(vector<string>& serachSpace);

	int m_dLength;
	double m_time;
	double rho;
	vector<string> m_path;

private:
	double  rnd(int low, double uper)
	{
		double p = (rand() / (double)RAND_MAX)*((uper)-(low)) + (low);
		return (p);
	};

	void m_iniProb(const Point start, map<string, double>& pro, vector<Point>& nodes, map<string, map<string, weights>>& edges);

	int rnd(int uper)
	{
		return (rand() % uper);
	};
	map<string, bool> m_tabu;//true means this points has been added to path
	map<string, double> Probability;
	double alpha;
	double beta;
};

#endif