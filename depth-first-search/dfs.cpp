#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include <GL/glut.h>
#include "../src/graph-graphics.h"
using namespace std;


int *color; // holds the colors of nodes
map<int, vector<int> > adjlist; // maps node number to a vector containing node numbers of neighbours
int vt; // no of vertices drawn
size_t n=0 , e=0; // no of nodes and edges
pair< int , int> *coordinates; // array of coordinates of nodes
vector <int> final;

/*string str; // to hold the node number to print on nodes
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
GLubyte fillCol[3] = {255,255,255}; //interior color of node (white)
GLubyte borderCol[3] = {0,0,0}; // border color of node (black)
GLubyte fillColt[3];
GLubyte strcol[3]={230,100,80}; // string color of node number (red)*/
void display(); // prototype


void DFS(int src) // dfs algo
{
    cout<<"greying node "<<src; nl
    color[src]= 1;
    display();
    usleep(1200000);
    final.push_back(src);
    vector<int> neighbours = adjlist[src];
    cout<<"exploring neighbors of "<<src; nl
    usleep(1200000);
    stack<int> s;
    for( int i : neighbours)
    {
        if(color[i] == 0)
            s.push(i);
    }
    while(!s.empty())
    {
        DFS(s.top());
        s.pop();        
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
            coordinates[vt].second = (800-y);
            cout<<x<<'\t'<<1000-y<<'\n';
            vt++;
            display();
            usleep(600000);
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)   
    {
        cout<<"\nRunning DFS\n";
        for(int i=0;i<n;i++)
        {
            if(color[i]==0)
            {
                usleep(600000);
                display();
                DFS(i);
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
    str = "hello";
    drawstr(100,100, str.c_str(), str.length());
    
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    vt=0;
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
    glutInitWindowSize(1300, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Depth First Search");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(handleResize);
    glutMainLoop();
    return 0;
}
