#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define BALL_MAX 3
#define BLOCK_MAX 33 
#define F 60 //fps
#define force 10

struct vector2{
    float x;
    float y;
    };
struct obj{
    float rad; //半径
    float mas; //質量
    float els; //反発係数
    float frc; //摩擦
    float rot; //角度
    float dps; //回転速度
    struct vector2 pos;
    struct vector2 vel;
    struct vector2 acc;
    float color[3];
};
struct blo{
    struct vector2 b_pos;
    struct vector2 size; 
    float b_color[3];
};
int flag[BALL_MAX*(BALL_MAX-1)/2]={0}; 
float circle[36][2];
float p = 2.0;
float dist_m;
float m_sevx=0.0,b_sevx=0.0,m_sevy=0.0,b_sevy=0.0;
struct obj ball[BALL_MAX]={
    // rad mas els  frc   rot dps pos_x  pos_y vel_x vel_y acc_x acc_y red green blue
       150,50,1.0, 0.995, 0,  0,  -700,  60,   40,   0,    0,    0,    1,  0,    0,
       30, 10 ,0.9, 0.01, 0,  0,  0,    -300,  0,  0,    0,    0,    0,  1,    0,
       30, 10, 1.0, 0.01, 0,  0,  0,    300,   0,    0,    0,    0,    0,  0,    1,
};
struct blo block[BLOCK_MAX]={
   // postion_x postion_y size_x size_y red green blue
      950,     550,      50,    100,  0.8, 0.3, 0.3,
      950,     450,      50,    100,  0.8, 0.3, 0.3,
      950,     350,      50,    100,  0.8, 0.3, 0.3,
      950,     250,      50,    100,  0.8, 0.3, 0.3,
      950,     150,      50,    100,  0.8, 0.3, 0.3,
      950,     50,       50,    100,  0.8, 0.3, 0.3,
      950,     -50,      50,    100,  0.8, 0.3, 0.3,
      950,    -150,      50,    100,  0.8, 0.3, 0.3,
      950,    -250,      50,    100,  0.8, 0.3, 0.3,
      950,    -350,      50,    100,  0.8, 0.3, 0.3,
      950,    -450,      50,    100,  0.8, 0.3, 0.3,//11low 1line 
      900,     550,      50,    100,  0.8, 0.3, 0.3,
      900,     450,      50,    100,  0.8, 0.3, 0.3,
      900,     350,      50,    100,  0.8, 0.3, 0.3,
      900,     250,      50,    100,  0.8, 0.3, 0.3,
      900,     150,      50,    100,  0.8, 0.3, 0.3,
      900,     50,       50,    100,  0.8, 0.3, 0.3,
      900,     -50,      50,    100,  0.8, 0.3, 0.3,
      900,    -150,      50,    100,  0.8, 0.3, 0.3,
      900,    -250,      50,    100,  0.8, 0.3, 0.3,
      900,    -350,      50,    100,  0.8, 0.3, 0.3,
      900,    -450,      50,    100,  0.8, 0.3, 0.3,//11low 2line
      850,     550,      50,    100,  0.8, 0.3, 0.3,
      850,     450,      50,    100,  0.8, 0.3, 0.3,
      850,     350,      50,    100,  0.8, 0.3, 0.3,
      850,     250,      50,    100,  0.8, 0.3, 0.3,
      850,     150,      50,    100,  0.8, 0.3, 0.3,
      850,     50,       50,    100,  0.8, 0.3, 0.3,
      850,     -50,      50,    100,  0.8, 0.3, 0.3,
      850,    -150,      50,    100,  0.8, 0.3, 0.3,
      850,    -250,      50,    100,  0.8, 0.3, 0.3,
      850,    -350,      50,    100,  0.8, 0.3, 0.3,
      850,    -450,      50,    100,  0.8, 0.3, 0.3,//11low 3line 
      
};
void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1100,600);
    glVertex2f(-1100,600);
    glVertex2f(-1100,-600);
    glVertex2f(1100,-600);
    glEnd();
    for(int i=0;i<BLOCK_MAX;i++){ 
    glColor3f(block[i].b_color[0],block[i].b_color[1],block[i].b_color[2]);
    glBegin(GL_LINE_LOOP);
    glVertex2f(block[i].b_pos.x,block[i].b_pos.y);
    glVertex2f(block[i].b_pos.x,block[i].b_pos.y-block[i].size.y);
    glVertex2f(block[i].b_pos.x+block[i].size.x,block[i].b_pos.y-block[i].size.y);
    glVertex2f(block[i].b_pos.x+block[i].size.x,block[i].b_pos.y);
    glEnd();
    }
    for(int i=0;i<BALL_MAX;i++){
        glPushMatrix();
        glTranslatef(ball[i].pos.x,ball[i].pos.y,0);
        glRotatef(ball[i].rot,0,0,1);
        glColor3f(ball[i].color[0],ball[i].color[1],ball[i].color[2]);
        glBegin(GL_LINE_LOOP);
         for(int j=0;j<36;j++)glVertex2f(ball[i].rad*circle[j][0],ball[i].rad*circle[j][1]);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(0,ball[i].rad);
        glVertex2f(0,-ball[i].rad);
        glVertex2f(ball[i].rad,0);
        glVertex2f(-ball[i].rad,0);
        glEnd();
        glPopMatrix();
        
}
glutSwapBuffers();
}
void simu(void){
    
    for(int i=0,count=0;i<BALL_MAX;i++){
        for(int j=i+1;j<BALL_MAX;j++,count++){ 
     dist_m=sqrt((ball[i].pos.x-ball[j].pos.x)*(ball[i].pos.x-ball[j].pos.x)+(ball[i].pos.y-ball[j].pos.y)*(ball[i].pos.y-ball[j].pos.y));
    if(dist_m<=ball[i].rad+ball[j].rad)if(flag[count]==0){
     m_sevx=(ball[i].mas*ball[i].vel.x+ball[j].mas*ball[j].vel.x-ball[j].mas*ball[i].els*(ball[i].vel.x-ball[j].vel.x))/(ball[i].mas+ball[j].mas);
     b_sevx=(ball[i].mas*ball[i].vel.x+ball[j].mas*ball[j].vel.x-ball[i].mas*ball[i].els*(ball[j].vel.x-ball[i].vel.x))/(ball[i].mas+ball[j].mas);
     m_sevy=(ball[i].mas*ball[i].vel.y+ball[j].mas*ball[j].vel.y-ball[j].mas*ball[i].els*(ball[i].vel.y-ball[j].vel.y))/(ball[i].mas+ball[j].mas);
     b_sevy=(ball[i].mas*ball[i].vel.y+ball[j].mas*ball[j].vel.y-ball[i].mas*ball[i].els*(ball[j].vel.y-ball[i].vel.y))/(ball[i].mas+ball[j].mas);
     ball[i].vel.x=m_sevx;
     ball[i].vel.y=m_sevy;
     ball[j].vel.x=b_sevx;
     ball[j].vel.y=b_sevy;
     flag[count]=1;
        }
    else flag[count]=0;
        }
   } 
    for(int i=0;i<BALL_MAX;i++){

//printf("%f\t%f\n%f\t%f\n\n",ball[0].vel.x,ball[1].vel.x,ball[0].vel.y,ball[1].vel.y);
    ball[i].vel.y+=ball[i].acc.y/F*p;
    ball[i].pos.y+=ball[i].vel.y/F*p;
    ball[i].vel.x+=ball[i].acc.x/F*p;
    ball[i].pos.x+=ball[i].vel.x/F*p;

    if(ball[i].pos.x>1100-ball[i].rad){
        ball[i].pos.x=1100-ball[i].rad;
        ball[i].vel.x=-1*ball[i].vel.x*ball[i].els;
        ball[i].acc.x=-1*ball[i].acc.x*ball[i].els;
    }
    if(ball[i].pos.x<-1100+ball[i].rad){
        ball[i].pos.x=-1100+ball[i].rad;
        ball[i].vel.x=-1*ball[i].vel.x*ball[i].els;
        ball[i].acc.x=-1*ball[i].acc.x*ball[i].els;
    }
    if(ball[i].pos.y>600-ball[i].rad){
        ball[i].pos.y=600-ball[i].rad;
        ball[i].vel.y=-1*ball[i].vel.y*ball[i].els;
        ball[i].acc.y=-1*ball[i].acc.y*ball[i].els;
    }
    if(ball[i].pos.y<-600+ball[i].rad){
        ball[i].pos.y=-600+ball[i].rad;
        ball[i].vel.y=-1*ball[i].vel.y*ball[i].els;
        ball[i].acc.y=-1*ball[i].acc.y*ball[i].els;
    }
    if(i!=0){
        for(int j=0;j<=BLOCK_MAX;j++){
    if(ball[i].pos.x+ball[i].rad>=block[j].b_pos.x&&ball[i].pos.y>=block[j].b_pos.y-block[j].size.y&&ball[i].pos.y<=block[j].b_pos.y){
        ball[i].vel.x*=-1;
        ball[i].vel.y*=1;
        block[j].b_pos.x+=1000;
    }
        }
    }
    for(int i=0;i<BALL_MAX;i++){
    if(i==0){
    ball[i].acc.x*=ball[i].frc;
    ball[i].acc.y*=ball[i].frc;
    ball[i].vel.x*=ball[i].frc;
    ball[i].vel.y*=ball[i].frc;
    }
    }
    glutPostRedisplay();
}
}
void resize(int w, int h) 
{
	glViewport(0, 0, w, h); //ウインドウ全体に表示
	glMatrixMode(GL_PROJECTION); //投影変換モードへ
	glLoadIdentity(); //投影変換の変換行列を単位行列で初期化
	glOrtho(-1200.0, 1200.0, -744.0, 744.0, 1.0, -1.0); //各軸-1.0～1.0で囲まれる立方体の範囲を並行投影
    glMatrixMode(GL_MODELVIEW); //視野変換・モデリング変換モードへ
	glLoadIdentity(); //視野変換・モデリング変換の変換行列を単位行列で初期化
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
        case '\033':exit(1);break;
        case 'a':if(ball[0].acc.x>=-60)ball[0].acc.x-=20;break;
        case 'd':if(ball[0].acc.x<=60)ball[0].acc.x+=20;break;
        case 'w':if(ball[0].acc.y<=60)ball[0].acc.y+=20;break;
        case 's':if(ball[0].acc.y>=-60)ball[0].acc.y-=20;break;
    }
glutPostRedisplay();
}
int main(int argc ,char *argv[]){
    for(float x=0;x<36;x+=1){
        circle[(int)x][0]=sin(x*M_PI/18);
        circle[(int)x][1]=cos(x*M_PI/18);
}
    glutInit(&argc, argv);
	glutInitWindowPosition(1000, 0); //ウインドウを表示する画面上の左上の位置
	glutInitWindowSize(900,600); //ウインドウ
	glutInitDisplayMode(GLUT_RGBA);
    glShadeModel(GL_FLAT);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize); //関数resizeをコールバックに設定
	glutKeyboardFunc(keyboard);
    glutIdleFunc(simu);
   	glClearColor(0.0, 0.0, 0.0, 0.0);
        glutMainLoop();
}
