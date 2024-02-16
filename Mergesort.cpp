#include "testlib.h"
#include <string>               

using namespace std;


void split(string A[], string B[], string C[], int size)
{ 
	int ai = 0, bi = 0, ci = 0;
  
	while (true)
  	{ 
		if (ai == size)
      			break;
   
 		B[bi] = A[ai];
    		ai ++;
    		bi ++;
    	
		if (ai == size)
      			break;
    	
		C[ci] = A[ai];
    		ai ++;
    		ci ++; 
	}
}

void merge(string X[], int xsize, string Y[], int ysize, string Z[])
{ 
	int xi = 0, yi = 0, zi = 0;

	while (xi < xsize && yi < ysize)
  	{ 
		if (X[xi] < Y[yi]) //adds x if x comes first else adds y
    		{ 
			Z[zi] = X[xi];
      			xi ++; 
		}
    		
		else
    		{
			Z[zi] = Y[yi];
      			yi ++; 
		}
    	
		zi ++;
	}
  
	while (xi < xsize) //if y finishes first
  	{
		Z[zi] = X[xi];
    		zi ++;
    		xi ++; 
	}
 	
	while (yi < ysize) //if x finishes first
  	{ 
		Z[zi] = Y[yi];
    		zi ++;
   	 	yi ++; 
	}
} // z is original array

void mergesort(string A[], int num)
{ 
	if (num <= 1)
		return;

	int Bsize = num - (num / 2);
  	int Csize = num / 2;
  
	string * B = new string[Bsize];
  	string * C = new string[Csize];
  
	split(A, B, C, num);
  
	mergesort(B, Bsize); //sorts first half
  	mergesort(C, Csize); //sorts second half
  	
	merge(B, Bsize, C, Csize, A);
  
	delete [] B; //deletes the pointers 
	delete [] C;
}


int main(int argc, char * argv[])
{	
	string * data;
        tester T(argc, argv, data);
        int length = T.get_number();  
        
	mergesort(data, length);
               
        T.finish(); 
}
