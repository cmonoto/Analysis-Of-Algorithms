
#include <iostream>
#include <vector>
#include <string>
#include <fstream>



using namespace std;



int b, n, k; //  b == balls, n == number of baskets, k == number of balls in one basket


int memoization(int b, int n, int k, int **a)
{
	if (a[b][n] > 0)
	{
		return a[b][n];
	}
	else if (b == 0 && n == 0) // when no ball and no basket will return 1
	{
		a[b][n] = 1;
		return a[b][n];
	}
	else if (n == 0){         // when no basket has some balls will return 0

		a[b][n] = 0;
		return a[b][n];

	}
	else if (b == 1) {       // check if only one ball, check if k == 1 or not  
		if (k == 0) {		// if k == 0, return 0
			a[b][n] = 0;	
			return a[b][n]; 
		}
		else {				// if k > 0, return number of baskets(n)
			a[b][n] = n;
			return  a[b][n];
		}

	}

	for (int i = 0; i <= k; i++)            // this for loop is to find out the sum of memoization from (b-i, n-1,k )
	{										// i from 0 to k, for example f(3, 3, 2) base on f(3,2,2)+f(2,2,2) + f(1,2,2)
		if (b - i >= 0 && n >= 0)			//  and then f(3,2,2) = f(3,1,2) + f(2,1,2) + f(1,1,2)
		{
		a[b][n] += memoization(b - i, n - 1, k, a);
		}
	}
	return a[b][n];
}

int main()
{
	int p;
	fstream in;              // input name
	ofstream out;			// output name
	int **a;

	in.open("input.txt", ios_base::in);       // open input.txt file

	out.open("output.txt", ios_base::out);     // open output.txt file

	if (!in.is_open())	cout << "Error, input file not founded" << endl;  // check if file open or not
																		//
	if (!out.is_open())  cout << "Error, output file not founded" << endl; //
	
	

	in >> p;                              // assign the first number to p which is how many problems 

	for (int i = 0; i < p; i++)          
	{
		in >> b >> n >> k;					// assign three number to balls baskets maxballs
		a = new int *[b + 1];				// create 1-D array
		for (int i = 0; i < b + 1; i++)     // create 2-D array
		{
			a[i] = new int[n + 1];
		}
		for (int i = 0; i < b + 1; i++)     
		{
			for (int j = 0; j < n + 1; j++)
			{
				a[i][j] = 0;                 // assign those array to 0
			}
		}
		out << b << "\t" << n << "\t" << k << "\t" << memoization(b, n, k, a) << endl;       // output the number to output file
	//	memset(a, 0, sizeof(a));             // reset the array
                for(int i=0; i< b+1; i++){
                    delete[]a[i];
		}
		delete[]a;
	}
               

		in.close();
		out.close();       // close the file


}
