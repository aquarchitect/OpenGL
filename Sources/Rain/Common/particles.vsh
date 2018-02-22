#ifdef GL_ES
precision highp float;
#endif

attribute vec2 aQuad;
varying vec2 vQuad;

void main() {
    gl_Position = vec4(aQuad, 0.0, 1.0);
    vQuad = (aQuad + 1.0) / 2.0;
}
