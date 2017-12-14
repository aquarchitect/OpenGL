#ifdef GL_ES
precision highp float;
#endif

struct Light {
    vec3 color;
    vec3 direction;
    
    float ambientIntensity;
    float diffuseIntensity;
};

const Light light = Light(vec3(1.0), vec3(0.0, 0.0, -1.0), 0.1, 0.8);

uniform sampler2D uTexture;
uniform mat4 uView;
uniform mat4 uWorld;

#if __VERSION__ >= 140
in vec4 vColor;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 fragColor;
#else
varying vec4 vColor;
varying vec2 vTexCoord;
varying vec3 vNormal;
#endif

void main() {
    vec3 normal = normalize(vNormal);
    vec3 direction = normalize((uView * uWorld * vec4(light.direction, 0.0)).xyz);
    
    vec3 ambientColor = light.color * light.ambientIntensity;
    vec3 diffuseColor = light.color * light.diffuseIntensity * max(-dot(normal, direction), 0.0);
    
#if __VERSION__ >= 140
    fragColor = texture(uTexture, vTexCoord) * vec4(ambientColor + diffuseColor, 1.0);
#else
    gl_FragColor = texture2D(uTexture, vTexCoord) * vec4(ambientColor + diffuseColor, 1.0);
#endif
}
