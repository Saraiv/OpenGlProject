#include "PoolTable.hpp"

using namespace Table;

void PoolTable::Render(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    vector<vec3> model = Model();
    verticesCount = model.size();

    glBufferData(GL_ARRAY_BUFFER, model.size() * sizeof(vec3), model.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PoolTable::Draw(vector<vec3> model, mat4 mvp){
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, false, value_ptr(mvp));
    glDrawArrays(GL_QUADS, 0, model.size());
    glUseProgram(0);
}

vector<vec3> PoolTable::Model(){
    return vector<vec3> {
        //Front
		vec3(-tableWidth, -tableHeight, tableLarge),
		vec3(tableWidth, -tableHeight, tableLarge),
		vec3(tableWidth, tableHeight, tableLarge),
		vec3(-tableWidth, tableHeight, tableLarge),

		//Back
		vec3(-tableWidth, -tableHeight, -tableLarge),
		vec3(-tableWidth, tableHeight, -tableLarge),
		vec3(tableWidth, tableHeight, -tableLarge),
		vec3(tableWidth, -tableHeight, -tableLarge),

		//Left
		vec3(-tableWidth, -tableHeight, tableLarge),
		vec3(-tableWidth, tableHeight, tableLarge),
		vec3(-tableWidth, tableHeight, -tableLarge),
		vec3(-tableWidth, -tableHeight, -tableLarge),

		//Right
		vec3(tableWidth, -tableHeight, tableLarge),
		vec3(tableWidth, -tableHeight, -tableLarge),
		vec3(tableWidth, tableHeight, -tableLarge),
		vec3(tableWidth, tableHeight, tableLarge),

		//Top
		vec3(-tableWidth, tableHeight, tableLarge),
		vec3(tableWidth, tableHeight, tableLarge),
		vec3(tableWidth, tableHeight, -tableLarge),
		vec3(-tableWidth, tableHeight, -tableLarge),

		//Bottom 
		vec3(-tableWidth, -tableHeight, tableLarge),
		vec3(-tableWidth, -tableHeight, -tableLarge),
		vec3(tableWidth, -tableHeight, -tableLarge),
		vec3(tableWidth, -tableHeight, tableLarge)
    };
}

GLuint PoolTable::Program(){
    ShaderInfo shader[] = {
        { GL_VERTEX_SHADER, "PoolTable.vert" },
        { GL_FRAGMENT_SHADER, "PoolTable.frag" },
        { GL_NONE, NULL }
    };

    return LoadShaders(shader);
}