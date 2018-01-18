#ifdef GL_ES
precision highp float;
#endif

attribute vec2 aPosition;

void main() {
    gl_PointSize = 100.0;
    gl_Position = vec4(aPosition * 2.0 - 1.0, 0.0, 1.0);
}
