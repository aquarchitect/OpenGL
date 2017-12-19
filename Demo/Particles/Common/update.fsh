#ifdef GL_ES
precision highp float;
#endif

#if __VERSION__ >= 140
in vec2 vPosition;
#else
varying vec2 vPosition;
#endif

void main() {
    gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
