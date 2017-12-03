#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D uTexture;

#if __VERSION__ >= 140
in vec4 vColor;
in vec2 vTexCoord;

out vec4 fragColor;
#else
varying vec4 vColor;
varying vec2 vTexCoord;
#endif

void main() {    
#if __VERSION__ >= 140
    fragColor = texture(uTexture, vTexCoord);
#else
    gl_FragColor = texture2D(uTexture, vTexCoord);
#endif
}
