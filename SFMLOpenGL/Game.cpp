#include <Game.h>



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
} Vert;

Vert vertex[36];
Vert finalVertex[36];
GLubyte triangles[36];

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

//const string filename = "minecraft.tga";
//const string filename = "cube.tga";

//const string filename = "tnt1.tga";
const string filename = "diamond.tga";


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
	setupPoints();
	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));
	//setup colour
	for (int i = 0; i < 36; i++)
	{
		vertex[i].color[0] = (rand() % 11) / 10.0f;
		vertex[i].color[1] = (rand() % 11) / 10.0f;
		vertex[i].color[2] = (rand() % 11) / 10.0f;
		vertex[i].color[3] = 1.0f;
	}

	//setup index for triangles
	for (int i = 0; i < 36; i++)
	{
		triangles[i] = i;
	}

	for (int i = 0; i < 36; i++)
	{
		finalVertex[i] = vertex[i];
	}

	for (int i = 0; i < 36; i = i + 6)
	{
		vertex[i].texel[0] = 0.0;
		vertex[i].texel[1] = 0.0;

		vertex[i + 1].texel[0] = 1.0;
		vertex[i + 1].texel[1] = 0.0;

		vertex[i + 2].texel[0] = 1.0;
		vertex[i + 2].texel[1] = 1.0;

		vertex[i + 3].texel[0] = 1.0;
		vertex[i + 3].texel[1] = 1.0;

		vertex[i + 4].texel[0] = 0.0;
		vertex[i + 4].texel[1] = 1.0;

		vertex[i + 5].texel[0] = 0.0;
		vertex[i + 5].texel[1] = 0.0;
	}

	

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, finalVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"layout(location = 0) in vec3 sv_position;"
		"layout(location = 1) in vec4 sv_color;"
		"layout(location = 2) in vec2 sv_texel;"

		"out vec4 color;"
		"out vec2 texel;"
		"void main() {"
		"	color = sv_color;"
		"	texel = sv_texel;"
		"	gl_Position = vec4(sv_position, 1.0);"
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

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"uniform sampler2D f_texture;"
		"in vec4 color;"
		"in vec2 texel;"
		"out vec4 fColor;"
		"void main() {"
		//"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		//"	fColor = color * texture2D(f_texture, texel);"
		"	fColor = texture2D(f_texture, texel);"
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
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
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
	glEnable(GL_DEPTH_TEST);
	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
	glBindAttribLocation(progID, texelID, "sv_position");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	glUseProgram(progID);
	//Move the cube up 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_displacmentVector.y += 0.0005f;
	}

	//moves cube down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_displacmentVector.y -= 0.0005f;
	}

	//Move the cube left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_displacmentVector.x -= 0.0005f;
	}

	//moves cube right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_displacmentVector.x += 0.0005f;
	}

	//Scale down.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_scale -= 0.005f;
	}

	//Scale up.
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_scale += 0.005f;
	}

	//Rotates X clockwise.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{

		m_rotationAngleX += 0.0005f;

		if (m_rotationAngleX > 360.0f)
		{
			m_rotationAngleX -= 360.0f;
		}
	}

	//Rotates Y clockwise
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		m_rotationAngleY += 0.0005f;

		if (m_rotationAngleY > 360.0f)
		{
			m_rotationAngleY -= 360.0f;
		}
	}

	//Rotates Z clockwise
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_rotationAngleZ += 0.0005f;

		if (m_rotationAngleZ > 360.0f)
		{
			m_rotationAngleZ -= 360.0f;
		}
	}

	//updates all points' position
	for (int i = 0; i < 36; i++)
	{
		MyVector3 tempVect{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
		tempVect = MyMatrix3::scale(m_scale) * tempVect;
		tempVect += m_displacmentVector;
		tempVect = MyMatrix3::rotationX(m_rotationAngleX) * tempVect;
		tempVect = MyMatrix3::rotationY(m_rotationAngleY) * tempVect;
		tempVect = MyMatrix3::rotationZ(m_rotationAngleZ) * tempVect;

		finalVertex[i].coordinate[0] = tempVect.x;
		finalVertex[i].coordinate[1] = tempVect.y;
		finalVertex[i].coordinate[2] = tempVect.z;
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, finalVertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)(7 * sizeof(float)));

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

void Game::setupPoints()
{
	//Declare all starting positions of the vertexs

	// Front
	vertex[0].coordinate[0] = -0.5;
	vertex[0].coordinate[1] = -0.5;
	vertex[0].coordinate[2] = 0.5;

	vertex[1].coordinate[0] = 0.5;
	vertex[1].coordinate[1] = -0.5;
	vertex[1].coordinate[2] = 0.5;

	vertex[2].coordinate[0] = 0.5;
	vertex[2].coordinate[1] = 0.5;
	vertex[2].coordinate[2] = 0.5;

	vertex[3].coordinate[0] = 0.5;
	vertex[3].coordinate[1] = 0.5;
	vertex[3].coordinate[2] = 0.5;

	vertex[4].coordinate[0] = -0.5;
	vertex[4].coordinate[1] = 0.5;
	vertex[4].coordinate[2] = 0.5;

	vertex[5].coordinate[0] = -0.5;
	vertex[5].coordinate[1] = -0.5;
	vertex[5].coordinate[2] = 0.5;

	// right side 

	vertex[6].coordinate[0] = 0.5;
	vertex[6].coordinate[1] = -0.5;
	vertex[6].coordinate[2] = 0.5;

	vertex[7].coordinate[0] = 0.5;
	vertex[7].coordinate[1] = -0.5;
	vertex[7].coordinate[2] = -0.5;

	vertex[8].coordinate[0] = 0.5;
	vertex[8].coordinate[1] = 0.5;
	vertex[8].coordinate[2] = -0.5;


	vertex[9].coordinate[0] = 0.5;
	vertex[9].coordinate[1] = 0.5;
	vertex[9].coordinate[2] = -0.5;

	vertex[10].coordinate[0] = 0.5;
	vertex[10].coordinate[1] = 0.5;
	vertex[10].coordinate[2] = 0.5;

	vertex[11].coordinate[0] = 0.5;
	vertex[11].coordinate[1] = -0.5;
	vertex[11].coordinate[2] = 0.5;

	// left side 

	vertex[12].coordinate[0] = -0.5;
	vertex[12].coordinate[1] = -0.5;
	vertex[12].coordinate[2] = -0.5;

	vertex[13].coordinate[0] = -0.5;
	vertex[13].coordinate[1] = -0.5;
	vertex[13].coordinate[2] = 0.5;

	vertex[14].coordinate[0] = -0.5;
	vertex[14].coordinate[1] = 0.5;
	vertex[14].coordinate[2] = 0.5;

	vertex[15].coordinate[0] = -0.5;
	vertex[15].coordinate[1] = 0.5;
	vertex[15].coordinate[2] = 0.5;

	vertex[16].coordinate[0] = -0.5;
	vertex[16].coordinate[1] = 0.5;
	vertex[16].coordinate[2] = -0.5;

	vertex[17].coordinate[0] = -0.5;
	vertex[17].coordinate[1] = -0.5;
	vertex[17].coordinate[2] = -0.5;

	//// Back
	vertex[18].coordinate[0] = 0.5;
	vertex[18].coordinate[1] = -0.5;
	vertex[18].coordinate[2] = -0.5;

	vertex[19].coordinate[0] = -0.5;
	vertex[19].coordinate[1] = -0.5;
	vertex[19].coordinate[2] = -0.5;

	vertex[20].coordinate[0] = -0.5;
	vertex[20].coordinate[1] = 0.5;
	vertex[20].coordinate[2] = -0.5;

	vertex[21].coordinate[0] = -0.5;
	vertex[21].coordinate[1] = 0.5;
	vertex[21].coordinate[2] = -0.5;

	vertex[22].coordinate[0] = 0.5;
	vertex[22].coordinate[1] = 0.5;
	vertex[22].coordinate[2] = -0.5;

	vertex[23].coordinate[0] = 0.5;
	vertex[23].coordinate[1] = -0.5;
	vertex[23].coordinate[2] = -0.5;

	// bottom
	vertex[24].coordinate[0] = -0.5;
	vertex[24].coordinate[1] = -0.5;
	vertex[24].coordinate[2] = -0.5;

	vertex[25].coordinate[0] = 0.5;
	vertex[25].coordinate[1] = -0.5;
	vertex[25].coordinate[2] = -0.5;

	vertex[26].coordinate[0] = 0.5;
	vertex[26].coordinate[1] = -0.5;
	vertex[26].coordinate[2] = 0.5;

	vertex[27].coordinate[0] = 0.5;
	vertex[27].coordinate[1] = -0.5;
	vertex[27].coordinate[2] = 0.5;

	vertex[28].coordinate[0] = -0.5;
	vertex[28].coordinate[1] = -0.5;
	vertex[28].coordinate[2] = 0.5;

	vertex[29].coordinate[0] = -0.5;
	vertex[29].coordinate[1] = -0.5;
	vertex[29].coordinate[2] = -0.5;

	// Top
	vertex[30].coordinate[0] = -0.5;
	vertex[30].coordinate[1] = 0.5;
	vertex[30].coordinate[2] = 0.5;

	vertex[31].coordinate[0] = 0.5;
	vertex[31].coordinate[1] = 0.5;
	vertex[31].coordinate[2] = 0.5;

	vertex[32].coordinate[0] = 0.5;
	vertex[32].coordinate[1] = 0.5;
	vertex[32].coordinate[2] = -0.5;

	vertex[33].coordinate[0] = 0.5;
	vertex[33].coordinate[1] = 0.5;
	vertex[33].coordinate[2] = -0.5;

	vertex[34].coordinate[0] = -0.5;
	vertex[34].coordinate[1] = 0.5;
	vertex[34].coordinate[2] = -0.5;

	vertex[35].coordinate[0] = -0.5;
	vertex[35].coordinate[1] = 0.5;
	vertex[35].coordinate[2] = 0.5;
}