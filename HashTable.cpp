#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>


using namespace std;

unsigned int hashf(string s)
{	unsigned int h = 987123654;
  	
	for (int i = 0; i < s.length(); i += 1)
  		 h = h * 691 + s[i];
 	
	if (h < 0)
    		h = -h;
  	return h;
}

struct place
{	int num_code;
	string state;
	string name;
 	int pop;
 	double area;
 	double lat;
 	double longit;
 	int road_intersect;
 	double distance;

	place(int nu, string s, string n, int p, double a, double la, double lo, int r, double d)
 	{	num_code=nu;
   		state=s;
		name=n;
		pop=p;
		area=a;
		lat=la;
		longit=lo;
		road_intersect=r;
		distance=d;
	}
	
	void print()
	{
		cout<<num_code<< " "<<state<<" "<< name<<" "<< pop<< " "<< area<<" "<<lat<< " "<< longit<< " "<<road_intersect<< " "<< distance<<endl;
	}

};

struct Link
{	place * P;
  	Link * next;

	Link(place * Pl = NULL, Link * n = NULL)
  	{ 	P = Pl;
    		next = n;
	} 
	
	
};

void print_links(Link * content)
{
	while(content!= NULL)
	{	cout<<content->P->num_code<<" "<<content->P->state<<" "<<content->P->name<<" "<<content->P->pop<<" "<<content->P->area<<" "<<content->P->lat<<" "<<content->P->longit<<" "<<content->P->road_intersect<<" "<<content->P->distance<<endl;
		content=content->next;
	}
}

/*	
place * find(Link * ptr, string n, string st)
{	//unsigned pos = hashf(n);
	//Link * ptr = hashtable[pos];
	
	while(ptr!=NULL)
	{
		if(ptr->P->state==st)
			return ptr->P;
		
		ptr=ptr->next;
	}
	return NULL;
}

void find_all_names(Link * ptr,string n)
{	Link * All_Names = NULL;
	//unsigned int pos = hashf(n);
	//Link * ptr = hashtable[pos];
	
	while(ptr!=NULL)
	{	if(ptr->P->name == n)
		{	All_Names=new Link(ptr->P, All_Names);
			pos++;
		}
	}
}
*/
Link ** hashtable[30000]; 

int main()
{
	Link ** hashtable = new Link * [30000](); //NULL pointers
	
	ifstream fin;
	fin.open("/home/www/class/een318/named-places.txt");
	 
	int num_code, pop, road_intersect;
	string state, name;
	double area, lat, longit, distance;
	string s;

	if (fin.fail())
	{
		cout << "Couldn't open the file\n";
        	exit(1);
    	}

   	else
   	{
        	while(getline(fin, s))
	        {
			if(fin.fail())
			{
				cout<<"Could not open file."<<endl;
				break;
            		}

			num_code = stoi(s.substr(0,8));
			state = s.substr(8,2);
			
			//town name
			for(int i=10; i<114; i++)
			{	if(s[i]==' ' && s[i+1]==' ')
				{	name=s.substr(10,i-10);
					break;
				}
			}

			for(int i=58; i<66; i++)
			{	if(s[i]!=' ')
				{	pop =  stoi(s.substr(i,66-i));
					break;
				}
			}

			for(int i=67; i<80; i++)
			{	if(s[i]!= ' ')
				{	area = stod(s.substr(i,80-i));
					break;
				}
			}

			for(int i=80; i<90; i++)
			{	if(s[i]!= ' ')
				{	lat = stod(s.substr(i,90-i));
					break;
				}
			}

			for(int i= 90; i<101; i++)
			{	if(s[i]!=' ')
				{	longit = stod(s.substr(i,101-i));
					break;
				}
			}
			
			for(int i=101; i<106; i++)
			{	if(s[i]!= ' ') 
				{	road_intersect = stoi(s.substr(i,106-i));
					break;
				}
			}
 			
			for(int i=106; i<=114; i++)
			{	if(s[i]!= ' ')
				{	distance = stod(s.substr(i, 114-i));
					break;
				}
			}
			
			int const size = 30000;
			unsigned int h=hashf(name);
			h=h%size;
			
			Link * ptr = hashtable[h];

			while(ptr != NULL)
			{	ptr=ptr->next;
			}
			if(ptr==NULL)
				hashtable[h] = new Link(new place(num_code, state, name, pop, area, lat, longit, road_intersect, distance)); 
			
        	}
	}
   	fin.close();

	while(true)
	{
		cout<<"Welcome to my cool program!"<<endl;
		cout<<"Type command: "<<endl<<"S - The computer will provide all of the information of the desired town in said state."<<endl;
		cout<<endl<< "/////////////////////////////////////////////////////////////"<<endl;
		cout<<"N - The computer will provide all of the information for all places with the given name in any state"<<endl;
		cout<<endl<<"//////////////////////////s///////"<<endl;
		cout<<"Q - Exit the program" << endl;
 
		cout<<endl<<"-----------------------------------------------"<< endl;

		string command;
		string name;
		string state;

		cin>>command;

		if(command=="S")
		{	cout<<endl;
			cout<<"Please type the name of the city."<<endl;
			cin.ignore();
			getline(cin, name);
			cout<<endl;
			cout<<"Please type the state abbreviations for the city you entered."<<endl;
			cin>>state;
	
			unsigned int pos = hashf(name);
			pos=pos%30000;
			
			if(hashtable[pos] == NULL)
			{	cout<<"The town you've entered does not exist."<<endl;
				continue;
			}
			Link * place = hashtable[pos];
			
			while(place->P->state != state)
			{
				place = place->next;
			} // keeps moving through until finds the one
			//print_links(place);
			place->P->print();
		}

		if(command=="N")
		{	cout<<endl;
                        cout<<"Please type the name of the city."<<endl;
                        cin.ignore();
                        getline(cin, name);
                        cout<<endl;
			
			unsigned int pos = hashf(name);
			pos=pos%30000;
			

			if(hashtable[pos] == NULL)
			{	cout<<"The town name you've entered does not exist."<<endl;
				continue;
			}
			Link * place = hashtable[pos];
			
			while(place->P->name != name)
			{
				place = place->next;
			} 
			//print_links(place);
			place->P->print();

		}

		if(command=="Q")
			break;
	}
        
	return 0;
}

