uniform highp mat4 u_Transformation;
uniform highp mat4 u_Projection;

attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_FacadeTexCoord;

varying lowp vec4 v_Color;
varying lowp vec2 v_FacadeTexCoord;

void main() {
    v_Color = a_Color;
    v_FacadeTexCoord = a_FacadeTexCoord;
    gl_Position = u_Projection * u_Transformation * a_Position;
}

