#ifdef GL_ES
precision highp float;
#endif

uniform mat4 uProjection;
uniform mat4 uTransformation;

#if __VERSION__ >= 140
in vec3 aPosition;
in vec4 aColor;

out vec4 vColor;
#else
attribute vec3 aPosition;
attribute vec4 aColor;

varying vec4 vColor;
#endif

void main() {
    vColor = aColor;
    gl_Position = uProjection * uTransformation * vec4(aPosition, 1.0);
}
