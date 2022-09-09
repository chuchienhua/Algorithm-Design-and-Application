#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<typeinfo>
#include<algorithm>
using namespace std;

//tar zcvf m11007k02.tgz m11007k02

struct Chords
{
	int p1 = -1;
	int p2 = -1;
	int k = -1;
	Chords(int Start, int End) {
		p1 = Start;
		p2 = End;
	}
};
vector <Chords> planar;
vector <Chords> Result;
int ** dot;
int Max(int i, int j) {
	if (i >= j) {
		return i;
	}
	else
	{
		return j;
	}
}
int Find_K(int j) 
{
	for (int idx = 0; idx < planar.size(); idx++) {
		if (planar[idx].p1 == j)
		{
			planar[idx].k = planar[idx].p2;
			return planar[idx].k;
			
		}
		else if (planar[idx].p2 == j)
		{
			planar[idx].k = planar[idx].p1;
			return planar[idx].k;			
		}
	}
	return 0;
}
int MIS(int i, int j) 
{
	if (dot[i][j] != -1)
	{
		return dot[i][j];
	}
	if (i >= j) {
		return 0;
	}
	else
	{
		int k = Find_K(j);
		//Case1 : K在兩點之外
		if (k < i || k > j)
		{
			dot[i][j - 1] = MIS(i, j - 1);
			return dot[i][j - 1];
		}
		//Case2 : K在兩點之內
		else if (k > i && k < j)
		{
			dot[i][j - 1] = MIS(i, j - 1);
			dot[i][k - 1] = MIS(i, k - 1);
			dot[k + 1][j - 1] = MIS(k + 1, j - 1);
			if (dot[i][j - 1] < dot[i][k - 1] + 1 + dot[k + 1][j - 1])
			{
				return dot[i][k - 1] + 1 + dot[k + 1][j - 1];
			}
			else
			{
				return dot[i][j - 1];
			}
		}
		//Case3
		else if (k == i)
		{
			dot[i + 1][j - 1] = MIS(i + 1, j - 1);
			return dot[i + 1][j - 1] + 1;
		}
	}
	return 0;
}

int GResult(int i,int j) {
	if (i >= j) {
		return 0;
	}
	else
	{
		int k = Find_K(j);
		//Case1 : K在兩點之外
		if (k < i || k > j)
		{
			return GResult(i, j - 1);
		}
		//Case2 : K在兩點之內
		else if (k > i && k < j)
		{
			if (dot[i][j - 1] < dot[i][k - 1] + 1 + dot[k + 1][j - 1])
			{	
				//cout << j << "	" << k << endl;
				Result.push_back(*new Chords(j, k));
				return GResult(i,k - 1) + 1 + GResult(k + 1,j - 1);
			}
			else
			{
				return GResult(i,j - 1);
			}
		}
		//Case3
		else if (k == i)
		{
			Result.push_back(*new Chords(i, j));
			return GResult(i + 1, j - 1) + 1;
		}
	}
	return 0;
}

void swap(int &i, int &j) {
	int temp = 0;
	temp = i;
	i = j;
	j = temp;
}

void swap(vector<Chords> v, int x, int y) {
	Chords temp = v[x];
	v[x] = v[y];
	v[y] = temp;

}
	
int partition(vector<Chords> &values, int left, int right) {
	int pivotIndex = left + (right - left) / 2;
	int pivotValue = values[pivotIndex].p1;
	int i = left, j = right;
	Chords temp(-1,-1);
	while (i <= j) {
		while (values[i].p1 < pivotValue) {
			i++;
		}
		while (values[j].p1 > pivotValue) {
			j--;
		}
		if (i <= j) {
			temp = values[i];
			values[i] = values[j];
			values[j] = temp;
			i++;
			j--;
		}
	}
	return i;
}

void quicksort(vector<Chords> &values, int left, int right) {
	if (left < right) {
		int pivotIndex = partition(values, left, right);
		quicksort(values, left, pivotIndex - 1);
		quicksort(values, pivotIndex, right);
	}
}

void SortResult() {
	for (int i = 0; i < Result.size()-1; i++) {
		if (Result[i].p1 > Result[i].p2) {
			swap(Result[i].p1, Result[i].p2);
		}
	}
	quicksort(Result, 0, Result.size()-1);
}

int main(int argc, char **argv)
{
	if (argc  < 3 )
	{
		cout << "Usage: ./[exe] [input file] [output file]" << endl;
		return 1;
	}

	// open the input file
	ifstream infile;
	infile.open(argv[1],ios::in);
	if (! infile)
	{
		cout << "Error: the input file is not opened!!" << endl;
		return 1;
	}
	// parse the input file
	cout << "======================" << endl;
	cout << "        Parser        " << endl;
	cout << "======================" << endl;

	char buffer[10000];

	infile >> buffer;
	int numChord = atoi(buffer);

	dot = new int *[numChord];
	for (int i = 0; i < numChord; i++)
	{
		dot[i] = new int[numChord];
	}
	for (int i = 0; i < numChord; i++) {
		for (int j = 0; j < numChord; j++) {
			dot[i][j] = -1;
		}
	}
	cout << argv[1] << endl;
	cout << "#Chords:" << numChord/2 << endl;

	for (int i = 0; i < numChord / 2; ++i)
	{
		infile >> buffer;
		int point1 = atoi(buffer);
		infile >> buffer;
		int point2 = atoi(buffer);
		//------------------------------------
		struct Chords Temp(point1, point2);
		planar.push_back(Temp);
		//------------------------------------
	}
	int ResultNum = MIS(0, numChord - 1);
	//cout << ResultNum << endl;
	GResult(0, numChord - 1);
	SortResult();

	//open the output file
	ofstream outfile;
	outfile.open(argv[2], ios::out);
	if (!outfile.is_open())
	{
		cout << "Error: the output file is not opened!!" << endl;
		return 1;
	}
    
	outfile << ResultNum << endl;
	for (int i = 0; i < Result.size(); i++) 
	{
		outfile << Result[i].p1 << " " << Result[i].p2 << endl;
	}
	outfile.close();
	return 0;
}