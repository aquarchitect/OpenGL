#ifdef GL_ES
precision highp float;
#endif

const vec2 GRAVITY = vec2(0.0, -0.5);
const vec2 WIND = vec2(0.0);
const float RESTITUTION = 0.2;

uniform highp sampler2D uPositions;
uniform highp sampler2D uVelocities;
uniform highp sampler2D uObstacles;

uniform vec2 uResolution;
uniform int uMode;
uniform float uRandom;

varying vec2 vQuad;

vec2 encode(float value) {
    vec2 channels = fract(vec2(1.0, 255.0) * value);
    channels -= channels.yy * vec2(1.0/255.0, 0.0);
    return channels;
}

float decode(vec2 channels) {
    return dot(channels, vec2(1.0, 1.0/255.0));
}

void updatePosition(inout vec2 position, vec2 velocity, vec2 obstacle, float random) {
    position += velocity + WIND;

    if (position.y <= 0.0 || position.x <= 0.0 || position.x >= uResolution.x) {
        position.x = abs(mod(position.x + 100.0 * random, uResolution.x));
        position.y += uResolution.y;
    }

    if (length(obstacle) != 0.0) {
        position -= velocity;
        position += 2.0 * obstacle - 1.0;
    }
}

void updateVelocity(vec2 position, inout vec2 velocity, vec2 obstacle, float random) {
    velocity += GRAVITY;

    if (position.y + velocity.y < -1.0) {
        velocity.x += random / 8.0;
        velocity.y = -2.5;
    }

    if (length(obstacle) != 0.0) {
        if (length(velocity) < 0.5) {
            velocity = (2.0 * obstacle - 1.0);
        } else {
            velocity = reflect(velocity, 2.0 * obstacle - 1.0) * RESTITUTION;
        }
    }
}

void main() {
    vec4 encodedPosition = texture2D(uPositions, vQuad);
    vec4 encodedVelocity = texture2D(uVelocities, vQuad);
    
    vec2 position = vec2(decode(encodedPosition.rg), decode(encodedPosition.ba));
    vec2 velocity = vec2(decode(encodedVelocity.rg), decode(encodedVelocity.ba)) * 2.0 - 1.0;
    vec2 obstacle = texture2D(uObstacles, position).xy;
    
    if (uMode == 0) {
        position *= uResolution;
        velocity *= uResolution;
        updatePosition(position, velocity, obstacle, uRandom * 2.0 - 1.0);
        position /= uResolution;
        
        gl_FragColor = vec4(encode(position.x), encode(position.y));
    } else if (uMode == 1) {
        position *= uResolution;
        velocity *= uResolution;
        updateVelocity(position, velocity, obstacle, uRandom * 2.0 - 1.0);
        velocity = (velocity/uResolution + 1.0) / 2.0;
        
        gl_FragColor = vec4(encode(velocity.x), encode(velocity.y));
    } else if (uMode == 2) {
        velocity = (velocity/1000.0 + 1.0) / 2.0;
        
        gl_FragColor = vec4(encode(velocity.x), encode(velocity.y));
    } else {
        discard;
    }
}
