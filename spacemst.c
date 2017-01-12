/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : spacemst.c

 * Purpose : Educational

 * Creation Date : 11-01-2017

 * Last Modified : Πεμ 12 Ιαν 2017 10:10:55 μμ EET

 * Created By :  Stamatios Anoustis

 _._._._._._._._._._._._._._._._._._._._._.*/

/*------------------Includes and global definitions---------------------*/
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int B[10000];  //costs of teleport installation
int A[10000][10000]; //costs of direct transmission 
int EXIT_STATUS = 0;

/*-----------------Main Code-------------------------------------------*/
//A structure to represent an adjacency list node
struct AdjListNode {

  int dest;
  int weight;
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
struct AdjListNode* newAdjListNode(int dest, int weight) {

  struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
  newNode->dest = dest;
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;

}

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

}

//A utility function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {

  struct AdjListNode* newNode = newAdjListNode(dest, weight);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  //The symmetric work must be done for undirected graph
  newNode = newAdjListNode(src, weight);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;

}

//structure to represent a min heap node
struct MinHeapNode {

  int vertex;
  int key;

};

//structure to represent a min heap
struct MinHeap {

  int capacity;
  int size;
  int *position;
  struct MinHeapNode** array;

};

//utility function to create a min heap node
struct MinHeapNode* newMinHeapNode(int vertex, int key) {

  struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
  minHeapNode->vertex = vertex;
  minHeapNode->key = key;
  return minHeapNode;

}  

//A utillity function  to create a min heap
struct MinHeap* newMinHeap(int capacity) {

  struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
  minHeap->capacity = capacity;
  minHeap->size = 0;
  minHeap->position = (int*) malloc(capacity*sizeof(int));
  minHeap->array = (struct MinHeapNode**) malloc(capacity*sizeof(struct MinHeapNode*));
  return minHeap;

}

//A utillity function to swap min heap nodes 
void swapMinHeapNode(struct MinHeapNode** node1, struct MinHeapNode** node2) {

  struct MinHeapNode* temp = *node1;
  *node1 = *node2;
  *node2 = temp;

}  

//A utillity function to heapify at a given index
void minHeapify(struct MinHeap* minHeap,int index) {

  int smallest = index;
  int left = 2*index + 1; 
  int right = 2*index + 2;
  if ((left < minHeap->size) && (minHeap->array[left]->key < minHeap->array[smallest]->key)) {

    smallest = left;

  } 
  
  if ((right < minHeap->size) && (minHeap->array[right]->key < minHeap->array[smallest]->key)) {

    smallest = right;

  } 

  if (smallest != index) {

    //The nodes to be swapped in min heap
    struct MinHeapNode* smallestNode = minHeap->array[smallest];
    struct MinHeapNode* indexNode = minHeap->array[index];
    //Swap positions
    minHeap->position[smallestNode->vertex] = index;
    minHeap->position[indexNode->vertex] = smallest;
    //Swap min heap nodes
    swapMinHeapNode(&minHeap->array[smallest] , &minHeap->array[index] );
    //Swap rest nodes
    minHeapify(minHeap, smallest);

  }

}  

// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap) {

  return minHeap->size == 0;
     
}

// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {

  if (isEmpty(minHeap)) {

    return NULL;

  }    
  
  // The root node is the minimum I need to extract
  struct MinHeapNode* root = minHeap->array[0];
  // Replace root node with last node so as to remain a heap
  struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
  minHeap->array[0] = lastNode;                                    
  // Update position of last node
  minHeap->position[root->vertex] = minHeap->size-1;
  minHeap->position[lastNode->vertex] = 0;                                                 
  //Reduce heap size and heapify root
  minHeap->size--;
  minHeapify(minHeap, 0);                                                              
  return root;
                                        
}

//Standard function to decrease key of a given vertex
void decreaseKey(struct MinHeap* minHeap, int vertex, int key) {

  //Get index of vertex in heap array
  int index = minHeap->position[vertex];
  //Get the node and update its key value
  minHeap->array[index]->key = key;
  //Up Heap while not heapified
  while(index && (minHeap->array[index]->key < minHeap->array[(index - 1) / 2]->key)) {

    // Swap this node with its parent
    minHeap->position[minHeap->array[index]->vertex] = (index-1)/2;
    minHeap->position[minHeap->array[(index-1)/2]->vertex] = index;
    swapMinHeapNode(&minHeap->array[index],  &minHeap->array[(index - 1) / 2]);
    //move to parent index
    index = (index - 1)/2;
  
  }

}

// A utility function to check if a given vertex  is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int vertex) {
  
  if (minHeap->position[vertex] < minHeap->size) {

    return true;

  }
  
  return false;

}

//A utility function used to compute the cost of the 
//constructed MST
int cost(struct Graph* graph,int parent[]) {
  
  int sum = 0;	
  int V = graph->V;	
  for (int u = 1; u < V; u++) {
  
    int v = parent[u];
    struct AdjListNode* adjListNode = graph->array[u].head;
    while (v != adjListNode->dest) {

      adjListNode = adjListNode->next;
    }
    
    sum = sum + adjListNode->weight;

  }

  return sum;

} 

// A utility function used to print the constructed MST
/*void printArr(int arr[], int n) {
 
  for (int i = 1; i < n; ++i) {

  printf("%d - %d\n", arr[i], i);

  }

}*/
    	  

int MST_PRIM(struct Graph* graph) {

  int V = graph->V;  // Get the number of vertices in graph
  int parent[V];  // Array to store constructed MST
  int key[V];  // Key values used to pick minimum weight edge in cut
  //Min heap represents set E
  struct MinHeap* minHeap = newMinHeap(V);
  //Initiallise min heap with all vertices with inf key except first vertex
  for (int v = 1; v < V; v++) {

    parent[v] = -1;
    key[v] = INT_MAX;
    minHeap->array[v] = newMinHeapNode(v, key[v]);
    minHeap->position[v] = v;

  }

  //Set key of first vertex zero
  parent[0] = -1;
  key[0] = 0;
  minHeap->array[0] = newMinHeapNode(0, key[0]);
  minHeap->position[0] = 0;
  //Initialise size of minHeap to V
  minHeap->size = V;
  //Min heap contains all nodes not yet included in MST
  while (!isEmpty(minHeap)) {

    //Extract light weight edge crossing the cut
    struct MinHeapNode* minHeapNode = extractMin(minHeap); //get the next u
    int u = minHeapNode->vertex;  //Store the extracted vertex
    //Traverse all adjacent nodes v of u end update their key values
    struct AdjListNode* adjListNode = graph->array[u].head;
    while (adjListNode != NULL) {

      int v = adjListNode->dest;
      // If v is not yet included in MST and weight of u-v is
      // less than key value of v, then update key value and
      // parent of v (v in Heap and w(u,v) < key[v] )
      if ( isInMinHeap(minHeap, v) && (adjListNode->weight < key[v]) ) {

        key[v] = adjListNode->weight;
	parent[v] = u;
        decreaseKey(minHeap, v, key[v]);

      }

      //Get the next v
      adjListNode = adjListNode->next;

    }

  }

 // printArr(parent, V);
 return cost(graph, parent);   
}  

int main (int argc, char** argv) {

  int N;  //number of planets;suppose 2 <= N <= 10000
  int K;  //number of teportable planets 0 <= K <= N
  int M;  //number of transmission channels N - 1 <= M <= 500000
  int index;  //the index of teleportable planet
  int index1;  //the index of the one connected planet
  int index2;  //the index of the other connected planet
  int weight;
  scanf( "%d", &N);
  scanf( "%d", &K);
  scanf( "%d", &M);
  struct Graph* telnet = newGraph(N + 1);
  for ( int i = 0; i < K; i++) {

    scanf( "%d", &index);
    scanf( "%d", &weight);
    addEdge(telnet, N, index - 1, weight);

  }

  struct Graph* net = newGraph(N);
  for ( int i = 0; i < M; i++) {

    scanf( "%d", &index1);	  
    scanf( "%d", &index2);	  
    scanf( "%d", &weight);
    addEdge(net, index1 - 1, index2 - 1, weight);
    addEdge(telnet, index1 - 1, index2 -1, weight);    

  }

  if (MST_PRIM(net) < MST_PRIM(telnet)){

    printf("%d\n", MST_PRIM(net));
  
  } else {

  printf("%d\n", MST_PRIM(telnet));

  }

  return 0;

}

