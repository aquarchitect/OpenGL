uniform highp mat4 u_Transformation;
uniform highp mat4 u_Projection;

attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_TexCoord;
attribute vec3 a_Normal;

varying lowp vec4 v_Color;
varying lowp vec2 v_TexCoord;
varying lowp vec3 v_Normal;
varying lowp vec3 v_Position;

void main() {
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_Normal = (u_Transformation * vec4(a_Normal, 0.0)).xyz;
    v_Position = (u_Transformation * a_Position).xyz;
    
    gl_Position = u_Projection * u_Transformation * a_Position;
}

