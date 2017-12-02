#ifdef GL_ES
precision highp float;
#endif

uniform mat4 uProjection;
uniform mat4 uTransformation;

#if __VERSION__ >= 140
in vec3 aPosition;
in vec4 aColor;
in vec2 aTexCoord;

out vec4 vColor;
out vec2 vTexCoord;
#else
attribute vec3 aPosition;
attribute vec4 aColor;
attribute vec2 aTexCoord;

varying vec4 vColor;
varying vec2 vTexCoord;
#endif

void main() {
    // pass to fragment shader
    vColor = aColor;
    vTexCoord = aTexCoord;
    
    gl_Position = uProjection * uTransformation * vec4(aPosition, 1.0);
}
