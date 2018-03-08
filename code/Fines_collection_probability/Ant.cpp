// Ant.h
//
// Created on: NOV 12, 2014
// Author: wshao
//

#include "Ant.h"

void Ant::m_moveToNextPoint(const Point start, Point& NPT, vector<Point>& nodes, map<string, map<string, weights>>& edges)
{
	m_tabu[start.m_Maker] = true;
	m_iniProb(start, Probability, nodes,edges);

	double mRate = rnd(0, 1);
	double mSelect = 0;
	map<string, double>::iterator it = Probability.begin();

	for (; it != Probability.end(); it++) {

		if (m_tabu.find(it->first)->second == false)
			mSelect += it->second;
		if (mSelect >= mRate)
		{
			NPT.m_Maker = it->first;
			break;
		}
	}
}

void Ant::m_reIni(vector<string>& searchSpace)
{
	map<string, bool>::iterator it = m_tabu.begin();

	for (; it != m_tabu.end(); it++)
	{
		it->second = true;
	}

	vector<string>::iterator itS = searchSpace.begin();
	for (; itS != searchSpace.end(); itS++)
	{
		m_tabu[*itS] = false;
	}
	
	m_path.clear();
	m_dLength = 0;
	m_time = 0;

	m_dLength = m_path.size();
}

void Ant::m_iniTabu(vector<Point>& nodes)
{
	vector<Point>::iterator itN = nodes.begin();

	for (; itN != nodes.end(); itN++)
	{
		m_tabu.insert(pair<string, bool>(itN->m_Maker, true));
	}
}


void Ant::m_iniTabuBySerachSpace(vector<string>& serachSpace)
{
	vector<string>::iterator itS = serachSpace.begin();
	for (; itS != serachSpace.end(); itS++)
	{
		m_tabu.find(*itS)->second = false;
	}
}




void Ant::m_iniProb(const Point start, map<string, double>& pro, vector<Point>& nodes,map<string,map<string,weights>>& edges)
{
	//calculate total probability 

	double tmpSumProbability = 0;;

	map<string, map<string, weights>>::iterator itEdge = edges.find(start.m_Maker);

	vector<Point>::iterator itNode = nodes.begin(); 

	for (; itNode != nodes.end(); itNode++)
	{
		if (m_tabu.find(itNode->m_Maker)->second == false)
			tmpSumProbability += pow(itEdge->second.find(itNode->m_Maker)->second.pheromone, alpha) * pow(itNode->probobality, beta);
	}


	double P = -1;
	string name;

	itEdge = edges.find(start.m_Maker);

	for (itNode = nodes.begin(); itNode != nodes.end(); itNode++)
	{
		name = itNode->m_Maker;
		if (m_tabu[name] == false)
		{
			P = pow(itEdge->second.find(itNode->m_Maker)->second.pheromone,alpha) * pow(itNode->probobality, beta) / tmpSumProbability;
		}
		else
		{
			P = 0;
		}
		pro[name] = P;
	}
}