#ifdef GL_ES
precision highp float;
#endif

uniform mat4 uModel;
uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;

#if __VERSION__ >= 140
in vec3 aPosition;
in vec4 aColor;
in vec2 aTexCoord;
in vec3 aNormal;

out vec4 vColor;
out vec2 vTexCoord;
out vec3 vNormal;
#else
attribute vec3 aPosition;
attribute vec4 aColor;
attribute vec2 aTexCoord;
attribute vec3 aNormal;

varying vec4 vColor;
varying vec2 vTexCoord;
varying vec3 vNormal;
#endif

void main() {
    gl_Position = uProjection * uView * uWorld * uModel * vec4(aPosition, 1.0);
    
    // pass to fragment shader
    vColor = aColor;
    vTexCoord = aTexCoord;
    vNormal = aNormal;
}
