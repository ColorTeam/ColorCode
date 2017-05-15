#include "gl_helper.h"
#include "utils.h"
#include "GameObject.h"

GLuint VBO;
GLuint EBO;
GLuint g_tex;
int m_t = 4;
int m_v = 12;
GLRTT rtt;
GLuint m_frameBuffer, m_colorBuffer;

int g_width, g_height;
char g_input_path[128] = "res/test.jpg";
char g_input_path1[128] = "res/test1.jpg";
char g_output_path[128] = "res/new.jpg";
GLenum image_type = GL_RGBA;
int image_channels = 4;

void *now_img = 0;

float vertices[20000] = {
	-1.0, 1.0, 0.0,
	1.0, 1.0, 0.0,
	-1.0, -1.0, 0.0,

	1.0, 1.0, 0.0,
	1.0, -1.0, 0.0,
	-1.0, -1.0, 0.0,

	0.0, 1.0, 0.1,
	1.0, 1.0, 0.1,
	0.0, 0.0, 0.1,

	1.0, 1.0, 0.1,
	1.0, 0.0, 0.1,
	0.0, 0.0, 0.1,

	0.0, 1.0,
	1.0, 1.0,
	0.0, 0.0,

	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,

	0.0, 1.0,
	1.0, 1.0,
	0.0, 0.0,

	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,

};

unsigned int ebo[30000] = {
	0, 1, 2,
	3, 4, 5,
	6, 7, 8,
	9, 10, 11,
};

/**
* 渲染回调函数
*/
void RenderScenceCB() {
	glClear(GL_COLOR_BUFFER_BIT);
	glActiveTexture(g_tex);
	glBindTexture(GL_TEXTURE_2D, g_tex);

	// 开启顶点属性
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// 绑定GL_ARRAY_BUFFER缓冲器

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*m_v * 5, vertices);
	// 告诉管线怎样解析bufer中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(m_v * 3 * sizeof(float)));
	
	// 开始绘制几何图形(绘制一个点)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 3 * m_t, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3*m_t);

	//  禁用顶点数据
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// 交换前后缓存
	glFlush();
	glutSwapBuffers();

	/*
	unsigned char* new_data = (unsigned char*)malloc(sizeof(unsigned char)*g_width*g_height*image_channels);
	rtt.GetColorData(new_data, image_type, GL_UNSIGNED_BYTE);
	stbi_write_png(g_output_path, g_width, g_height, image_channels, new_data, image_channels * sizeof(unsigned char)*g_width);
	*/
	//exit(0);
}

/**
* 创建顶点缓冲器
*/
static void CreateVertexBuffer() {
	// 创建缓冲器
	glGenBuffers(1, &VBO);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 绑定顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_v * 5, vertices, GL_DYNAMIC_DRAW);
}

static void CreateIndexBuffer() {
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_t * 3, ebo, GL_STATIC_DRAW);
}

static void CreateTexture(BigTex bigtex) {
	glGenTextures(1, &g_tex);
	glBindTexture(GL_TEXTURE_2D, g_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, image_type, bigtex.width, bigtex.height, 0, image_type, GL_UNSIGNED_BYTE, bigtex.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0u);
}

static void SpecialKeyboardCB(int Key, int x, int y)
{
	OnKeyboard(Key);
}

void glOnRender() {
	//-1.0, 1.0,
	//	1.0, 1.0,
	//	-1.0, -1.0,

	//	1.0, 1.0,
	//	1.0, -1.0,
	//	-1.0, -1.0,
	Vec2f tmp = player.getGLPosition();
	printf("tmp: %.2f %.2f\n", tmp.x, tmp.y);
	vertices[18] = tmp.x;
	vertices[19] = tmp.y + 0.1;
	vertices[21] = tmp.x + 0.1;
	vertices[22] = tmp.y + 0.1;
	vertices[24] = tmp.x;
	vertices[25] = tmp.y;

	vertices[27] = tmp.x + 0.1;
	vertices[28] = tmp.y + 0.1;
	vertices[30] = tmp.x + 0.1;
	vertices[31] = tmp.y;
	vertices[33] = tmp.x;
	vertices[34] = tmp.y;


	glutMainLoopEvent();
	printf("haha\n");
	glutPostRedisplay();
}

/**
* 主函数
*/
//initiate window size
int gl_work_init(int width0, int height0, BigTex bigtex) {
	bool res = GLInit(0, 0);
	if (!res) return 0;
	glutReshapeWindow(width0, height0);
	glutDisplayFunc(RenderScenceCB);
	glutSpecialFunc(SpecialKeyboardCB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateTexture(bigtex);

	GLProgram g_program;
	g_program.CreateProgram();
	g_program.UseShaders_file("shader/test.vert", "shader/test.frag");

	// 通知开始GLUT的内部循环
	// 只运行一次，Render to texture
	//RenderScenceCB();
	return 0;
}