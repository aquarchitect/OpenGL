#ifdef GL_ES
precision highp float;
#endif

struct light {
    vec3 color;
    vec3 direction;
    
    float ambient;
    float diffuse;
};

uniform sampler2D uTexture;
uniform mat4 uView;
uniform mat4 uWorld;
uniform light uLight;

varying vec2 vTexCoord;
varying vec3 vNormal;

void main() {
    vec3 normal = normalize(vNormal);
    vec3 direction = normalize((uView * uWorld * vec4(uLight.direction, 0.0)).xyz);
    
    vec3 ambientColor = uLight.color * uLight.ambient;
    vec3 diffuseColor = uLight.color * uLight.diffuse * max(-dot(normal, direction), 0.0);
    
    gl_FragColor = texture2D(uTexture, vTexCoord) * vec4(ambientColor + diffuseColor, 1.0);
}
