#include "Planets.hpp"
using namespace Planet;

#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb/stb_image.h"

void Planets::GetPointersId(GLuint shader, GLuint vertexId, GLuint normalsId, GLuint texturesId, GLuint textureId, int counter){
    this->shader = shader;
    this->vertexId = vertexId;
    this->normalsId = normalsId;
    this->texturesId = texturesId;
    this->textureId = textureId;
    this->counter = counter;
}

void Planets::Read(const string fileName){
    // planet pos
    vector<fvec3> vertexPosition; // (x, y, z)
	vector<fvec2> vertexTextureCoord; // (x, y)
	vector<fvec3> vertexNormal; // (x, y, z)

    // planet faces
    vector<GLint> vertexPositionIndicies;
	vector<GLint> vertexTextureCoordIndicies;
	vector<GLint> vertexNormalIndicies;

    stringstream ss;
    ifstream inFile(objectsPath + fileName);
    string line = "";
    string pre = "";
    string nextFile;

    vec3 vec3Aux;
    vec2 vec2Aux;

    try {
		if (!inFile.is_open())
			throw runtime_error("Error opening the planet file");
	} catch (const exception& e){
		cout << "Exception occurred: " << e.what() << endl;
	}

    while(getline(inFile, line)){
        ss.str(line);
        ss >> pre;

        if(pre == "mtllib", "v", "vt", "vn", "f"){
            if(pre == "mtllib"){
                ss >> nextFile;
                Material(nextFile);
            } else if(pre == "v"){
                ss >> vec3Aux.x >> vec3Aux.y >> vec3Aux.z;
                vertexPosition.push_back(vec3Aux);
            } else if(pre == "vn"){
                ss >> vec3Aux.x >> vec3Aux.y >> vec3Aux.z;
                vertexNormal.push_back(vec3Aux);
            } else if(pre == "vt"){
                ss >> vec2Aux.x >> vec2Aux.y;
                vertexTextureCoord.push_back(vec2Aux);
            } else if(pre == "f"){
                for(int i = 0; i < 3; i++){
                    string data;
                    ss >> data;
                    istringstream iss(data);

                    string index;
                    getline(iss, index, '/');
                    int vIndex = stoi(index) - 1;

                    getline(iss, index, '/');
                    int nIndex = stoi(index) - 1;

                    getline(iss, index, '/');
                    int tIndex = stoi(index) - 1;


                    vertex_positions.push_back(vertexPosition[vIndex]);
                    vertex_normals.push_back(vertexNormal[nIndex]);
                    vertex_textures_coords.push_back(vertexTextureCoord[tIndex]);
                }
            }
        }
        ss.clear();
    }

    inFile.close();
}

void Planets::Material(const string fileName){
    ifstream inFile(materialsPath + fileName);
    vec3 vec3Aux;
    string line = "";

    while(getline(inFile, line)){
        istringstream iss(line);
        string pre;
		string nextFile;

		iss >> pre;

		if(pre == "Ka"){ // Ambiental light
			iss >> vec3Aux.x >> vec3Aux.y >> vec3Aux.z;
			ka = vec3Aux;
		}
		else if(pre == "Kd"){ // Directional light
			iss >> vec3Aux.x >> vec3Aux.y >> vec3Aux.z;
			kd = vec3Aux;
		}
		else if(pre == "Ks"){ // Specular light
			iss >> vec3Aux.x >> vec3Aux.y >> vec3Aux.z;
			ks = vec3Aux;
		}
		else if(pre == "Ns") // Brightness
			iss >> ns;
		else if(pre == "map_Kd"){ // Image
			iss >> nextFile;
			Texture(nextFile);
		}
    }

    inFile.close();
}

void Planets::Texture(const string textureFile){
    glActiveTexture(GL_TEXTURE0);

    GLuint textureName = counter;
    this->textureName = textureName;

    string textureFileTemp = imagesPath + textureFile;

    glGenTextures(1, &textureName);
    glBindTexture(GL_TEXTURE_2D, textureName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nChannels;
    unsigned char* image = stbi_load(textureFileTemp.c_str(), &width, &height, &nChannels, 0);

    if(image){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(image);
    } else cout << "Error opening texture" << endl;
}

void Planets::Send(void){
    GLfloat BindVertex[24192 * 3];
	GLfloat BindNormals[24192 * 3];
	GLfloat BindTextures[24192 * 2];

	for (int i = 0; i < vertex_positions.size(); i++) {
		//Vertex (x, y, z)
		BindVertex[i * 3] = vertex_positions[i].x;
		BindVertex[i * 3 + 1] = vertex_positions[i].y;
		BindVertex[i * 3 + 2] = vertex_positions[i].z;
		
		//Normals (x, y, z)
		BindNormals[i * 3] = vertex_normals[i].x;
		BindNormals[i * 3 + 1] = vertex_normals[i].y;
		BindNormals[i * 3 + 2] = vertex_normals[i].z;

		//Textures (x, y)
		BindTextures[i * 2] = vertex_textures_coords[i].x;
		BindTextures[i * 2 + 1] = vertex_textures_coords[i].y;
	}

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(3, VBO);
    for(int i = 0; i < 3; i++){
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        if (i == 0)
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(BindVertex), BindVertex, 0);
		if (i == 1)
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(BindNormals), BindNormals, 0);
		if (i == 2)
			glBufferStorage(GL_ARRAY_BUFFER, sizeof(BindTextures), BindTextures, 0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glVertexAttribPointer(vertexId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer(normalsId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glVertexAttribPointer(texturesId, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(vertexId);
	glEnableVertexAttribArray(normalsId);
	glEnableVertexAttribArray(texturesId);

    glProgramUniform1i(shader, textureId, 0);

    GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error: " << error << std::endl;                           
	}
}


void Planets::Draw(vec3 position, vec3 orientation, mat4 modelMatrix){
    Camera::GetInstance()->Update();

    mat4 tempPlanet = modelMatrix;

    tempPlanet = translate(tempPlanet, position);

    tempPlanet = rotate(tempPlanet, radians(orientation.x), vec3(1, 0, 0)); //pitch
	tempPlanet = rotate(tempPlanet, radians(orientation.y), vec3(0, 1, 0)); //yaw
	tempPlanet = rotate(tempPlanet, radians(orientation.z), vec3(0, 0, 1)); //roll

    GLint modelId = glGetProgramResourceLocation(shader, GL_UNIFORM, "Model");
	glProgramUniformMatrix4fv(shader, modelId, 1, GL_FALSE, value_ptr(tempPlanet));

	mat4 modelView = Camera::GetInstance()->view * tempPlanet;
	GLint modelViewId = glGetProgramResourceLocation(shader, GL_UNIFORM, "ModelView");
	glProgramUniformMatrix4fv(shader, modelViewId, 1, GL_FALSE, value_ptr(modelView));

	mat3 normalMatrix = inverseTranspose(mat3(modelView));
	GLint normalMatrixId = glGetProgramResourceLocation(shader, GL_UNIFORM, "NormalMatrix");
	glProgramUniformMatrix4fv(shader, normalMatrixId, 1, GL_FALSE, value_ptr(normalMatrix));

	GLint viewId = glGetProgramResourceLocation(shader, GL_UNIFORM, "View");
	glProgramUniformMatrix4fv(shader, viewId, 1, GL_FALSE, value_ptr(Camera::GetInstance()->view));

	GLint projectionId = glGetProgramResourceLocation(shader, GL_UNIFORM, "Projection");
	glProgramUniformMatrix4fv(shader, projectionId, 1, GL_FALSE, value_ptr(Camera::GetInstance()->projection));

	glBindTexture(GL_TEXTURE_2D, textureName + 1);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, vertex_positions.size());
}

Planets::~Planets(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, VBO);
    glDeleteProgram(shader);
}