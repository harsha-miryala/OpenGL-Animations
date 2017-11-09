#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include <GL/glut.h>
#include "../src/graph-graphics.h"
using namespace std;

int *color; // holds the colors of nodes
int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes
void display(); // prototype
bool done=false;
set <pair<int,int>> final;

// a structure to represent a weighted edge in graph
struct Edge
{
    int src, dest, weight;
};

// a structure to represent a connected, undirected
// and weighted graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges. 
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    struct Edge* edge;
};
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
 
    graph->edge = new Edge[E];
 
    return graph;
}
 
struct Graph* graph;

// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};
 
// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i 
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high 
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and 
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}
 
// The main function to construct MST using Kruskal's algorithm
void Kruskal(struct Graph* graph)
{
    int V = graph->V;
    struct Edge result[V];  // Tnis will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges
 
    // Step 1:  Sort all the edges in non-decreasing 
    // order of their weight. If we are not allowed to 
    // change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
 
    // Allocate memory for creating V ssubsets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
        // Step 2: Pick the smallest edge. And increment 
        // the index for next iteration
        struct Edge next_edge = graph->edge[i++];
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
 
        // If including this edge does't cause cycle,
        // include it in result and increment the index 
        // of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            color[next_edge.src]=1;
            color[next_edge.dest]=1;
            final.insert(make_pair(next_edge.src,next_edge.dest));
            display();
            usleep(1200000);
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 	
 	for(int i=0;i<n;i++)
 	{
 		color[i]=2;
 	}
 	display();
    // print the contents of result[] to display the built MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
                                                 result[i].weight);
    return;
}

void mouse(int button, int state, int x, int y)  
{  
    if(vt<n)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)   
        { 
            coordinates[vt].first = x;
            coordinates[vt].second = (700-y);
            cout<< coordinates[vt].first <<'\t'<<  coordinates[vt].second <<'\n';
            vt++;
            display();
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)   
    {
        //for(int i=0;i<n;i++)
		if(color[0]==0&&done==false)
		{
				cout<<"\nRunning Krushkal\n";
				done = true;
				Kruskal(graph);
		}
    }
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(!done)
    {
	    for(int i=0;i<vt;i++)
	    {
	        str=to_string(i);
	        drawCircle(color[i],coordinates[i]);
	    }
	    if(vt==n)
	    {
	        for(int i=0;i<e;i++)
	        {
	        	str=to_string(graph->edge[i].weight);
	        	drawEdge(coordinates[graph->edge[i].src],coordinates[graph->edge[i].dest],0);
	        }
	    }
	}
	else //krushkal is done. now display the result
	{
		for(int i=0;i<vt;i++)
	    {
	        str=to_string(i);
	        drawCircle(color[i],coordinates[i]);
	    }
	    for(int i=0;i<e;i++)
	    {
	        str=to_string(graph->edge[i].weight);
	        if(final.find(make_pair(graph->edge[i].src,graph->edge[i].dest))!=final.end()||
	        		final.find(make_pair(graph->edge[i].dest,graph->edge[i].src))!=final.end())
	        {
	        	drawEdge(coordinates[graph->edge[i].src],coordinates[graph->edge[i].dest],1);
	        }
	        else
	        {
	        	drawEdge(coordinates[graph->edge[i].src],coordinates[graph->edge[i].dest],0);
	        }
	    }
	}
    glColor3f(1.0f, 1.0f, 1.0f);
    str = "-----------------------------------------------------------";
    drawstr(10,110, str.c_str(), str.length());
    str = "Dijkstra-Shortest Path Algorithm";
    drawstr(10,90, str.c_str(), str.length());
    str = "White - Initial color of the node";
    drawstr(10,70, str.c_str(), str.length());
    str = "Green - The node is being processed";
    drawstr(10,50, str.c_str(), str.length());
    str = "Red - All of its neighbours are reached or the final processing is done";
    drawstr(10,30, str.c_str(), str.length());
    str = "-----------------------------------------------------------";
    drawstr(10,10, str.c_str(), str.length());
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
	cout<<"Enter the number of nodes in the graph"; nl
	cin>>n;
	color =  new int[n];
	for(int i=0;i<n;i++)
	{
		color[i]=0;
	}
	coordinates= new pair< int ,int > [n];
	cout<<"Enter the number of edges in the graph"; nl
	cin>>e;
	cout<<"Enter the edges of the graph (u --> v) pairs and their weight w"; nl
	graph = createGraph(n, e);
	size_t u,v,w;
	for(int i=0;i<e;i++)
	{
		cin>>u>>v>>w;
		graph->edge[i].src = u;
    	graph->edge[i].dest = v;
    	graph->edge[i].weight = w;
	}
	/**/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Krushkal");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
