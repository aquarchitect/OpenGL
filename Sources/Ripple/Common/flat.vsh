#ifdef GL_ES
precision highp float;
#endif

attribute vec2 aPosition;
varying vec2 aTexCoord;

void main() {
    gl_Position = vec4(aPosition, 0.0, 1.0);
    aTexCoord = aPosition;
}
