#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include <GL/glut.h>
#include "../src/graph-graphics.h"
using namespace std;

int *color; // holds the colors of nodes
vector <int>  graph[100000];
int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes
void display(); // prototype
vector<int> dist;
bool done=false; //to display the result if the algo is done running
set <pair<int,int>> final;

// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// Function to print shortest path from source to j
// using parent array
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j]==-1)
        return;
 	final.insert(make_pair(min(j,parent[j]),max(j,parent[j])));
 	color[parent[j]]=2;
 	display();
    usleep(1200000);
    printPath(parent, parent[j]);
 
    printf("%d ", j);
}
 
// A utility function to print the constructed distance
// array
int printSolution(int n, int parent[])
{
    int src = 0;
    color[src]=2;
    display();
    usleep(1200000);
    //printf("Vertex\t  Distance\tPath");
    for (int i = 1; i < n; i++)
    {
    	color[i]=2;
    	display();
    	usleep(1200000);
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
    cout<<endl;
}

// Prints shortest paths from src to all other vertices
void dijkstra(int src)
{
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[n];
    // Parent array to store shortest path tree
 	int parent[n];   
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < n; i++)
    {
        parent[0] = -1;
        dist.push_back(INT_MAX);
        sptSet[i] = false;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < n-1; count++)
    {
        int u = minDistance(sptSet); 
        // Mark the picked vertex as processed
        sptSet[u] = true;
        color[u] = 1;
        display();
        usleep(1200000);
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < n; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
 	done = true;
    // print the constructed distance array
    printSolution(n, parent);
    display();
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
		if(color[0]==0&&done==false)
		{
				cout<<"\nRunning Dijkstra\n";
				display();
				dijkstra(0);
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
	        for(int i=0;i<n;i++)
	        {
	        	for( int j=0;j<n;j++)
	        	{
	        		if(graph[i][j])
	        		{
	        			str=to_string(graph[i][j]);
	        			drawEdge(coordinates[i],coordinates[j],0);
	        		}
	        	}
	        }
	    }
	}
	else //dijkstra is done. now display the result
	{
		for(int i=0;i<vt;i++)
	    {
	        str=to_string(i);
	        drawCircle(color[i],coordinates[i]);
	    }
	    for(int i=0;i<n;i++)
	    {
	        for( int j=0;j<n;j++)
	        {
	        	if(graph[i][j])
	        	{
	        		str=to_string(graph[i][j]);
	        		if(final.find(make_pair(i,j))!=final.end()||final.find(make_pair(j,i))!=final.end())
	        		{
	        			drawEdge(coordinates[i],coordinates[j],1);
	        			
	        		}
	        		else
	        		{
	        			drawEdge(coordinates[i],coordinates[j],0);
	        		}
	        	}
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
	size_t u,v,w;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			graph[i].push_back(0);
	}
	for(int i=0;i<e;i++)
	{
		cin>>u>>v>>w;
		//adjlist[u].push_back(make_pair(v,w));
		//adjlist[v].push_back(make_pair(u,w));
		graph[u][v]=w;
		graph[v][u]=w;
	}
	/**/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dijkstra");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
