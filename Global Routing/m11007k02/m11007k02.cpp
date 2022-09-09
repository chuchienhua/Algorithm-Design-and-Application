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
#include <iomanip>
#include <list>
#include <climits>
#include <string>
#include <cmath>
using namespace std;

//tar zcvf m11007k02.tgz m11007k02
class NDcost
{
public:
    //////////////////set////////////////////
    void setnet(int netID) { _netID = netID; }
    void setX1(int x1) { _x1 = x1; }
    void setY1(int y1) { _y1 = y1; }
    void setX2(int x2) { _x2 = x2; }
    void setY2(int y2) { _y2 = y2; }

    int By1;
    int By2;
    int Bx1;
    int Bx2;
    int size;
    int capacity;
    vector<int> id;
    vector<int> path;
    vector<int> xs;
    vector<int> xt;
    vector<int> ys;
    vector<int> yt;
    vector<vector<int> >x;
    vector<vector<int> >y;
    vector<NDcost> NDcosts;
    //////////////////get////////////////////

    int getnet() { return _netID; }
    int getX1() { return _x1; }
    int getY1() { return _y1; }
    int getX2() { return _x2; }
    int getY2() { return _y2; }

private:
    int _netID;
    int _x1;
    int _y1;
    int _x2;
    int _y2;
};

int main (int argc, char **argv)
{
	if (argc  < 3 )
	{
		cout << "Usage: ./[exe] [input file] [output file]" << endl;
		
	}

	// open the input file
	ifstream infile;
	infile.open(argv[1],ios::in);
	if (! infile)
	{
		cout << "Error: the input file is not opened!!" << endl;
	}

	// parse the input file
	char buffer[10000];
    vector<NDcost> NDcosts;
    //parser start

    int By1;
    int By2;
    int capacity;
    vector<int> id;
    vector<int> path;
    vector<int> xs;
    vector<int> xt;
    vector<int> ys;
    vector<int> yt;
    vector<vector<int> >x;
    vector<vector<int> >y;
    

    while (!infile.eof())
    {
        infile >> buffer;
        if (!strcmp(buffer, "grid"))
        {

            infile >> buffer;
            By1 = atoi(buffer);

            infile >> buffer;
            By2 = atoi(buffer);
        }
        if (!strcmp(buffer, "capacity"))
        {

            //input default cost
            infile >> buffer;
            capacity = atoi(buffer);
        }
        if (!strcmp(buffer, "num"))
        {

            //set non default cost size
            infile >> buffer;
            if (!strcmp(buffer, "net"))
            {
                infile >> buffer;
                int size = atoi(buffer);
                NDcosts.resize(size);

                for (int i = 0; i < size; ++i)
                {
                    //input num net x1 y1 x2 y2
                    infile >> buffer;
                    NDcosts[i].setnet(atoi(buffer));
                    infile >> buffer;
                    NDcosts[i].setX1(atoi(buffer));
                    infile >> buffer;
                    NDcosts[i].setY1(atoi(buffer));
                    infile >> buffer;
                    NDcosts[i].setX2(atoi(buffer));
                    infile >> buffer;
                    NDcosts[i].setY2(atoi(buffer));
                }
            }
        }   
    }

    infile.close();
    // The following demonstrates how to use the parser
    cout << "grid: " << By1 << " " << By2 << endl;
    cout << "capacity: " << capacity << endl;
    cout << "num net: " << NDcosts.size() << endl;

    id.resize(NDcosts.size());
    path.resize(NDcosts.size());
    xs.resize(NDcosts.size());
    ys.resize(NDcosts.size());
    xt.resize(NDcosts.size());
    yt.resize(NDcosts.size());
    x.resize(10000);
    for (int i = 0; i < 10000; ++i)
    {
        x[i].resize(10000);
    }
    y.resize(10000);
    for (int i = 0; i < 10000; ++i)
    {
        y[i].resize(10000);
    }

    for (int i = 0; i < NDcosts.size(); ++i)
    {
        cout << NDcosts[i].getnet() << " "<< NDcosts[i].getX1() << " " << NDcosts[i].getY1() << " "<< NDcosts[i].getX2() << " " << NDcosts[i].getY2() << endl;

        id[i] = NDcosts[i].getnet();
        path[i] = abs(NDcosts[i].getX1() - NDcosts[i].getX2()) + abs(NDcosts[i].getY1() - NDcosts[i].getY2());
        xs[i] = NDcosts[i].getX1();
        ys[i] = NDcosts[i].getY1();
        xt[i] = NDcosts[i].getX2();
        yt[i] = NDcosts[i].getY2();
        x[i][0] = xs[i];
        y[i][0] = ys[i];
        //cout<<x[i][0]<<" "<<y[i][0]<<endl;
    }
    for(int xlocation=0 ;   xlocation   <   id.size() ; xlocation++)
    {
        int ylocation=0;
            if(xs[xlocation]<xt[xlocation])
            {
                    for(int xmin=xs[xlocation]; xmin<=xt[xlocation]; xmin++)
                    {
                        x[xlocation][ylocation]=xmin;
                        y[xlocation][ylocation]=ys[xlocation];
                        ylocation++;
                    }
            }

            if(xs[xlocation]>=xt[xlocation])
            {
                    for(int xmin=xs[xlocation]; xmin>=xt[xlocation]; xmin--)
                    {
                        x[xlocation][ylocation]=xmin;
                        y[xlocation][ylocation]=ys[xlocation];
                        ylocation++;
                    }
            }

            if(ys[xlocation]<yt[xlocation])
            {
                    for(int ymin=ys[xlocation]+1; ymin<=yt[xlocation]; ymin++)
                    {
                        x[xlocation][ylocation]=x[xlocation][ylocation-1];
                        y[xlocation][ylocation]=ymin;
                        ylocation++;
                    }
            }

            if(ys[xlocation]>=yt[xlocation])
            {
                    for(int ymin=ys[xlocation]-1; ymin>=yt[xlocation]; ymin--)
                    {
                        x[xlocation][ylocation]=x[xlocation][ylocation-1];
                        y[xlocation][ylocation]=ymin;
                        ylocation++;
                    }
            }
    }  

    std::ofstream outfile;
    outfile.open(argv[2], ios::out);
    if (!outfile.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        return 1;
    }

    for (int i = 0; i < NDcosts.size() ; i++)
    {
        cout << id[i] << " " << path[i] <<endl;
        outfile << id[i] << " " << path[i] <<endl;     
        for (int j = 0; j < path[i]; j++)
        {
            cout << x[i][j]<< " " << y[i][j] << " "<< x[i][j+1] << " " << y[i][j+1] << endl;
            outfile << x[i][j]<< " " << y[i][j] << " "<< x[i][j+1] << " " << y[i][j+1] << endl;
        }
    }
    outfile.close();
    return 0;
}