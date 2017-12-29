#ifdef GL_ES
precision highp float;
#endif

uniform vec2 uResolution;

uniform sampler2D uPositions;
uniform sampler2D uVelocities;

attribute vec2 aTexCoord;
varying vec2 vVelocity;

float decode(vec2 channels) {
    return dot(channels, vec2(1.0, 1.0/255.0));
}

void main() {
    vec4 encodedPosition = texture2D(uPositions, aTexCoord);
    vec4 encodedVelocity = texture2D(uVelocities, aTexCoord);
    
    vec2 position = vec2(decode(encodedPosition.rg), decode(encodedPosition.ba)) * 2.0 - 1.0;
    vec2 velocity = vec2(decode(encodedVelocity.rg), decode(encodedVelocity.ba));
    
    gl_PointSize = 50.0;
    gl_Position = vec4(position, 0.0, 1.0);
    
    vVelocity = velocity;
}
