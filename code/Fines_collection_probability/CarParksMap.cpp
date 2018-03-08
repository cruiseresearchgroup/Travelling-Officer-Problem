//
// CarParksMap.cpp
//
// Created on: NOV 25, 2014
// Author: wshao
//

#include<fstream>
#include<iostream>
#include <algorithm>  
#include<string>

#include "CarParksMap.h"

void CarParksMap::iniMap(const string filename)
{
	ifstream file(filename); // declare file stream
	if (!file.good())
	{
		cout << filename << " is not existed." << endl;
		system("pause");
	}

	string streetMaker;
	string sX;
	string sY;
	Point tmp;
	int  index = 0;

	while (file.good())
	{
		getline(file, streetMaker, ','); // read a string until next comma:   
		getline(file, sX, ','); // read a string until next comma:   
		getline(file, sY, '\n'); // read a string until next comma:   
		//getline(file, enter);
		
		tmp.m_Maker = streetMaker;
		tmp.x = stod(sX);
		tmp.y = stod(sY);
		tmp.m_index = index++;

		nodes.push_back(tmp);
	}


	//ini edeges
	weights weight;
	weight.distance = -1.0;
	weight.probability = -1.0;
	map<string, weights> tmp2;
	string str1; string str2;

	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		tmp2.insert(map<string, weights>::value_type(nodes[i].m_Maker, weight));
	}

	for (unsigned int j = 0; j < nodes.size(); j++)
	{	
		edges.insert(map<string, map<string, weights> > ::value_type(nodes[j].m_Maker, tmp2));
	}


	m_q = nodes.size();

}



int CarParksMap::m_readDisMat(const string filename)
{
	ifstream file(filename); // declare file stream
	if (!file.good())
	{
		cout << filename << " is not existed." << endl;
		system("pause");
	}

	string start; string end; string dis; string tmpStart;
	double distance;
	map<string, double> tmp;

	while (file.good())
	{
		getline(file, start, ','); // read a string until next comma:      
		getline(file, end, ',');
		getline(file, dis, '\n');
		distance = stod(dis);

		edges[start][end].distance = distance;
	}


	return 0;
}

double CarParksMap::TtoD(string time)
{
	int ihour, iminute;// , isecond;
	string hour;
	string minute;
	//string second;

	double hours, minutes;//, seconds;

	double t = 0;
	ihour = time.find(':');
	hour = time.substr(0, ihour);
	hours = stod(hour);
	
	iminute = time.size()-1;
	minute = time.substr(ihour+1, iminute);
	minutes = stod(minute);

	t = hours * 60 + minutes;

	return t;
}
void CarParksMap::m_readRecords(const string filename)
{
	ifstream file(filename); // declare file stream
	if (!file.good())
	{
		cout << filename << " is not existed." << endl;
		system("pause");
	}
	//streetMaker,vio_start,vio_end
	string streetMaker;
	string vioStart;
	string vioEnd;
	double Start;
	double end;

	while (file.good())
	{
		getline(file, streetMaker, ','); // read a string until next comma:      
		getline(file, vioStart, ',');
		getline(file, vioEnd, '\n');
		Start = TtoD(vioStart);
		end = TtoD(vioEnd);

		for (vector<Point>::iterator itNode = nodes.begin(); itNode != nodes.end(); itNode++)
		{
			if (itNode->m_Maker == streetMaker)
			{
				record r;
				r.maker = streetMaker;
				r.vioTime = Start;
				r.depTime = end;
				r.isCheck = false;
				r.isSense = false;
				signals.push_back(r);
				itNode->records.push_back(r);
			}
		}
	}
	std::sort(signals.begin(),signals.end(), SortByVioTime);
}

void CarParksMap::m_iniAnt(const int nAnt)
{
	for (int i = 0; i < nAnt; i++)
	{
		Ant tmpAnt;
		tmpAnt.m_iniTabu(nodes);
		m_ants.push_back(tmpAnt);
	}
}

void CarParksMap::m_iniAntBySearchSpace(vector<string>& m_searchSpace)
{
	for (unsigned int i = 0; i < m_ants.size(); i++)
	{
		m_ants[i].m_iniTabuBySerachSpace(m_searchSpace);
	}
}

void CarParksMap::m_getBestACOPath(vector<string>& best,double bsTime)
{

	double time = 1441;
	int benefit = -1;
	int temp = -1;
	for (unsigned int i = 0; i < m_ants.size(); i++)
	{
		m_ants[i].m_dLength = m_ants[i].m_path.size();
		time = m_ants[i].m_time;
		if (benefit < m_ants[i].m_dLength)
		{
			temp = i;
			benefit = m_ants[i].m_dLength;
			continue;
		}

		if (time  > (m_ants[i].m_time + 0.000001) && benefit == m_ants[i].m_dLength )
		{
			temp = i;
			time = m_ants[i].m_time;
		}
	}

	if ((int)best.size() < m_ants[temp].m_dLength )
	{
		best.clear();
		best = m_ants[temp].m_path;
	}

	if ((int)best.size() == m_ants[temp].m_dLength && bsTime > time)
	{
		best.clear();
		best = m_ants[temp].m_path;
	}
}

void CarParksMap::m_updatePheromone()
{
	vector<Ant>::iterator itAnts = m_ants.begin();
	for (; itAnts != m_ants.end(); itAnts++)
	{
		vector<string>::iterator it = itAnts->m_path.begin();
		for (; it != itAnts->m_path.end() - 1; it++)
		{
			edges[*(it)][*(it+1)].deltaPheromone += (itAnts->m_dLength) / (m_q);
			if ((m_q) == itAnts->m_dLength)
				edges[*(it)][*(it + 1)].deltaPheromone += (1440 * 1440) / (itAnts->m_time * itAnts->m_time);
		}
	}// calculate deltaPheromone in total serach space
    
	itAnts = m_ants.begin();
	for (; itAnts != m_ants.end(); itAnts++)
	{
		vector<string>::iterator it = itAnts->m_path.begin();
		for (; it != itAnts->m_path.end() - 1; it++)
		{
			edges[*(it)][*(it + 1)].pheromone = edges[*(it)][*(it + 1)].pheromone * m_rho + edges[*(it)][*(it + 1)].deltaPheromone;
		}
	}

	itAnts = m_ants.begin();
	for (; itAnts != m_ants.end(); itAnts++)
	{
		vector<string>::iterator it = itAnts->m_path.begin();
		for (; it != itAnts->m_path.end() - 1; it++)
		{
			edges[*(it)][*(it + 1)].deltaPheromone = 0.0;
		}
	}//initilize deltaPheromone value to 0 
}

double CarParksMap::m_getDistance(const Point start, const Point end)
{
	map<string, map<string, weights> >::iterator it = edges.find(start.m_Maker);

	map<string, weights>::iterator itsecond = it->second.find(end.m_Maker);

	return itsecond->second.distance;
}

void CarParksMap::m_iniPheromoneValues()
{
	map<string, map<string, weights>>::iterator itEdge = edges.begin();

	for (; itEdge != edges.end(); itEdge++)
	{
		for (map<string, weights>::iterator itWeight = itEdge->second.begin(); itWeight != itEdge->second.end(); itWeight++)
		{
			itWeight->second.deltaPheromone = 0.0;
			itWeight->second.pheromone = 1.0;
		}
	}
}