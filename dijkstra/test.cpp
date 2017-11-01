#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include <GL/glut.h>
#include "../src/graph-graphics.h"
using namespace std;

int *color; // holds the colors of nodes
int *ecolor; //holds the colors of edges for final shortest path display
map< int, vector< pair<int, int > > > adjlist; // maps node number to a vector containing node numbers of neighbours
int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes
void display(); // prototype
vector<int> dist;
bool done=false; //to display the result if the algo is done running
typedef pair<int, int> iPair;

// Prints shortest paths from src to all other vertices
void dijkstra(int src)
{
    // Create a priority queue to store vertices that are being preprocessed. 
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
 
    // Create a vector for distances and initialize all distances as infinite (INF)
    for(int i=0;i<n;i++)
    {
    	dist.push_back(INT_MAX);
    }
 
    // Insert source itself in priority queue and initialize its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;
 
    /* Looping till priority queue becomes empty (or all distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance vertex, extract it from priority queue.
        int u = pq.top().second;
        pq.pop();
 
        // 'i' is used to get all adjacent vertices of a vertex
        vector< pair<int, int> >::iterator i;
        for (i = adjlist[u].begin(); i != adjlist[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent of u.
            int v = (*i).first;
            int weight = (*i).second;
 
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
 
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
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
		if(color[i]==0&&done=false)
		{
				cout<<"\nRunning Dijkstra\n";
				//cout<<"greying node "<<i; nl
				//color[i]=1;
				display();
				dijkstra(i);
		}
		done=true;
    }
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //if(!done)
    //{
	    for(int i=0;i<vt;i++)
	    {
	        str=to_string(i);
	        drawCircle(color[i],coordinates[i]);
	    }
	    if(vt==n)
	    {
	        for(int i=0;i<n;i++)
	        {
	        	vector< pair <int ,int > > neighbours = adjlist[i];
	        	for( pair<int ,int > j : neighbours)
	        	{
	        		drawEdge(coordinates[i],coordinates[j.first]);
	        	}
	        }
	    }
	//}
	/*
	else //dijkstra is done. now display the result
	{
		cout<<"\n Done. Displaying result.\n";
		for(auto a : shortest_path)
		{
			color[a] = 1;
		}
		for(int i=0;i<vt;i++)
	    {
	        str=to_string(::distance[i]);
	        drawCircle(color[i],coordinates[i]);
	    }
	    if(vt==n)
	    {
	        for(int i=0;i<n;i++)
	        {
	        	vector< pair <int ,int > > neighbours = adjlist[i];
	        	for( pair<int ,int > j : neighbours)
	        	{
	        		drawEdge(coordinates[i],coordinates[j.first]);
	        	}
	        }
	    }	
	}*/
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
	ecolor = new int[n];
	cout<<"Enter the edges of the graph (u --> v) pairs and their weight w"; nl
	size_t u,v,w;
	for(int i=0;i<e;i++)
	{
		cin>>u>>v>>w;
		adjlist[u].push_back(make_pair(v,w));
		adjlist[v].push_back(make_pair(u,w));
	}
	/**/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dijkstra");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
