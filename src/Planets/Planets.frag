#version 470

uniform mat4 Model;
uniform mat4 View;
uniform mat4 ModelView;
uniform sampler2D textureSampler;

uniform samplerCube cubeMap;

struct AmbientLight{
	vec3 ambient;
};

uniform AmbientLight ambientLight;

struct DirectionalLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight directionalLight;

struct PointLight{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

uniform PointLight pointLight;

struct SpotLight{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;

	float spotCutoff, spotExponent;
	vec3 spotDirection;
};

uniform SpotLight spotLight;

struct Material{
	vec3 emissive;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

in vec3 vPositionPlanetSpace;
in vec3 vNormalPlanetSpace;
in vec2 uv;

layout (location = 0) out vec4 fColor;

vec4 calcAmbientLight(AmbientLight light);
vec4 calcDirectionalLight(DirectionalLight light);
vec4 calcPointLight(PointLight light);
vec4 calcSpotLight(SpotLight light);

void main(){
	vec4 emissive = vec4(material.emissive, 1.0);
	vec4 light[4];
	light[0] = calcAmbientLight(ambientLight);
	light[1] = calcDirectionalLight(directionalLight);
	light[2] = calcPointLight(pointLight);
	light[3] = vec4(0.0);
	fColor = (emissive +light[0]+ light[1]+light[2]+light[3] + vec4(0.2)) * texture(textureSampler, uv);
}

vec4 calcAmbientLight(AmbientLight light){
	vec4 ambient = vec4(material.ambient * light.ambient, 1.0);
	return ambient;
}

vec4 calcDirectionalLight(DirectionalLight light){
	vec4 ambient = vec4(material.ambient * light.ambient, 1.0);

	vec3 lightDirectionPlanetSpace = (View * vec4(light.direction, 0.0)).xyz;
	vec3 L = normalize(-lightDirectionPlanetSpace);
	vec3 N = normalize(vNormalPlanetSpace);
	float NdotL = max(dot(N, L), 0.0);
	vec4 diffuse = vec4(material.diffuse * light.diffuse, 1.0) * NdotL;
	
	vec3 V = normalize(-vPositionPlanetSpace);

	vec3 R = reflect(-L, N);
	float RdotV = max(dot(R, V), 0.0);
    
	vec4 specular = pow(RdotV, material.shininess) * vec4(light.specular * material.specular, 1.0);

	return (ambient + diffuse + specular);
}

vec4 calcPointLight(PointLight light){
	vec4 ambient = vec4(material.ambient * light.ambient, 1.0);

	vec3 lightPositionPlanetSpace = (View * vec4(light.position, 1.0)).xyz;
	vec3 L = normalize(lightPositionPlanetSpace - vPositionPlanetSpace);
	vec3 N = normalize(vNormalPlanetSpace);
	float NdotL = max(dot(N, L), 0.0);
	vec4 diffuse = vec4(material.diffuse * light.diffuse, 1.0) * NdotL;

	vec3 V = normalize(-vPositionPlanetSpace);
    
	vec3 R = reflect(-L, N);
	float RdotV = max(dot(R, V), 0.0);
    
	vec4 specular = pow(RdotV, material.shininess) * vec4(light.specular * material.specular, 1.0);
	
	float dist = length(mat3(View) * light.position - vPositionPlanetSpace);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	return (attenuation * (ambient + diffuse + specular));
}
