#include <stdio.h>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <time.h>

#include "Officer.h"
using namespace std;


int main()
{
	
	Area::iniPLeave("chinatown_pro.csv");//read distribution of violated period in the current area
	double startTime = 420; // Officer begin to collect money from this time
	double endTime = 1140;   // Officer end collecting fines at this time
	double updateTime = 5; // the violation information update frequency
	double speed = 70; //officers' avg speed
	Point startPoint(0, 0, false, 0);//index = 0, x = 0,y = 0, violation = false 
	Officer officer(1, speed);//index = 1,speed = 50 meters/minute	
	

	startPoint.m_Maker = "start";
	officer.m_findPath(startPoint, startTime, ACO, endTime, updateTime);
	officer.m_showPath();
	system("pause");
}