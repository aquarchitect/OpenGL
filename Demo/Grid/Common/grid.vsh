#ifdef GL_ES
precision highp float;
#endif

uniform float uTime;

#if __VERSION__ >= 140
in vec2 aPoint;
out vec3 vColor;
#else
attribute vec2 aPoint;
varying vec3 vColor;
#endif

void main() {
    gl_PointSize = 10.0;
    gl_Position = vec4(vec3(0.0), 1.0);
    
    vColor = vec3(1.0, 0.0, 0.0);
}
