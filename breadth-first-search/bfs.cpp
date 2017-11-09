#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include <GL/glut.h>
#include "../src/graph-graphics.h"

int *color; // holds the colors of nodes
map<int, vector<int> > adjlist; // maps node number to a vector containing node numbers of neighbours
int vt=0; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes
vector <int> final;

void display(); // prototype


void BFS(int src) // bfs algo
{
	vector<int> neighbours = adjlist[src];
	cout<<"exploring neighbors of "<<src; nl
	queue<int> q;
	usleep(1200000);
	for( int i : neighbours)
	{
		if(color[i] == 0)
		{
			color[i]=1;
			cout<<"greying node "<<i; nl
			final.push_back(i);
			display();
			usleep(1200000);
			q.push(i);
		}
	}
	while(!q.empty())
	{
		BFS(q.front());
		q.pop();		
	}
	cout<<"blacking. completely visited "<<src; nl
	color[src]= 2;
	display();
	usleep(1200000);
	if(final.size()==n&&src==0)
	{
		cout<<"\n";
        for(int i=0;i<n;i++)
        {
            cout<<final[i]<<" ";
        }
        cout<<endl;
	}
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
            usleep(600000);
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)   
    {
        cout<<"\nRunning BFS\n";
        for(int i=0;i<n;i++)
		{
			if(color[i]==0)
			{
				cout<<"greying node "<<i; nl
				color[i]=1;
				final.push_back(i);
				display();
				BFS(i);
				usleep(600000);
			}
		}
    }
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<vt;i++)
    {
        str=to_string(i);
        drawCircle(color[i],coordinates[i]);
    }
    if(vt==n)
    {
        for(int i=0;i<n;i++)
        {
        	vector<int> neighbours = adjlist[i];
        	for( int j : neighbours)
        	{
        		drawEdge(coordinates[i],coordinates[j]);
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
	coordinates= new pair< int ,int > [n];
	memset(color, 0 ,n*sizeof(int));
	cout<<"Enter the number of edges in the graph"; nl
	cin>>e;
	cout<<"Enter the edges of the graph (u --> v) pairs"; nl
	size_t u,v;
	for(int i=0;i<e;i++)
	{
		cin>>u>>v;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
	}
	/**/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Breadth First Search");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
