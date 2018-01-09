#ifdef GL_ES
precision highp float;
#endif

attribute vec2 aPosition;
varying vec2 vPosition;

void main() {
    gl_Position = vec4(aPosition, 0.0, 1.0);
    vPosition = (aPosition + 1.0) / 2.0;
}
