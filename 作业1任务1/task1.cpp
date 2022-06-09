#include"GL/glut.h"
#include"iostream"
#include"math.h"
#include"stdlib.h"
using namespace std;

GLfloat pointsize = 1.0f;//设置像素点大小
double pi = acos(-1.0);//定义pi的大小
float RGB[8][3] = //定义颜色数组
{
	{0.5,0.5,0.5},//灰色0-45度
	{0,0,1},//蓝色45-90度
	{0,0.5,0},//绿色90-135度
	{0,1,1},//淡蓝135-180度
	{1,0,0},//红色180-225度
	{1,0,1},//粉色225-270度
	{1,1,0},//黄色270-315度
	{1,1,1}//白色315-360度
};

void drawOneLine(GLint x1, GLint y1, GLint x2, GLint y2)//整数Bresenham算法
{
	int x = x1;//初始x坐标
	int y = y1;//初始y坐标
	int dx = abs(x1 - x2);//起始横坐标长度
	int dy = abs(y1 - y2);//起始纵坐标长度
	int sx = x2 - x1 > 0 ? 1 : -1;//判断x增量方向
	int sy = y2 - y1 > 0 ? 1 : -1;//判断y增量方向
	int flag = 0;
	int error = 2 * dy - dx;
	if (dy > dx)//要使得dx比dy长
	{
		swap(dx, dy);//否则，交换dx、dy
		flag = 1;
	}
	glPointSize(pointsize);//指定栅格化像素点的直径
	for (int i = 1; i < dx; i++)
	{
		glVertex2i(x, y);//指定绘制该点
		if (error >= 0)
		{
			if (flag == 1)
				x = x + sx;
			else
				y = y + sy;
			error -= 2 * dx;
		}
		if (flag == 1)
			y = y + sy;
		else
			x = x + sx;
		error += 2 * dy;
	}

}

void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);//把窗口清除为当前颜色
	glColor3f(1.0f, 1.0f, 1.0f);//设置颜色为白色
	glBegin(GL_POINTS);//开始绘图，对应glEnd()
	for (int n = 0; n < 360; n = n + 5) //每隔5度绘制一根直线
	{
		int i = n / 45;//分为8种颜色，每种45度
		glColor3f(RGB[i][0], RGB[i][1], RGB[i][2]);//从颜色数组中选取颜色
		drawOneLine(0, 0, (GLint)(10000 * cos(n / 180.0 * pi)), (GLint)(10000 * sin(n / 180.0 * pi)));
	}
	glEnd();//结束绘图，对应glBegin()
	glFlush();//强制刷新缓冲，保证绘图命执行
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);//初始化GLUT库
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//设置图形显示模式
	glutInitWindowPosition(100, 100);//设置在窗口的中心位置
	glutInitWindowSize(600, 600);//设置窗口大小
	glutCreateWindow("Bresenham直线光栅化算法"); //创建窗口
	glClearColor(0.0, 0.0, 0.0, 0.0);//清除颜色缓存
	glMatrixMode(GL_PROJECTION);//增加透视
	glLoadIdentity();//恢复初始坐标系
	gluOrtho2D(-10000.0, 10000.0, -10000.0, 10000.0);//设置显示区域
	glutDisplayFunc(display);//设置一个函数
	glutMainLoop();//进入GLUT事件处理循环
	system("pause");
	return 0;
}