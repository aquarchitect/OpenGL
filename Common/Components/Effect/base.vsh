#if __VERSION__ >= 140
in vec2 a_Position;
#else
attribute vec2 a_Position;
#endif

void main() {
    gl_Position = vec4(a_Position, 0.0, 1.0);
}
