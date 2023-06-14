#include "Lights.hpp"

using namespace Light;

void Light::Lights(Planets* planets, GLuint shader){
    vec3 off = vec3(0.0f, 0.0f, 0.0f);
    bool l[4] = { true, true, true, true };
    //Environmental
    if(l[0])
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "ambientLight.ambient"), 1, value_ptr(vec3(1.8f, 1.8f, 1.8f)));
    else
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "ambientLight.ambient"), 1, value_ptr(off));
    //Directional
    if(l[1]){
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.direction"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.ambient"), 1, value_ptr(vec3(0.6f, 0.6f, 0.6f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.diffuse"), 1, value_ptr(vec3(1.0f, 1.0f, 1.0f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.specular"), 1, value_ptr(vec3(1.0f, 1.0f, 1.0f)));
    } else{
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.direction"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.ambient"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.diffuse"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.specular"), 1, value_ptr(off));
    }
    //Point
    if(l[2]){
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.position"), 1, value_ptr(vec3(0.0f, 0.0f, 5.0f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.ambient"), 1, value_ptr(vec3(0.1f, 0.1f, 0.1f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.diffuse"), 1, value_ptr(vec3(1.0f, 1.0f, 1.0f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.specular"), 1, value_ptr(vec3(1.0f, 1.0f, 1.0f)));
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.constant"), 1.0f);
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.linear"), 0.06f);
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.quadratic"), 0.02f);
    } else{
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.direction"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.ambient"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.diffuse"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "directionalLight.specular"), 1, value_ptr(off));
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.constant"), 1.0f);
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.linear"), 0.06f);
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "pointLight.quadratic"), 0.02f);
    }
    //Spotlight
    if(l[3]){
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.position"), 1, value_ptr(vec3(0.8f, 0.8f, 0.8f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.ambient"), 1, value_ptr(vec3(2.0f, 2.0f, 2.0f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.diffuse"), 1, value_ptr(vec3(10.0f, 10.0f, 10.0f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.specular"), 1, value_ptr(vec3(10.0f, 10.0f, 10.0f)));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.direction"), 1, value_ptr(vec3(0.0f, 2.0f, 0.0f)));

        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.angle"), 0.00005f);
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.constant"), 1.0f);
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.linear"), 0.06f);
        glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.quadratic"), 0.02f);
    } else{
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.position"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.ambient"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.diffuse"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.specular"), 1, value_ptr(off));
        glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "spotLight.direction"), 1, value_ptr(off));
    }

    glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "material.emissive"), 1, value_ptr(vec3(0.1, 0.1, 0.1)));
    glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "material.ambient"), 1, value_ptr(planets->ka));
    glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "material.diffuse"), 1, value_ptr(planets->kd));
    glProgramUniform3fv(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "material.specular"), 1, value_ptr(planets->ks));
    glProgramUniform1f(shader, glGetProgramResourceLocation(shader, GL_UNIFORM, "material.shininess"), planets->ns);
}