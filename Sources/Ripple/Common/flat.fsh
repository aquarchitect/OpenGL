#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D uTexture;
uniform float uTime;

varying vec2 aTexCoord;

void main() {
    vec2 uv = normalize(aTexCoord) * cos(length(aTexCoord*10.0) - uTime);
    gl_FragColor = vec4(texture2D(uTexture, uv).xyz, 1.0);
}

