#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include <GL/glut.h>

using namespace std;

int cost[1000][1000];
int n,Count=0;
int visited[1000];

class Points
{
    public:
        float x;
        float y;
    void setPoints(float xa , float ya)
    {
        x=xa;
        y=ya;
    }
};

Points XY[10];

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);
    gluOrtho2D(0,500,0,500);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10);
    glEnable(GL_POINT_SMOOTH);
    glColor3f(1.0,1.0,1.0);
    
    glBegin(GL_POINTS);
    for(int i=0;i<n;i++)
    {
        if(visited[i]==0)   
        glColor3f(1.0,1.0,1.0);
        else                
        glColor3f(1.0,0.0,0.0);
        glVertex2f(XY[i].x,XY[i].y);
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
             if(cost[i][j]!=0)
            {
                glVertex2f(XY[i].x,XY[i].y);                    
                glVertex2f(XY[j].x,XY[j].y);
            }
        }
    }
    glEnd();

    glutSwapBuffers();
}


void mouse(int btn, int state, int x , int y)
{
    if(Count<n && state==GLUT_DOWN && btn==GLUT_LEFT_BUTTON)
    {
        XY[Count].setPoints(x,500-y);
        Count++;
        display();
    }

}

void DFS(int i)
{
    int j;
    printf("\n%d",i);
    visited[i]=1;

    display();
    usleep(600000);

    for(j=0;j<n;j++)
    {
       if(!visited[j]&&cost[i][j]!=0)
       {
            DFS(j);
       }
    }
}

void keyPressed(unsigned char key, int x , int y)
{
    DFS(0);
}


int main(int argc,char** argv){
    printf("\n Enter the no: of vertices : ");
    cin>>n;
    int e;
    printf("\n Enter the no.of edges : ");
    cin>>e;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(j!=i)
            cost[i][j]=0;
            else
            cost[i][j]=1;
        }
    }

    printf("\n Enter the edges : format x---y \n");

    for(int i=0;i<e;i++)
    {
        int p,q;
        cin>>p>>q;
        cost[p][q]=1;
        cost[q][p]=1;
    }

    for(int i=0;i<n;i++)
    {
        visited[i]=0;
    }

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(50,50);
    glutCreateWindow("DFS");

    init();

    //callback functions
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;

}