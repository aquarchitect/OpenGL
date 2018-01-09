#ifdef GL_ES
precision highp float;
#endif

const vec4 blue = vec4(0.0, 0.0, 1.0, 1.0);

void main() {
    vec2 point = gl_PointCoord * 2.0 - 1.0;

    if (length(point) <= 1.0) {
        gl_FragColor = blue;
    } else {
        discard;
    }
}
