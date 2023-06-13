#version 440 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat3 NormalMatrix;

in vec3 VPosition;
in vec3 VNormals;
in vec2 texCoords;

out vec2 uv;
out vec3 normal;
out vec3 vPositionEyeSpace;
out vec3 vNormalEyeSpace;

void main(){
	normal = VNormals;
	uv = texCoords;
	vPositionEyeSpace = (ModelView * vec4(VPosition, 1.0)).xyz;
	vNormalEyeSpace = normalize(NormalMatrix * VNormals);
	gl_Position = Projection * ModelView * vec4(VPosition, 1.0f);
}