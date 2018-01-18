#ifdef GL_ES
precision highp float;
#endif

const vec4 BLUE = vec4(0.0, 0.0, 1.0, 1.0);

uniform int uMode;

void main() {
    vec2 point = gl_PointCoord * 2.0 - 1.0;

    if (length(point) <= 1.0) {
        if (uMode == 0) {
            vec2 norm = normalize(point * vec2(1.0, -1.0));
            gl_FragColor = vec4((norm + 1.0) / 2.0, 0.0, 1.0);
        } else {
            gl_FragColor = BLUE;
        }
    } else {
        discard;
    }
}
