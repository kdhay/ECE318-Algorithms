#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct road
{
	string n, type;
  	int start, end;
  	double length;

  	road(string title, string roadtype, int begin, int last, double distance)
	{
    		n = title;
    		type = roadtype;
    		start = begin;
    		end = last;
    		length = distance;
	}
};


struct node
{
	double longitude, latitude, distance;
  	string state, name;
  	int lineNUM;
  	vector<road> roads;

  	node(double longi, double lati, double dist, string sta, string nam, int num)
	{
    		longitude = longi;
    		latitude = lati;
    		distance = dist;
   	 	state = sta;
    		lineNUM = num;
    		name = nam;
	}

  	void insert_roads(road a)
	{
    		roads.push_back(a);
  	}
};

int main()
{
	vector<node> location;
  	ifstream inFile, inFile2;
  	
	int lane = 0;
  	inFile.open("/home/www/class/een318/intersections.txt");
  
	if(inFile.fail())
    		cout << "Failed to open intersectons.txt " << endl;
  
	string n;
  	getline(inFile, n);
  
	while(!inFile.eof())
	{
    		string line = "";
    		string lo = "";  string la = ""; string di = ""; string st = ""; string na = "";
    		getline(inFile, line);
    		int i = 0;
    
		while(line[i] == ' ')
      			i++;
    		
		int j = 0;
    
		while(line[i] != ' ')
		{
      			lo = lo + line[i];
      			i++; 
			j++;
		}

	    	while(line[i] == ' ')
      			i++;
	
     		for(int j = i; line[i] != ' '; j++)
		{
      			la = la + line[i];
      			i++;
		}
    
		while(line[i] == ' ')
      			i++;
    
		for(int j = i; line[i] != ' '; j++)
		{
      			di = di + line[i];
      			i++;
		}

    		while(line[i] == ' ')
      			i++;
    
		for(int j = i; line[i] != ' '; j++)
		{
      			st = st + line[i];
     			i++;
		}
    
		while(line[i] == ' ')
      			i++;
	
    		for(int j = i; i < line.length(); j++)
		{
      			na = na + line[i];
      			i++;
		}

    
		node place(stod(lo), stod(la), stod(di), st, na, lane);
    		location.push_back(place);
    		lane++;
  	}
  	
	inFile.close();

  	inFile2.open("/home/www/class/een318/connections.txt");
  
	if(inFile2.fail())
   		 cout << "Failed to open file." << endl;
  
	while(!inFile2.eof())
	{        //READ CONNECTIONS.TXT
    		string a, b, c, d, e;
    		getline(inFile2, a, ' ');
    		getline(inFile2, b, ' ');
    		getline(inFile2, c, ' ');
    		getline(inFile2, d, ' ');
    		getline(inFile2, e);

    		int one = stoi(c);
    		int two = stoi(d);
    		double three = stod(e);
    
		if(one > 12348129)
       			one = 0;
    
		if(two > 31242135)
       			two = 0;
    
		if(three > 12342173)
       			three = 0;
    
		road path(a, b, one, two, three);
   	 	location[one].insert_roads(path);
    		location[two].insert_roads(path);
  	}

  	int p = 0;
  
	while(true)
	{
    		int input;
    
		if(p == 0)
		{
     			cout << "Location varies from 1 - 29145" << endl;
     			cout << "Enter the location to start: " << endl;
     			cin >> input;
    			cout << "Location to start: " << input << endl << endl;
    		}
    
		cout << "Location " << input << ", " << location[input].distance << " miles from " << location[input].name << ", " << location[input].state << endl;
    		cout << "roads leaading away: " << endl;
    
		int i = 0;
    
		while(i < location[input].roads.size())
		{
      			cout << "   " << i+1 << ":  " << location[input].roads[i].n << ",  " << location[input].roads[i].length << " miles to location ";
      
			if(location[input].roads[i].start == input)
        			cout << location[input].roads[i].end << endl;
      			
			else
        			cout << location[input].roads[i].start << endl;
      			i++;
    		}
    		
		int num;
    		cout << "take which road?  " ;
    		cin >> num;
    
		if(num > i)
		{
      			cout << "Invalid entry. Start over" << endl;
      			break;
		}
    
		if(location[input].roads[num].start == input)
      			input = location[input].roads[num].end;
    
		else
      			input = location[input].roads[num].start;
    		p++;
    	}

 	inFile2.close();
  	return 0;
}

