#include <bits/stdc++.h>
#include "graph-graphics.h"
using namespace std;

string str; // to hold the node number to print on nodes
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
GLubyte strcol[3]={230,100,80}; // string color of node number (red)

void drawstr(GLuint x, GLuint y, const char* format, int length)// draw string on screen
{
    glRasterPos2i(x, y);  
    for(int i=0; i<length; ++i)
    {
        glutBitmapCharacter(font_style, *(format+i) );
    }
}

void setPixel(GLint x, GLint y) // set pixel as black
{
    glBegin(GL_POINTS); 
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize (30.0);
    glVertex2i(x,y);
    glEnd();
}

void setPixel(GLint x, GLint y,int clr) // set pixel as black
{
    glBegin(GL_POINTS); 
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize (30.0);
    glVertex2i(x,y);
    glEnd();
}

void drawCircle(int color,pair <int , int> center) // circle drawing algo
{
  int i;
  int x=center.first,y=center.second;
  GLfloat radius=16;
  GLfloat PI = 3.14f;
  int triangleAmount = 1000; 
  GLfloat twicePi = 2.0f * PI;

  glEnable(GL_LINE_SMOOTH);
  glLineWidth(2.0);

  glBegin(GL_LINES);
  if(color==0)
  glColor4f(1.0, 1.0, 1.0, 1.0);
  else if(color==1)
  glColor4f(0.0, 128/255.0, 0.0, 0.5);
  else
  glColor4f(128/255.0, 0.0, 0.0, 1.0);
  for(i = 0; i <= triangleAmount; i++)
  {
    glVertex2f( x, y);
    glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
  }
  glEnd();
  drawstr(x-32,y, str.c_str(), str.length());  
}

void drawEdge(pair<int ,int> p, pair<int, int> q) // line drawing algo
{
    int x1,x2,y1,y2;
    x1= p.first;
    x2= q.first;
    y1= p.second;
    y2= q.second;

    int dx, dy, x, y, d, s1, s2, swap=0, temp;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    s1 = sign(x2-x1);
    s2 = sign(y2-y1);

    if(dy > dx)
    {
        temp = dx;
        dx = dy; 
        dy = temp;
        swap = 1;
    }

    d = 2 * dy - dx;
    x = x1;
    y = y1;

    int i;

    for(i = 1; i < dx; i++)
    {
        setPixel(x,y);

        while(d>=0)
        {
            d=d-2*dx;
            if(swap)
                x+=s1;
            else
                y+=s2;
        }

        d=d+2*dy;
        if(swap)
            y+=s2;
        else
            x+=s1;
    }
}
void drawEdge(pair<int ,int> p, pair<int, int> q,int clr) // line drawing algo
{
    int x1,x2,y1,y2;
    x1= p.first;
    x2= q.first;
    y1= p.second;
    y2= q.second;

    int dx, dy, x, y, d, s1, s2, swap=0, temp;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    s1 = sign(x2-x1);
    s2 = sign(y2-y1);

    if(dy > dx)
    {
        temp = dx;
        dx = dy; 
        dy = temp;
        swap = 1;
    }

    d = 2 * dy - dx;
    x = x1;
    y = y1;

    int i;

    for(i = 1; i < dx; i++)
    {
        if(clr==0)     
        setPixel(x,y);
        else
        setPixel(x,y,1);
        while(d>=0)
        {
            d=d-2*dx;
            if(swap)
                x+=s1;
            else
                y+=s2;
        }

        d=d+2*dy;
        if(swap)
            y+=s2;
        else
            x+=s1;
    }
    drawstr((x1+x2)/2-5,(y1+y2)/2, str.c_str(), str.length());
}
void handleResize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);   // Transformations being applied to Projection Matrix
    glLoadIdentity();   // Always call after changing matrix
    glViewport(0,0,w,h);
    gluOrtho2D(0.0,1000.0,0.0,700.0); // Here object is being moved along with window, wx & hy window size. Here clipping range is zNear=1,zFar=-200
    glMatrixMode(GL_MODELVIEW); // Transformations on ModelView Matrix(default)
}