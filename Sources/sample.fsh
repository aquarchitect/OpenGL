uniform sampler2D u_FacadeTexture;

varying lowp vec4 v_Color;
varying lowp vec2 v_FacadeTexCoord;

void main() {
    gl_FragColor = texture2D(u_FacadeTexture, v_FacadeTexCoord);
}
