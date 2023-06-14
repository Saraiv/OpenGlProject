#version 440 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat3 NormalMatrix;

in vec3 vertexPosition;
in vec3 vertexNormals;
in vec2 textureCoords;

out vec2 uv;
out vec3 normal;
out vec3 vertexPositionPlanetSpace;
out vec3 vNormalPlanetSpace;

void main(){
	normal = vertexNormals;
	uv = textureCoords;
	vertexPositionPlanetSpace = (ModelView * vec4(vertexPosition, 1.0)).xyz;
	vNormalPlanetSpace = normalize(NormalMatrix * vertexNormals);
	gl_Position = Projection * ModelView * vec4(vertexPosition, 1.0f);
}