#include <iostream>
#include<string>
#include<conio.h>
#include <cmath>
#include<climits>
#define INF INT_MIN        //INF DEFINE WITH NEGATIVE INFINITE NUMBER
using namespace std;
class Stacks {    //I implement my own stack  class of satcks.
public:
	int Array[100];     //public attribute 
	int top = -1;       //intial the top is -1
	int count = 0;

	void push(int data) {
		Array[++top] = data;    //push function it will push the data into stack
		count++;
	}
	int pop() {
		int data = Array[top--]; //pop function it will pop the data from the stack
		count--;
		return data;

	}


	bool isEmpty() {
		return count == 0;         //is Empty funation  will return true if stack is empty /false if stack is not empty 
	}
};

class DirectedAcylicGraph :public Stacks{       //A DirectedAcylicGraph class inherited from Stacks class to use stack method in the DAG class 
public:
	int Ver;
	int egdevalue[100][100];       //weight's of an edge
	int vertices[100];             //vertices in DAG   
	bool visited[100];
	int distances[100];            //Distance Of vertices
	Stacks newnode = Stacks();

	void number_of_ver(){              //A function number_of_ver ask user to enter number of vertex and simple  initialize the vertices array integer (from 0 to so on), distance to 'INF' and all vertex as not visited.

		cout << "Enter the number of vertex you want to create (vertex start from 0 so,you enter the verteces+1)?? :";
		cin >> Ver;
		for (int i = 0; i < Ver; i++) {

			vertices[i] = i;
			distances[i] = INF;
			visited[i] = false;
		}

	}






	void addEdge() {    //addEgde function intialize the weight's of edge's from source to dest  of DAG by user input
		int S, D, weight, no_egde;
		cout << "How many edge's in your graph ??:"; cin >> no_egde;
		for (int i = 1; i <= no_egde; i++)
		{
			cout << "Enter the source:"; cin >> S;
			cout << "Enter the destination:"; cin >> D;   
			cout << "Enter weight of edge from path " << S << " to " << D << " :"; cin >> weight;//Edge weight input
			egdevalue[S][D] = weight;
		}

	}





	void LargerDistances(int source) {     //function will Print the longest Distance of Longest path..
		cout << "LONGEST path  from source " << source << " is :" << endl;

		for (int i = 0; i < Ver; i++){
			cout << "from " << source << " to " << i << ": ";
			if (distances[i] == INF || distances[i]<0) {
				cout << " -Infinity " << endl;
			}
			else {
				cout << distances[i] << endl;
			}

		}


		cout << endl;
	}






	void topo(int source) {  //function will take the vertex and mark's as visited  and push it's adjacent vertex to the stack if it's all vertex is visited or it's have no adjacent vertex remaing
		visited[source] = true;
		for (int next = 0; next < Ver; next++) {
			if (egdevalue[source][next] != 0 && visited[next] == false) {
				topo(next);       //RECURSIVE CALL TO MARK THE ADJACENT VERTEX TO SOURCE.
			}
		}
		newnode.push(source);              //Push into stack
	}
	void Topo_Sort() {    //function will call topo function for every vertices that is not  mark as visited.. 
		for (int i = 0; i < Ver; i++) {
			if (visited[i] == false) {
				topo(i);
			}

		}
	}

	void Topological_sort(){ //function will apply topoLOgical sort to every vertex in the graph
		Topo_Sort();
	}
	void update() {    //Update function will pop the data(verteces) from stack and update the distance of all verttice's from path_to_path
		while (newnode.isEmpty() == false) {      //while loop run while stack is not empty.. newnode is object of class Stack's
			int from = newnode.pop();         //pop the vertex from Stack and intialize in "from variable".  
			if (distances[from] != INF) { //INF infinity
				for (int next = 0; next < Ver; next++) {
					if (egdevalue[from][next] != 0) {
						if (distances[next]< distances[from] + egdevalue[from][next]) { //if distance of upcoming vertex is lessthen distance of starting vertex + weight of egde between them
							distances[next] = distances[from] + egdevalue[from][next];
						}
					}
				}
			}
		}
	}


	void LongestPath(int source) { //longest path function 
		Topological_sort();       //call Topological_sort
		distances[source] = 0;    //intialize the distance of source as 0
		update();                 //call update function 
		LargerDistances(source);  //calling of LargerDistance function      
	}
};

int main() {
	DirectedAcylicGraph Digraph; //object Of DirectedAcyclicGraph class
	Digraph.number_of_ver();     //calling method of DAG class 
	Digraph.addEdge();          //calling method of DAG class

	int s;

	cout << "***Enter the source  you want to find longest weighed simple path ***\n";
	cout << "Enter the source :"; cin >> s;

	Digraph.LongestPath(s);



	_getch();
}
