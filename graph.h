/* 
 * ==========================
 * File: graph.h
 * Author: Sebastián Colín 
 * Date: 14/11/2023
 * Description: This file defines 
 * a graph class and its methods. 
 * ==========================
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>


using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    		vector<int> *adjList;
		int *adjMatrix;

public:
	
  		void loadGraphList(string, int);
  		void loadGraphMat(string, int, int);
		Graph(int);
		Graph();
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
		string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
		bool contains(list<int>, int);
		void sortAdjList();
};

Graph::Graph() {
    edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    adjMatrix = new int [nodes * nodes];
    for (int i = 0; i < nodes * nodes; i++)
        adjMatrix[i] = 0;      // Every matrix node = 0
    edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u * nodes + v] = 1;
	adjMatrix[v * nodes + u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(), adjList[i].end());
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;

		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()) {
    	aux << q.front() << " ";
    	q.pop_front();
    }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";

	while (node != start) {
		reverse.push(node);
    	node = path[node][0];
  	}

	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  	}
	return aux.str();
}

void Graph::loadGraphList(string data, int a){
	adjList = new vector<int>[a];
	nodes = a;
	int u, v, i = 0;
	while ( i < data.size()) {
			u = (int)data[i+1] - 48;
			v = (int)data[i+3] - 48;
			i = i + 6;
			addEdgeAdjList(u,v);
	}
	sortAdjList();
}

void Graph::loadGraphMat(string data, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
	int u, v, i = 0;
	while (i < data.size()) {
		u = (int)data[i+1] - 48;
		v = (int)data[i+3] - 48;
		i = i + 6;
		addEdgeAdjMatrix(u,v);
	}
}

// HW Implementations 

std::string Graph::DFS(int start, int goal) {
	stack<int> st;
	list<int> visited;		
	vector<vector<int>> paths(nodes, vector<int>(1, -1)); // Initialize path remeber-er (wth)

	st.push(start); // Push first element into the stack

	string ans = depthHelper(start, goal, st, visited, paths);
	ans = ans + print_path(paths, start, goal);

	return ans;
}

string Graph::depthHelper(int current, int goal, stack<int> &st,
list<int> &visited, vector<vector<int>> &paths) {

    /*
        Base Case: target found
    */
	if (current == goal) {
		return print_visited(visited);
	/*
        Alt case: node non-existent
    */
	} else if (st.empty()) {
		return ("node not found");
	
	/*
        Initiates recursion searching for node
    */
	} else {
		current = st.top();
		st.pop();
		visited.push_back(current);

        /*
        We use current as the index because nodes are created in order
        */

		for (int i = 0; i < adjList[current].size(); i++) { 
			if (contains(visited, adjList[current][i]) == false) {
				st.push(adjList[current][i]);		
				paths[adjList[current][i]][0] = current;	
			}
		}
		return depthHelper(current, goal, st, visited, paths);
	}
	return "node not found";
}

std::string Graph::BFS(int start, int goal) {
	queue<int> qu;
	list<int> visited;
	
	vector<vector<int>> paths(nodes, vector<int>(1, -1)); // Initialize path remeber-er (wth) x2
	
	qu.push(start); // Push first element into the queue
	string ans = breadthHelper(start, goal, qu, visited, paths);
	ans = ans + print_path(paths, start, goal);

	return ans;
}

string Graph::breadthHelper(int current, int goal, queue<int> &qu,
list<int> &visited,vector<vector<int>> &paths) {

    /*
        Base Case: target found
    */
    if (current == goal) {
		return print_visited(visited);
    /*
        Alt case: node non-existent
    */
	} else if (qu.empty()) {
		return ("node not found");
    /*
        Initiates recursion searching for node
    */
	} else {
		current = qu.front();
		qu.pop();
		visited.push_back(current);


		for (int i = 0; i < adjList[current].size(); i++) {
			if (contains(visited, adjList[current][i]) == false) {
				qu.push(adjList[current][i]);
				if (paths[adjList[current][i]][0] == -1)
					paths[adjList[current][i]][0] = current;	
			}
		}
		return breadthHelper(current, goal, qu, visited, paths);
	}
	return "node not found";

}

#endif