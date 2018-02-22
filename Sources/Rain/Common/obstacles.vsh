#ifdef GL_ES
precision highp float;
#endif

attribute vec2 aQuad;

void main() {
    gl_PointSize = 100.0;
    gl_Position = vec4(aQuad * 2.0 - 1.0, 0.0, 1.0);
}
