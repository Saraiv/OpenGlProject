#version 440 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat3 NormalMatrix;

in vec3 VertexPosition;
in vec3 VertexNormals;
in vec2 TextureCoords;

out vec2 UV;
out vec3 Normal;
out vec3 VertexPositionPlanetSpace;
out vec3 VertexNormalPlanetSpace;

void main(){ 
	Normal = VertexNormals;
	UV = TextureCoords;
	VertexPositionPlanetSpace = (ModelView * vec4(VertexPosition, 1.0)).xyz;
	VertexNormalPlanetSpace = normalize(NormalMatrix * VertexNormals);
	gl_Position = Projection * ModelView * vec4(VertexPosition, 1.0f);
}