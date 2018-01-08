#ifdef GL_ES
precision highp float;
#endif

const vec2 gravity = vec2(0.0, -0.5);
const vec2 wind = vec2(0.0);

uniform sampler2D uPositions;
uniform sampler2D uVelocities;

uniform vec2 uResolution;
uniform int uMode;

varying vec2 vPosition;

vec2 encode(float value) {
    vec2 channels = fract(vec2(1.0, 255.0) * value);
    channels -= channels.yy * vec2(1.0/255.0, 0.0);
    return channels;
}

float decode(vec2 channels) {
    return dot(channels, vec2(1.0, 1.0/255.0));
}

void updatePosition(inout vec2 position, vec2 velocity) {
    position += velocity + wind;
    
    if (position.y <= 0.0) {
        position.y += uResolution.y;
    }
}

void updateVelocity(vec2 position, inout vec2 velocity) {
    velocity += gravity;
    
    if (position.y + velocity.y < 0.0) {
        velocity.y = 0.0;
    }
}

void main() {
    vec4 encodedPosition = texture2D(uPositions, vPosition);
    vec4 encodedVelocity = texture2D(uVelocities, vPosition);
    
    vec2 position = vec2(decode(encodedPosition.rg), decode(encodedPosition.ba)) * uResolution;
    vec2 velocity = vec2(decode(encodedVelocity.rg), decode(encodedVelocity.ba)) * 2.0 - 1.0;
    
    if (uMode == 0) {
        velocity *= uResolution;
        updatePosition(position, velocity);
        position /= uResolution;
        
        gl_FragColor = vec4(encode(position.x), encode(position.y));
    } else if (uMode == 1) {
        velocity *= uResolution;
        updateVelocity(position, velocity);
        velocity = (velocity/uResolution + 1.0) / 2.0;
        
        gl_FragColor = vec4(encode(velocity.x), encode(velocity.y));
    } else if (uMode == 2) {
        velocity = (velocity/1000.0 + 1.0) / 2.0;
        
        gl_FragColor = vec4(encode(velocity.x), encode(velocity.y));
    } else {
        discard;
    }
}
