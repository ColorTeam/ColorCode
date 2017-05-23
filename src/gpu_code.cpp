#include "gl_helper.h"
#include "utils.h"
#include "GameObject.h"

GLuint VBO;
GLuint EBO;
//GLuint g_tex[MAX_TEX];
//int texn = 0;

int m_t = 2;// 6;
int m_v = 4;// 18;
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

	0.0, 1.0, 0.2,
	1.0, 1.0, 0.2,
	0.0, 0.0, 0.2,

	1.0, 1.0, 0.2,
	1.0, 0.0, 0.2,
	0.0, 0.0, 0.2,

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
	12, 13, 14,
	15, 16, 17,
};

/**
* 渲染回调函数
*/
void RenderGameObject(SpriteFrame nowFrame, Vec2f Pos) {
	for (int i = 0; i < 4; i++) {
		vertices[i << 1] = Pos.x + nowFrame.v[i].x / 1024 * 2;
		vertices[(i << 1) + 1] = Pos.y + nowFrame.v[i].y / 1024 * 2;
	}
	glActiveTexture(bigtex[nowFrame.bigtexIndex].tex_id);
	glBindTexture(GL_TEXTURE_2D, bigtex[nowFrame.bigtexIndex].tex_id);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*m_v * 2, vertices);// nowFrame.v);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*m_v * 2, sizeof(float)*m_v * 2, nowFrame.vt);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(m_v * 2 * sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float)*m_t * 3, nowFrame.ebo);
	glDrawElements(GL_TRIANGLES, 3 * m_t, GL_UNSIGNED_INT, 0);
}

void RenderScenceCB() {
	glClear(GL_COLOR_BUFFER_BIT);

	//Render enemys
	for (int index = 0; index < enemy.size(); index++) {
		RenderGameObject(enemy[index].getSpriteFrame(), enemy[index].getGLPosition());
	}

	//Render Player
	RenderGameObject(player.getSpriteFrame(), player.getGLPosition());
	
	//  禁用顶点数据
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glFlush();
	glutSwapBuffers();
	/*
	glClear(GL_COLOR_BUFFER_BIT);
	//for (int i=0; i<bigtex.size(); i++)
	glActiveTexture(bigtex[0].tex_id);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bigtex[0].tex_id);

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
	*/

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_v*4, vertices, GL_DYNAMIC_DRAW);
}

static void CreateIndexBuffer() {
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_t * 3, ebo, GL_DYNAMIC_DRAW);
}

static void CreateTexture(BigTex &bigtex) {
	glGenTextures(1, &bigtex.tex_id);
	glBindTexture(GL_TEXTURE_2D, bigtex.tex_id);
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
	Vec2f pos = player.getGLPosition();
	Vec2f size = player.getGLSize();

	//printf("tmp: %.2f %.2f\n", tmp.x, tmp.y);
	vertices[18] = pos.x;
	vertices[19] = pos.y + size.y;
	vertices[21] = pos.x + size.x;
	vertices[22] = pos.y + size.y;
	vertices[24] = pos.x;
	vertices[25] = pos.y;

	vertices[27] = pos.x + size.x;
	vertices[28] = pos.y + size.y;
	vertices[30] = pos.x + size.x;
	vertices[31] = pos.y;
	vertices[33] = pos.x;
	vertices[34] = pos.y;

	Vec2f pos2 = enemy[0].getGLPosition();
	Vec2f size2 = enemy[0].getGLSize();
	vertices[36] = pos2.x;
	vertices[37] = pos2.y + size2.y;
	vertices[39] = pos2.x + size2.x;
	vertices[40] = pos2.y + size2.y;
	vertices[42] = pos2.x;
	vertices[43] = pos2.y;

	vertices[45] = pos2.x + size2.x;
	vertices[46] = pos2.y + size2.y;
	vertices[48] = pos2.x + size2.x;
	vertices[49] = pos2.y;
	vertices[51] = pos2.x;
	vertices[52] = pos2.y;

	glutMainLoopEvent();
	glutPostRedisplay();
}

/**
* 主函数
*/
//initiate window size
int gl_work_init(int width0, int height0) {
	bool res = GLInit(0, 0);
	if (!res) return 0;
	glutReshapeWindow(width0, height0);
	glutDisplayFunc(RenderScenceCB);
	glutSpecialFunc(SpecialKeyboardCB);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	CreateVertexBuffer();
	CreateIndexBuffer();
	for (int i=0; i<bigtex.size(); i++)
		CreateTexture(bigtex[i]);

	GLProgram g_program;
	g_program.CreateProgram();
	g_program.UseShaders_file("shader/test.vert", "shader/test.frag");

	// 通知开始GLUT的内部循环
	// 只运行一次，Render to texture
	//RenderScenceCB();
	return 0;
}