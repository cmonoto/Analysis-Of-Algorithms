
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;


struct vertex{
	int vertexNumber;
	int rr;
	int cc;
	int value;

};


int main(){

	int p, q;
	int row = 0;
	int col = 0;
	fstream in;              // input name
	ofstream out;			// output name
	int** a;

	in.open("input.txt", ios_base::in);       // open input.txt file

	out.open("output.txt", ios_base::out);     // open output.txt file

	if (!in.is_open())	cout << "Error, input file not founded" << endl;  // check if file open or not

	if (!out.is_open())  cout << "Error, output file not founded" << endl; //


	in >> p >> q;

	if (p == 0 && q == 0) return 0;

	vertex* adjList = new vertex[4 * p*q];

	a = new int *[p];				// create 1-D array
	for (int i = 0; i < q; i++)     // create 2-D array
	{
		a[i] = new int[q];
	}
	int x = 0;
	for (int i = 0; i < p; i++){
		for (int j = 0; j < q; j++){
			in >> a[i][j];                  // get input from input file
			for (int k = 0; k < 4; k++)     //  each vertex has four direction
			{                               // create the total row * total col * 4 direction
				adjList[x].rr = i;
				adjList[x].cc = j;
				adjList[x].value = a[i][j];    // get valuse
				x++;
			}
		}
	}

	x = 0;
	for (int i = 0; i < p*q * 4; i = i + 4){         // get vertex number of each vertex
		for (int j = 0; j < 4; j++){
			adjList[x].vertexNumber = i / 4;
			x++;
		}
	}

	vector< vector<int> > mylist;                     // create 2-D vector to get adjacency list
	mylist.resize(p*q);                             // the first vector size will be row * col


	for (int i = 0; i < p*q * 4; i = i + 4)
	{
		int j = i / 4;
		if (adjList[i].value == 0) continue;
		if (adjList[i].rr + adjList[i].value < p) {                                     // check if South neighbor exit, push it to adj list
			mylist.at(j).push_back(adjList[i].vertexNumber + q * adjList[i].value);
		}

		if (adjList[i].cc + adjList[i].value < q) {                                      // check if East neighbor exit, push it to adj list
			mylist.at(j).push_back(adjList[i].vertexNumber + adjList[i].value);
		}

		if (adjList[i].rr - adjList[i].value > -1)     {                                // check if North neighbor exit, push it to adj list
			mylist.at(j).push_back(adjList[i].vertexNumber - q * adjList[i].value);
		}

		if (adjList[i].cc - adjList[i].value > -1)        {                             // check if West neighbor exit, push it to adj list
			mylist.at(j).push_back(adjList[i].vertexNumber - adjList[i].value);
		}
	}

	bool *visited;                                                         //

	visited = new bool[p*q];
	for (int i = 0; i < p*q; i++)
	{
		visited[i] = false;                                                 // set up all vertex is not visited
	}

	stack <int> s;                                                         // create a stack to get path of DFS
	int start = 0;                                                        
	int exit = p*q - 1;
	s.push(start);                                                           // when reach each vertex, set staues as visited
	visited[start] = true;
	while (start != exit)                                                    // 
	{
		if (mylist.at(start).size() == 0)                                     // when the size == 0, it means that no neighbor of this vertex, so 
		{																	// we need pop the vector and update the start
			s.pop();
			start = s.top();
		}
		for (int i = 0; i < mylist.at(start).size(); i++)                     // check if all neighbor are visited or not
		{
			if (visited[mylist.at(start).at(i)] == false)                    // if not visited, mark as visited and goes to next vertex
			{
				start = mylist.at(start).at(i);
				visited[start] = true;
				s.push(start);
				break;
			}
			if (i == mylist.at(start).size() - 1){                           // if all visited, pop and update start again


				if (visited[mylist.at(start).at(mylist.at(start).size() - 1)] == true)
				{
					s.pop();
					start = s.top();
					break;
				}
			}
		}
	}

	stack <int> w;                                        // create a new stack to recurisve the output
	while (!s.empty())
	{
		w.push(s.top());
		s.pop();
	}
	int v;
	int z;
	while (!w.empty())
	{
		z = w.top();
		w.pop();
		if (w.empty()) break;                              // give two valuse and transfer it to character which 'S', 'E', 'W' ,and 'N'
		v = w.top();
		if (v - z >= p) out << 'S' << ' ';
		else if ((0 < (v - z)) && ((v - z)< p)) out << 'E' << ' ';
		else if ((0 < (z - v)) && ((z - v)< p))    out << 'W' << ' ';
		else if (z - v >= p) out << 'N' << ' ';

	}

	in.close();                                           // close the input and output files
	out.close();

	for (int i = 0; i< q; i++){                       // detele the array
		delete[]a[i];
	}
	delete[]a;

	delete[]visited;




	return 0;

}

