#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;
#define nl cout<<"\n";
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define sign(x) ((x>0)?1:((x<0)?-1:0))

extern string str; // to hold the node number to print on nodes
extern GLvoid *font_style;
extern GLubyte fillCol[3]; //interior color of node (white)
extern GLubyte borderCol[3]; // border color of node (black)
extern GLubyte fillColt[3];
extern GLubyte strcol[3]; // string color of node number (red)

void handleResize(int , int );
void drawCircle(int ,pair <int , int>);
void drawEdge(pair<int ,int> , pair<int, int> );
void drawEdge(pair<int ,int> , pair<int, int> ,int );
void drawstr(GLuint , GLuint , const char* , int );
void setPixel(GLint , GLint );
void setPixel(GLint , GLint ,int );

