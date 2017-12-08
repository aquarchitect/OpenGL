#ifdef GL_ES
precision highp float;
#endif

#if __VERSION__ >= 140
in vec3 vColor;

out vec4 fragColor
#else
varying vec3 vColor;
#endif

void main() {
#if __VERSION__ >= 140
    fragColor = vec4(1.0);
#else
    gl_FragColor = vec4(1.0);
#endif
}
