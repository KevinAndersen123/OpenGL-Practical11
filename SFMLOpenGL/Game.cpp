#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} MyVertex;

MyVertex initialVertex[36]; //Original Vertexes
MyVertex vertex[36];		//Current Vertexes
GLubyte triangles[36];		//Triangles to be drawn

							/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
vsid,		//Vertex Shader ID
fsid,		//Fragment Shader ID
progID,		//Program ID
vao = 0,	//Vertex Array ID
vbo[1],		// Vertex Buffer ID
positionID, //Position ID
colorID,	// Color ID
to,			// Texture ID 1 to 32
textureID,	//Texture ID
texelID;	// Texel ID


			

//const string filename = "tnt1.tga";
//const string filename = "diamond.tga";
const string filename = "RAGNAR.tga";


int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	//Declare all starting positions of the vertexes.
	initialVertex[0].coordinate[0] = -0.5f;
	initialVertex[0].coordinate[1] = -0.5f;
	initialVertex[0].coordinate[2] = -0.5f;

	initialVertex[1].coordinate[0] = -0.5f;
	initialVertex[1].coordinate[1] = -0.5f;
	initialVertex[1].coordinate[2] = 0.5f;

	initialVertex[2].coordinate[0] = -0.5f;
	initialVertex[2].coordinate[1] = 0.5f;
	initialVertex[2].coordinate[2] = -0.5f;

	initialVertex[3].coordinate[0] = 0.5f;
	initialVertex[3].coordinate[1] = 0.5f;
	initialVertex[3].coordinate[2] = -0.5f;

	initialVertex[4].coordinate[0] = -0.5f;
	initialVertex[4].coordinate[1] = -0.5f;
	initialVertex[4].coordinate[2] = -0.5f;

	initialVertex[5].coordinate[0] = -0.5f;
	initialVertex[5].coordinate[1] = 0.5f;
	initialVertex[5].coordinate[2] = -0.5f;

	initialVertex[6].coordinate[0] = 0.5f;
	initialVertex[6].coordinate[1] = -0.5f;
	initialVertex[6].coordinate[2] = 0.5f;

	initialVertex[7].coordinate[0] = -0.5f;
	initialVertex[7].coordinate[1] = -0.5f;
	initialVertex[7].coordinate[2] = -0.5f;

	initialVertex[8].coordinate[0] = 0.5f;
	initialVertex[8].coordinate[1] = -0.5f;
	initialVertex[8].coordinate[2] = -0.5f;

	initialVertex[9].coordinate[0] = 0.5f;
	initialVertex[9].coordinate[1] = 0.5f;
	initialVertex[9].coordinate[2] = -0.5f;

	initialVertex[10].coordinate[0] = 0.5f;
	initialVertex[10].coordinate[1] = -0.5f;
	initialVertex[10].coordinate[2] = -0.5f;

	initialVertex[11].coordinate[0] = -0.5f;
	initialVertex[11].coordinate[1] = -0.5f;
	initialVertex[11].coordinate[2] = -0.5f;

	initialVertex[12].coordinate[0] = -0.5f;
	initialVertex[12].coordinate[1] = -0.5f;
	initialVertex[12].coordinate[2] = 0.5f;

	initialVertex[13].coordinate[0] = -0.5f;
	initialVertex[13].coordinate[1] = 0.5f;
	initialVertex[13].coordinate[2] = 0.5f;

	initialVertex[14].coordinate[0] = -0.5f;
	initialVertex[14].coordinate[1] = 0.5f;
	initialVertex[14].coordinate[2] = -0.5f;

	initialVertex[15].coordinate[0] = 0.5f;
	initialVertex[15].coordinate[1] = -0.5f;
	initialVertex[15].coordinate[2] = 0.5f;

	initialVertex[16].coordinate[0] = -0.5f;
	initialVertex[16].coordinate[1] = -0.5f;
	initialVertex[16].coordinate[2] = 0.5f;

	initialVertex[17].coordinate[0] = -0.5f;
	initialVertex[17].coordinate[1] = -0.5f;
	initialVertex[17].coordinate[2] = -0.5f;

	initialVertex[18].coordinate[0] = -0.5f;
	initialVertex[18].coordinate[1] = 0.5f;
	initialVertex[18].coordinate[2] = 0.5f;

	initialVertex[19].coordinate[0] = -0.5f;
	initialVertex[19].coordinate[1] = -0.5f;
	initialVertex[19].coordinate[2] = 0.5f;

	initialVertex[20].coordinate[0] = 0.5f;
	initialVertex[20].coordinate[1] = -0.5f;
	initialVertex[20].coordinate[2] = 0.5f;

	initialVertex[21].coordinate[0] = 0.5f;
	initialVertex[21].coordinate[1] = 0.5f;
	initialVertex[21].coordinate[2] = 0.5f;

	initialVertex[22].coordinate[0] = 0.5f;
	initialVertex[22].coordinate[1] = -0.5f;
	initialVertex[22].coordinate[2] = -0.5f;

	initialVertex[23].coordinate[0] = 0.5f;
	initialVertex[23].coordinate[1] = 0.5f;
	initialVertex[23].coordinate[2] = -0.5f;

	initialVertex[24].coordinate[0] = 0.5f;
	initialVertex[24].coordinate[1] = -0.5f;
	initialVertex[24].coordinate[2] = -0.5f;

	initialVertex[25].coordinate[0] = 0.5f;
	initialVertex[25].coordinate[1] = 0.5f;
	initialVertex[25].coordinate[2] = 0.5f;

	initialVertex[26].coordinate[0] = 0.5f;
	initialVertex[26].coordinate[1] = -0.5f;
	initialVertex[26].coordinate[2] = 0.5f;

	initialVertex[27].coordinate[0] = 0.5f;
	initialVertex[27].coordinate[1] = 0.5f;
	initialVertex[27].coordinate[2] = 0.5f;

	initialVertex[28].coordinate[0] = 0.5f;
	initialVertex[28].coordinate[1] = 0.5f;
	initialVertex[28].coordinate[2] = -0.5f;

	initialVertex[29].coordinate[0] = -0.5f;
	initialVertex[29].coordinate[1] = 0.5f;
	initialVertex[29].coordinate[2] = -0.5f;

	initialVertex[30].coordinate[0] = 0.5f;
	initialVertex[30].coordinate[1] = 0.5f;
	initialVertex[30].coordinate[2] = 0.5f;

	initialVertex[31].coordinate[0] = -0.5f;
	initialVertex[31].coordinate[1] = 0.5f;
	initialVertex[31].coordinate[2] = -0.5f;

	initialVertex[32].coordinate[0] = -0.5f;
	initialVertex[32].coordinate[1] = 0.5f;
	initialVertex[32].coordinate[2] = 0.5f;

	initialVertex[33].coordinate[0] = 0.5f;
	initialVertex[33].coordinate[1] = 0.5f;
	initialVertex[33].coordinate[2] = 0.5f;

	initialVertex[34].coordinate[0] = -0.5f;
	initialVertex[34].coordinate[1] = 0.5f;
	initialVertex[34].coordinate[2] = 0.5f;


	initialVertex[35].coordinate[0] = 0.5f;
	initialVertex[35].coordinate[1] = -0.5f;
	initialVertex[35].coordinate[2] = 0.5f;

	initialVertex[0].texel[0] = 0.75f;
	initialVertex[0].texel[1] = 0.25f;

	initialVertex[1].texel[0] = 1.0f;
	initialVertex[1].texel[1] = 0.25f;

	initialVertex[2].texel[0] = 1.0f;
	initialVertex[2].texel[1] = 0.5f;

	initialVertex[3].texel[0] = 0.75f;
	initialVertex[3].texel[1] = 0.5f;

	initialVertex[4].texel[0] = 0.5f;
	initialVertex[4].texel[1] = 0.25f;

	initialVertex[5].texel[0] = 0.5f;
	initialVertex[5].texel[1] = 0.5f;

	initialVertex[6].texel[0] = 0.25f;
	initialVertex[6].texel[1] = 0.0f;

	initialVertex[7].texel[0] = 0.0f;
	initialVertex[7].texel[1] = 0.25f;

	initialVertex[8].texel[0] = 0.25f;
	initialVertex[8].texel[1] = 0.25f;

	initialVertex[9].texel[0] = 0.50f;
	initialVertex[9].texel[1] = 0.5f;

	initialVertex[10].texel[0] = 0.50f;
	initialVertex[10].texel[1] = 0.25f;

	initialVertex[11].texel[0] = 0.75f;
	initialVertex[11].texel[1] = 0.25f;

	initialVertex[12].texel[0] = 0.75f;
	initialVertex[12].texel[1] = 0.25f;

	initialVertex[13].texel[0] = 1.0f;
	initialVertex[13].texel[1] = 0.5f;

	initialVertex[14].texel[0] = 0.75f;
	initialVertex[14].texel[1] = 0.5f;

	initialVertex[15].texel[0] = 0.25f;
	initialVertex[15].texel[1] = 0.25f;

	initialVertex[16].texel[0] = 0.0f;
	initialVertex[16].texel[1] = 0.25f;

	initialVertex[17].texel[0] = 0.0f;
	initialVertex[17].texel[1] = 0.0f;

	initialVertex[18].texel[0] = 0.0f;
	initialVertex[18].texel[1] = 0.5f;

	initialVertex[19].texel[0] = 0.0f;
	initialVertex[19].texel[1] = 0.25f;

	initialVertex[20].texel[0] = 0.25f;
	initialVertex[20].texel[1] = 0.25f;

	initialVertex[21].texel[0] = 0.25f;
	initialVertex[21].texel[1] = 0.5f;

	initialVertex[22].texel[0] = 0.50f;
	initialVertex[22].texel[1] = 0.25f;

	initialVertex[23].texel[0] = 0.50f;
	initialVertex[23].texel[1] = 0.5f;

	initialVertex[24].texel[0] = 0.25f;
	initialVertex[24].texel[1] = 0.5f;

	initialVertex[25].texel[0] = 0.25f;
	initialVertex[25].texel[1] = 0.25f;

	initialVertex[26].texel[0] = 0.25f;
	initialVertex[26].texel[1] = 0.25f;

	initialVertex[27].texel[0] = 0.0f;
	initialVertex[27].texel[1] = 0.5f;

	initialVertex[28].texel[0] = 0.0f;
	initialVertex[28].texel[1] = 0.75f;

	initialVertex[29].texel[0] = 0.25f;
	initialVertex[29].texel[1] = 0.75f;

	initialVertex[30].texel[0] = 0.25f;
	initialVertex[30].texel[1] = 0.5f;

	initialVertex[31].texel[0] = 0.0f;
	initialVertex[31].texel[1] = 0.75f;

	initialVertex[32].texel[0] = 0.0f;
	initialVertex[32].texel[1] = 0.5f;

	initialVertex[33].texel[0] = 0.25f;
	initialVertex[33].texel[1] = 0.5f;

	initialVertex[34].texel[0] = 0.0f;
	initialVertex[34].texel[1] = 0.5f;

	initialVertex[35].texel[0] = 0.25f;
	initialVertex[35].texel[1] = 0.25f;

	//Set current vertex to initial.
	for (int i = 0; i < 36; i++)
	{
		vertex[i] = initialVertex[i];
	}

	/*Index of Poly / Triangle to Draw */
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;
	triangles[6] = 6;   triangles[7] = 7;   triangles[8] = 8;
	triangles[9] = 9;   triangles[10] = 10;   triangles[11] = 11;
	triangles[12] = 12;   triangles[13] = 13;   triangles[14] = 14;
	triangles[15] = 15;   triangles[16] = 16;   triangles[17] = 17;
	triangles[18] = 18;   triangles[19] = 19;   triangles[20] = 20;
	triangles[21] = 21;   triangles[22] = 22;   triangles[23] = 23;
	triangles[24] = 24;   triangles[25] = 25;   triangles[26] = 26;
	triangles[27] = 27;   triangles[28] = 28;   triangles[29] = 29;
	triangles[30] = 30;   triangles[31] = 31;   triangles[32] = 32;
	triangles[33] = 33;   triangles[34] = 34;   triangles[35] = 35;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_texel;"
		"out vec4 color;"
		"out vec2 texel;"
		"void main() {"
		"	color = sv_color;"
		"	texel = sv_texel;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

						   //Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	const char* fs_src = "#version 400\n\r"
		"uniform sampler2D f_texture;"
		"in vec4 color;"
		"in vec2 texel;"
		"out vec4 fColor;"
		"void main() {"
		"	fColor = texture(f_texture, texel.st);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	//Move the cube up or down.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_displacmentVector.y += 0.0005f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_displacmentVector.y -= 0.0005f;
	}

	//Move the cube left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_displacmentVector.x -= 0.0005f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_displacmentVector.x += 0.0005f;
	}

	//Rotate on Z clockwise.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_rotationAngleZ -= 0.0005f;

		if (m_rotationAngleZ > 360.0f)
		{
			m_rotationAngleZ -= 360.0f;
		}
	}

	//Rotate on X clockwise.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{

		m_rotationAngleX -= 0.0005f;

		if (m_rotationAngleX > 360.0f)
		{
			m_rotationAngleX -= 360.0f;
		}
	}

	//Rotate on Y clockwise
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		m_rotationAngleY -= 0.0005f;

		if (m_rotationAngleY > 360.0f)
		{
			m_rotationAngleY -= 360.0f;
		}
	}

	//Scale down.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_scale -= 0.0005f;
	}

	//Scale up.
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_scale += 0.0005f;
	}

	//Update the position of all the points.
	for (int i = 0; i < 36; i++)
	{
		//Assigne the initial vertex to a tempory vector
		MyVector3 tempVect{ initialVertex[i].coordinate[0], initialVertex[i].coordinate[1], initialVertex[i].coordinate[2] };

		tempVect = MyMatrix3::rotationX(m_rotationAngleX) * tempVect;
		tempVect = MyMatrix3::rotationY(m_rotationAngleY) * tempVect;
		tempVect = MyMatrix3::rotationZ(m_rotationAngleZ) * tempVect;
		tempVect = MyMatrix3::scale(m_scale) * tempVect;
		tempVect += m_displacmentVector;
		vertex[i].coordinate[0] = tempVect.x;
		vertex[i].coordinate[1] = tempVect.y;
		vertex[i].coordinate[2] = tempVect.z;
	}

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
	CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex) * 36, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
	model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (void*)(7 * sizeof(float)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}
