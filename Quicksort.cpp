#include "testlib.h"
#include <string>               

using namespace std;

int random_in_range(int a, int b)
{	return random() % (b - a + 1) + a; 
}

void swap(string &a, string &b)
{
	string temp = a;
	a = b;
	b = temp;
}

int partition(string arr[], int low, int high)
{ 
	int pivpos = random_in_range(low, high);
  	string  pivot = arr[pivpos];
  
	swap(arr[high], arr[pivpos]); //puts pivot to the end
  	
	int i = low, s = low;
 
	while (i < high)
  	{
		if (arr[i] >= pivot) //keeps the greater ones to the front 
      		{	i ++;      }
	    		
		else // if i is smaller
    		{ 
			swap(arr[i], arr[s]);
     			s ++;
      			i ++; 
		}
	}
  	swap(arr[high], arr[s]);
  	return s; 
}

void quicksort(string arr[], int low, int high)
{	
	if (high - low < 1)
    		return;
  
	int piv = partition(arr, low,  high);
  	
	quicksort(arr, low, piv - 1);
  	quicksort(arr, piv + 1, high); 
}

int main(int argc, char * argv[])
{	
	string * data;
              tester T(argc, argv, data);
              int length = T.get_number();  
        
	quicksort(data, 0, length-1);
               
              T.finish(); 
}
