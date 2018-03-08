//
// Officer.h
//
// Created on: Nov 25, 2014
// Author: wshao
//
#ifndef OFFICER_H_
#define OFFICER_H_

#include<iostream>
#include<queue>
#include<time.h>


#include "CarParksMap.h"


enum algorithm{greedy, ACO, nature };

const int maxIterCount = 20;
const int nAnts = 30;


class Officer
{
public:
	Officer()
	{
		m_index = 0;
		m_speed = 50; // meter/minute
		benifit = 0.0;
		saveTime = 0.0;
	}

	Officer(int index, double speed)
	{
		m_index = index;
		m_speed = speed;
		benifit = 0.0;
		saveTime = 0.0;
	}

	~Officer(){};

	int m_findPath(Point start, double time, int algorithm, double limitTime, double updateTime);
	int m_showPath();
private:
	void m_moveNextPoint(Point cur,Point& next,double curTime); //greedy 
	int m_greedyFindPath(); 
	void m_nature();
	void m_updateNode(Point next, double curTime);
	void m_calP(double curTime, Point curPoint);
	double getBenifits(Point PT,double time);
	void updateQueue(double time);

	void m_walkToNextNode(Point cur, Point& next, double curTime);
	void m_ACOFindPath();
	void updateSearchSpace(double time);

	void searchAll();


	double calTime(Point start, Point end);
	

	double benifit;
	double saveTime;

	CarParksMap m_map;
	int m_index;
	double m_startTime;
	Point m_start;

	vector<Point> m_path;
	queue<string> m_queue;
	vector<string> m_searchSpace;

	double m_endTime;
	double m_speed;
	double m_updateTime;
};
#endif