#ifdef GL_ES
precision highp float;
#endif

const vec4 color = vec4(0.0, 0.0, 1.0, 1.0);

uniform sampler2D uBackground;
uniform vec2 uResolution;

varying vec2 vPosition;

float get(vec2 offset) {
    vec2 p = vPosition + offset;
    return length((texture2D(uBackground, p).xy - 0.5) * 2.0);
}

const float DIAG     = 0.011344;
const float ADJACENT = 0.083820;
const float CENTER   = 0.619347;

void main() {
    float norm =
        get(vec2( 1.0, -1.0)) * DIAG +
        get(vec2( 1.0,  0.0)) * ADJACENT +
        get(vec2( 1.0,  1.0)) * DIAG +
        get(vec2( 0.0, -1.0)) * ADJACENT +
        get(vec2( 0.0,  0.0)) * CENTER +
        get(vec2( 0.0,  1.0)) * ADJACENT +
        get(vec2(-1.0, -1.0)) * DIAG +
        get(vec2(-1.0,  0.0)) * ADJACENT +
        get(vec2(-1.0,  1.0)) * DIAG;
    gl_FragColor = mix(vec4(0.0), color, norm);
}
