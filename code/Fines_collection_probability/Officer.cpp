//
// Officer.cpp
//
// Created on: NOV 25, 2014
// Author: wshao
//

#include"Officer.h"

void Officer::m_moveNextPoint(Point cur,Point& next,double curTime)
{
	m_calP(curTime,cur);
	double max = 0.00001;
	string minKey = "start";
	vector<Point>::iterator itNode = m_map.nodes.begin();
	for (; itNode != m_map.nodes.end(); itNode++)
	{
		if (max < itNode->probobality)
		{
			max = itNode->probobality;
			minKey = itNode->m_Maker;
		}
	}

	if (max < 0.0001)
		next.m_Maker = "NULL";
	else
		next.m_Maker = minKey;
}

void Officer::m_calP(double curTime, Point curPoint)
{
	double arriveTime;//estimate arrive time when get to the Point x
	vector<Point>::iterator itNode = m_map.nodes.begin();

	for (; itNode != m_map.nodes.end(); itNode++)
	{
		if (itNode->m_Maker == "start")
			itNode->probobality = 0.0;
		else
		{
			arriveTime = curTime + calTime(curPoint, *itNode);	
			itNode->probobality = itNode->calP(arriveTime,curTime);
		}
	}
}

int Officer::m_findPath(Point startPT, double startTime, int algorithm, double endTime,double updateTime)
{
	m_startTime = startTime;
	m_start = startPT;
	m_endTime = endTime;
	m_updateTime = updateTime;

	m_map.iniMap("chinatown_location.csv");
	m_map.m_readDisMat("chinatown_distance.csv");
	m_map.m_readRecords("Chinatown9_record.csv");

	switch (algorithm)
	{
	case greedy:
		m_greedyFindPath();
		break;
	case ACO:
		m_ACOFindPath();
		break;
	case nature:
		m_nature();
		break;
	}
	return 0;
}



void Officer::m_updateNode(Point PT,double curTime)
{
	vector<Point>::iterator itNode = m_map.nodes.begin();

	for (; itNode != m_map.nodes.end(); itNode++)
	{
		if (PT.m_Maker == itNode->m_Maker)
		{
			for (vector<record>::iterator itRecord = itNode->records.begin(); itRecord != itNode->records.end(); itRecord++)
			{
				if (curTime > itRecord->vioTime && curTime < itRecord->depTime)
				{
					itRecord->isCheck = true;
					break;
				}
			}
		}
	}
}
int Officer::m_showPath()
{
	cout << "benifit: "<<benifit << endl;
	cout << "saveTime: " << saveTime << endl;
	cout << m_path.size() << endl;

	//bool flag = false;

	//	for (unsigned int j = 0; j < m_map.signals.size(); j++)
	//	{
	//		for (unsigned int i = 0; i < m_path.size(); i++)
	//		{
	//			if (m_path[i].m_Maker == m_map.signals[j].maker)
	//				flag = true;
	//		}
	//		if (!flag)
	//			cout << m_map.signals[j].maker << endl;
	//		flag = false;
	//	}
	//
	

	for (unsigned int i = 0; i < m_path.size(); i++)
		cout << m_path[i].m_Maker << "-->";

	return 0;
}

int Officer::m_greedyFindPath()
{
	Point next;
	double time = m_startTime;
	m_path.clear();
	m_path.push_back(m_start);
	Point current;
	current = m_start;
	while (time < m_endTime)
	{
		m_moveNextPoint(current, next, time);
		if ("NULL" == next.m_Maker)
		{
			time = time + 1.0;
			saveTime = saveTime + 1.0;
			continue;
		}		
		m_path.push_back(next); 
		time += calTime(current, next);
		benifit += getBenifits(next, time);
		m_updateNode(next, time);
		current = next;
	}

	return 0;
}


void Officer::m_ACOFindPath()
{
	Point next;
	double time = m_startTime;
	m_path.clear();
	m_path.push_back(m_start);
	Point current;
	current = m_start;

	m_map.m_iniAnt(nAnts);

	while (time < m_endTime)
	{	
		updateSearchSpace(time);
		if (m_searchSpace.empty())
		{
			time = time + 1.0;
			saveTime = saveTime + 1.0;
			continue;
		}
		m_map.m_q = m_searchSpace.size();
		m_map.m_iniAntBySearchSpace(m_searchSpace);

		//double aaaa = clock();
		m_walkToNextNode(current, next, time);
		//double bbbb = clock();
		//cout << "time is :" << (double)(bbbb - aaaa) / CLOCKS_PER_SEC << endl;

		if ("NULL" == next.m_Maker)
		{
			time = time + 1.0;
			saveTime = saveTime + 1.0;
			continue;
		}
		m_path.push_back(next);
		cout << next.m_Maker<<"-->";

		vector<record>::iterator itSignal = m_map.signals.begin();

		for (; itSignal != m_map.signals.end(); itSignal++)
		{
			if (itSignal->maker == next.m_Maker && itSignal->isCheck == false)
			{
				itSignal->isCheck = true;
				break;
			}
		}

		time += calTime(current, next);
		benifit += getBenifits(next, time);
		m_updateNode(next, time);
		current = next;
	}
}

void Officer::m_walkToNextNode(Point curPT,Point& nextPT, double curTime)
{
	double time = curTime;
	Point PT;
	Point start = curPT;

	vector<string> S_best;
	double best_time = -1;
	m_map.m_iniPheromoneValues();
	for (int j = 0; j < nAnts; j++)
	{
		m_map.m_ants[j].m_reIni(m_searchSpace);
	}


	for (int i = 0; i < maxIterCount; i++)
	{
		for (int j = 0; j < nAnts; j++)
		{
			while (time < m_endTime && m_map.m_ants[j].m_path.size() < m_searchSpace.size() + 1)
			{
				m_calP(time, start);
				m_map.m_ants[j].m_moveToNextPoint(start, PT, m_map.nodes, m_map.edges);
				
				if (start == PT || PT.m_Maker == "")
				{
					m_map.m_ants[j].m_time = time;
					break;
				}
				m_map.m_ants[j].m_path.push_back(PT.m_Maker);
				time += calTime(start, PT);
				start = PT;
			}

			time = curTime;
			start = curPT;
		}



		m_map.m_getBestACOPath(S_best, best_time);

		if (S_best.size() > m_searchSpace.size() - 1 || S_best.size() == 0)
			break;
		m_map.m_updatePheromone();
		for (int j = 0; j < nAnts; j++)
		{
			m_map.m_ants[j].m_reIni(m_searchSpace);
		}
	}
	if (S_best.size() == 0)
		nextPT.m_Maker = "NULL";
	else
		nextPT.m_Maker = S_best[0];
}


double Officer::getBenifits(Point PT, double time)
{
	vector<Point>::iterator itPoint = m_map.nodes.begin();

	for (; itPoint != m_map.nodes.end(); itPoint++)
	{
		if (PT.m_Maker == itPoint->m_Maker)
		{
			vector<record>::iterator itRecord = itPoint->records.begin();

			for (; itRecord != itPoint->records.end(); itRecord++)
			{
				if (time < itRecord->vioTime || itRecord->isCheck == true || time> itRecord->depTime)
					continue;
				else
					return 1.0;
			}
		}
	}
	return 0.0;
}

void Officer::m_nature()
{
	double time = m_startTime;

	Point next;
	m_path.clear();
	m_path.push_back(m_start);
	Point current;
	current = m_start;
	updateQueue(time);
	while (time < m_endTime)
	{
		if (m_queue.empty())
		{
			time = time + 1.0;
			updateQueue(time);
			saveTime = saveTime + 1.0;
			continue;
		}
		else 
		{
			
			next.m_Maker = m_queue.front();
			m_queue.pop();
			m_path.push_back(next);
		}
		time += calTime(current, next);
		benifit += getBenifits(next, time);
		m_updateNode(next, time);
		updateQueue(time);
		current = next;
	}
}
void Officer::updateQueue(double time)
{

	vector<record>::iterator itSignal = m_map.signals.begin();

	for (; itSignal != m_map.signals.end(); itSignal++)
	{
		if (time > itSignal->vioTime && time < itSignal->depTime && itSignal->isSense == false)
		{
			m_queue.push(itSignal->maker);
			itSignal->isSense = true;
		}
	}
}

void Officer::updateSearchSpace(double time)
{
	m_searchSpace.clear();
	m_searchSpace.reserve(0);
	vector<record>::iterator itSignal = m_map.signals.begin();

	for (; itSignal != m_map.signals.end(); itSignal++)
	{
		if (time > itSignal->vioTime && time < itSignal->depTime  && itSignal->isCheck == false)
		{
			m_searchSpace.push_back(itSignal->maker);
		}
	}
}

double Officer::calTime(Point start, Point end)
{

	return m_map.m_getDistance(start, end) / m_speed;
}



