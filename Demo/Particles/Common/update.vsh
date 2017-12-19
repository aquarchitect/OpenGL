#ifdef GL_ES
precision highp float;
#endif

#if __VERSION__ >= 140
in vec2 aPosition;
out vec2 vPosition;
#else
attribute vec2 aPosition;
varying vec2 vPosition;
#endif

void main() {
    gl_Position = vec4(aPosition, 0.0, 1.0);
    vPosition = (aPosition + 1.0) * 2.0;
}
