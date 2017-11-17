struct Light {
    lowp vec3 color;
    lowp vec3 direction;
    lowp float ambientIntensity;
    lowp float diffuseIntensity;
};

uniform Light u_Light;
uniform sampler2D u_Texture;

varying lowp vec4 v_Color;
varying lowp vec2 v_TexCoord;
varying lowp vec3 v_Normal;

void main() {
    lowp vec3 normal = normalize(v_Normal);
    lowp vec3 direction = normalize(u_Light.direction);
    
    lowp vec3 ambientColor = u_Light.color * u_Light.ambientIntensity;
    lowp vec3 diffuseColor = u_Light.color * u_Light.diffuseIntensity * max(-dot(normal, direction), 0.0);
    
    gl_FragColor = texture2D(u_Texture, v_TexCoord) * vec4(ambientColor + diffuseColor, 1.0);
}
