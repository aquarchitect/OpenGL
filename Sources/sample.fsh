varying lowp vec4 v_Color;
varying lowp vec2 v_FacadeTexCoord;

uniform sampler2D u_FacadeTexture;

void main() {
    gl_FragColor = v_Color * texture2D(u_FacadeTexture, v_FacadeTexCoord);
}
