#ifdef GL_ES
precision highp float;
#endif

struct Light {
    vec3 color;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
} u_Light;

struct Material {
    float shininess;
    float specularIntensity;
};

const Light u_Light = Light(vec3(1.0,1.0,1.0), vec3(1.0,1.0,-1.0), 0.1, 0.7);
const Material u_Material = Material(7.0, 2.0);

uniform sampler2D u_Texture;

#if __VERSION__ >= 140
in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Position;
out vec4 fragColor;
#else
varying vec4 v_Color;
varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_Position;
#endif

void main() {
    vec3 normal = normalize(v_Normal);
    vec3 direction = normalize(u_Light.direction);
    vec3 eye = normalize(v_Position);
    vec3 reflection = reflect(u_Light.direction, normal);
    
    vec3 ambientColor = u_Light.color * u_Light.ambientIntensity;
    vec3 diffuseColor = u_Light.color * u_Light.diffuseIntensity * max(-dot(normal, direction), 0.0);
    vec3 specularColor = u_Light.color * u_Material.specularIntensity * pow(max(0.0, -dot(eye, reflection)), u_Material.shininess);
    vec4 lightColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
    
#if __VERSION__ >= 140
    fraColor = texture(u_Texture, v_TexCoord) * lightColor;
#else
    gl_FragColor = texture2D(u_Texture, v_TexCoord) * lightColor;
#endif
}
