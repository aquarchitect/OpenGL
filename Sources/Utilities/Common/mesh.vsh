#ifdef GL_ES
precision highp float;
#endif

uniform mat4 uModel;
uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

varying vec2 vTexCoord;
varying vec3 vNormal;

void main() {
    mat4 transformation = uView * uWorld * uModel;
    gl_Position = uProjection * transformation * vec4(aPosition, 1.0);
    
    // pass to fragment shader
    vTexCoord = aTexCoord;
    vNormal = (transformation * vec4(aNormal, 0.0)).xyz;
}
