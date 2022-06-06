#include<GL/glut.h>
#include<stdio.h>
typedef float point[3];
point v[4]={{0.0,0.0,1.0},{0.0,0.942809,-0.33333},{-0.816497,-0.471405,-
0.333333},{0.816497,-0.471405,-0.333333}};
int n;/*recursive steps*/
void triangle(point a,point b,point c)
{
glBegin(GL_TRIANGLES);
glNormal3fv(a);
glVertex3fv(a);
glVertex3fv(b);
glVertex3fv(c);
glEnd();
}
void tetrahedron(point a, point b, point c, point d)
{
glColor3f(1.0,1.0,0.0);
triangle(a,b,c);
glColor3f(0.0,1.0,1.0);
triangle(a,c,d);
glColor3f(1.0,0.0,1.0);
triangle(a,d,b);
glColor3f(0.0,0.0,0.0);
triangle(b,d,c);
}
void divide_tetrahedron(point a, point b, point c, point d, int n)
{
int j;
point v1,v2,v3,v4,v5,v6;/*variables to store six mid points*/
if(n>0)
{ /*the six mid-points of the six edges of a tetrahedron*/
for(j=0;j<3;j++)v1[j]=(a[j]+b[j])/2;/*mid point of edge ab*/
for(j=0;j<3;j++)v2[j]=(a[j]+c[j])/2;/*mid point of edge ac*/
for(j=0;j<3;j++)v3[j]=(a[j]+d[j])/2;/*mid point of edge ad*/
for(j=0;j<3;j++)v4[j]=(b[j]+c[j])/2;/*mid point of edge bc*/
for(j=0;j<3;j++)v5[j]=(c[j]+d[j])/2;/*mid point of edge cd*/
for(j=0;j<3;j++)v6[j]=(b[j]+d[j])/2;/*mid point of edge bd*/
divide_tetrahedron(a, v1,v2,v3,n-1);/*a tetrahedron formed from vertices a,mid point 
of ab,ac,ad edge*/
divide_tetrahedron( v1,b,v4,v6,n-1);/*a tetrahedron formed from vertices b,mid point 
of ab,bc,bd edge*/
divide_tetrahedron( v2,v4,c,v5,n-1);/*a tetrahedron formed from vertices c,mid point 
of ac,bc,cd edge*/
divide_tetrahedron( v3,v6,v5,d,n-1);/*a tetrahedron formed from vertices d,mid point 
of ad,cd,bd edge*/
}
else
tetrahedron(a,b,c,d);/*drawing the tetrahedrons*/
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glEnable(GL_DEPTH_TEST);
divide_tetrahedron(v[0],v[1],v[2],v[3],n);
glFlush();
}
void myreshape(int w,int h)
{
glViewport(0,0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if(w<=h)
{
glOrtho
(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);}
else
glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
glMatrixMode(GL_MODELVIEW);
glutPostRedisplay();
}
void main(int argc,char **argv)
{
printf("Enter the number of sub-divisons:\n");
scanf("%d",&n);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
glutInitWindowPosition(0,0);
glutInitWindowSize(500,500);
glutCreateWindow("3D sierpinski");
glutReshapeFunc(myreshape);
glutDisplayFunc(display);
glClearColor(0.0,0.0,0.0,1.0);
glutMainLoop();
}

