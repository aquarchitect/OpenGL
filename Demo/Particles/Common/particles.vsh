#ifdef GL_ES
precision highp float;
#endif

const float BASE = 255.0;
const float OFFSET = BASE * BASE / 2.0;

uniform sampler2D uPosition;
uniform vec2 uScale;
uniform vec2 uGrid;
uniform vec2 uResolution;

#if __VERSION__ >= 140
in vec2 aIndex;
#else
attribute vec2 aIndex;
#endif

float decode(vec2 channels, float scale) {
    return (dot(channels, vec2(BASE, BASE * BASE)) - OFFSET) / scale;
}

void main() {
    vec4 encodedPosition = texture2D(uPosition, aIndex / uGrid);
    
    float px = decode(encodedPosition.rg, uScale.x);
    float py = decode(encodedPosition.ba, uScale.x);
    
    vec2 p = vec2(px, py) / uResolution * 2.0 - 1.0;
    
    gl_PointSize = 10.0;
    gl_Position = vec4(p, 0.0, 1.0);
}
