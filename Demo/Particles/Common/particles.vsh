#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D uPosition;

uniform vec2 uGrid;
uniform vec2 uResolution;

attribute vec2 aTexCoord;
varying vec4 vColor;

float decode(vec2 channels) {
    return dot(channels, vec2(1.0, 1.0/255.0));
}

void main() {
    vec4 data = texture2D(uPosition, aTexCoord);
    
    vec2 position = vec2(decode(data.rg), decode(data.ba)) * 2.0 - 1.0;
    
    gl_PointSize = 50.0;
    gl_Position = vec4(position, 0.0, 1.0);
    
    vColor = data;
}
