//
// Area.h
//
// Created on: NOV 26, 2014
// Author: wshao
//

#ifndef AREA_H_
#define AREA_H_

#include <fstream>
#include <vector>
#include <iostream>
#include<string>

using namespace std;

class Area
{
public: 
	Area(){}
	static vector<double> pLeave;
	static void iniPLeave(string filename)
	{
		ifstream file(filename); // declare file stream

		if (!file.good())
		{
			cout << filename << " cannot open." << endl;
			system("pause");
		}

		double value;
		string tmp;

		while (file.good())
		{
			getline(file, tmp, ','); // read a string until next comma:     
			value = stod(tmp);
			pLeave.push_back(1.0 - value);
		}
	}
};


#endif // !AREA_H_
