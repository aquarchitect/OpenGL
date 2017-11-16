uniform highp mat4 u_Transform;

attribute vec4 a_Position;
attribute vec4 a_Color;

varying lowp vec4 v_Color;

void main() {
    v_Color = a_Color;
    gl_Position = u_Transform * a_Position;
}

