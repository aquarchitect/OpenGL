#ifdef GL_ES
precision highp float;
#endif

uniform mat4 u_Transformation;
uniform mat4 u_Projection;

#if __VERSION__ >= 140
in vec4 a_Position;
in vec4 a_Color;
in vec2 a_TexCoord;
in vec3 a_Normal;

out vec4 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_Position;
#else
attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_TexCoord;
attribute vec3 a_Normal;

varying vec4 v_Color;
varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_Position;
#endif

void main() {
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_Normal = (u_Transformation * vec4(a_Normal, 0.0)).xyz;
    v_Position = (u_Transformation * a_Position).xyz;
    
    gl_Position = u_Projection * u_Transformation * a_Position;
}
