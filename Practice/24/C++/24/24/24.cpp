#include <iostream>
#include <fstream>
#include "json.hpp"
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
using json = nlohmann::json;

int main()
{
	json j, j1, j2 ;
	ifstream src("in.json") ;
	src >> j ;
	int p=0, s=0, k ;
	
	for (int i=0; i < j.size(); i++)
	{
		p=j[i]["userId"] ;
		for (int d=0; d < j.size(); d++)
		{
			if (j[i]["userId"]==j[d]["userId"] and j[i]["id"]!=-1)
			{
				if (bool(j[d]["completed"]) == true) 
				{k +=1 ;}
				j1[i]["userId"]=j[i]["userId"];
				j1[i]["task_completed"]=k ;
				if (j[i]["id"]!=j[d]["id"]) 
				{
					j[d]["id"]=-1 ;
				}
			}
		}
	}
	for (int i = 0; i < j1.size(); i++)
	{
		if (!empty(j1[i]))
		{
			j2[s]["userId"] = j1[i]["userId"] ;
			j2[s]["task_completed"] = j1[i]["task_completed"] ;
			s++ ;
		}
	}
	ofstream srco("out.json");
	srco << setw(2) << j2;
}