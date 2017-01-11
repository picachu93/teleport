/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : spacemst.c

 * Purpose : Educational

 * Creation Date : 11-01-2017

 * Last Modified : Τετ 11 Ιαν 2017 07:03:17 μμ EET

 * Created By :  Stamatios Anoustis

 _._._._._._._._._._._._._._._._._._._._._.*/

/*------------------Includes and global definitions---------------------*/
#include <stdio.h> 
#include <stdlib.h>

int B[10000];  //costs of teleport installation
int A[10000][10000]; //costs of direct transmission 
int EXIT_STATUS = 0;

/*-----------------Main Code-------------------------------------------*/

//A structure to represent an adjacency list node
struct AdjListNode {

  int dest;
  struct AdjListNode* next;

};

//A structure to represent an adjacency list
struct AdjList {

  struct AdjListNode* head; //pointer to head node of list

}; 

//A structure to represent the Graph.Its an array of 
//adjacency lists.Size of array V.
struct Graph {

  int V;  //number of vertices
  struct AdjList* array;

};  

//A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {

  struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
  newNode->dest = dest;
  newNode->next = NULL;
  return newNode;

};

//A utility function to create a new Graph of V nodes
struct Graph* newGraph(int V) {

  struct Graph* newGraph = (struct Graph*) malloc(sizeof(struct Graph));
  newGraph->V = V;  
  //Create an array of adjacency lists of size V.
  newGraph->array = (struct AdjList*) malloc(V*sizeof(struct AdjList));
  for (int i = 0; i < V; i++) {

  newGraph->array[i].head = NULL;

  }

  return newGraph;

};

//A utility function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {

  struct AdjListNode* newNode = newAdjListNode(dest);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  //The symmetric work must be done for undirected graph
  newNode = newAdjListNode(src);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;

};

// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph) {

  for (int i = 0; i < graph->V; i++) {
    struct AdjListNode* pCrawl = graph->array[i].head;
    printf("\n Adjacency list of vertex %d\n head ", i);
    while (pCrawl) {

      printf("-> %d", pCrawl->dest);
      pCrawl = pCrawl->next;

    }

    printf("\n");

  }

};

int main (int argc, char** argv) {

	int N;  //number of planets;suppose 2 <= N <= 10000
	int K;  //number of teportable planets 0 <= K <= N
	int M;  //number of transmission channels N - 1 <= M <= 500000
	int index;  //the index of teleportable planet
	int index1;  //the index of the one connected planet
	int index2;  //the index of the other connected planet
	scanf( "%d", &N);
	scanf( "%d", &K);
	scanf( "%d", &M);
	for ( int i = 0; i < K; i++) {

		scanf( "%d", &index);
		scanf( "%d", &B[index - 1]);

	}

	for ( int i = 0; i < M; i++) {

		scanf( "%d", &index1);	  
		scanf( "%d", &index2);	  
		scanf( "%d", &A[index1 - 1][index2 - 1]);
		A[index2 - 1][index1 - 1] = A[index1 - 1][index2 - 1];    

	}

	for ( int i = 0; i < N; i++) {

		printf("%d ", B[i]);

	}

	printf("\n");
	printf("\n");

	for ( int i = 0; i < N; i++) {

		for ( int j = 0; j < N; j++) {	  

			printf("%d ", A[i][j]);

		}  

		printf("\n");

	} 

}

