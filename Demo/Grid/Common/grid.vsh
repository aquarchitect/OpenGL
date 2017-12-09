#ifdef GL_ES
precision highp float;
#endif

uniform vec2 uResolution;
uniform vec2 uGridSize;
uniform float uTime;

#if __VERSION__ >= 140
in vec2 aPoint;
in float aIndex;
out vec3 vColor;
#else
attribute vec2 aPoint;
attribute float aIndex;
varying vec3 vColor;
#endif

mat4 translation(float vertexID) {
    float ri = floor(vertexID / uGridSize.x);  // row index
    float ci = mod(vertexID, uGridSize.x);     // column index
    
    float rd = 2.0 / (uGridSize.y - 1.0);   // row distance
    float cd = 2.0 / (uGridSize.x - 1.0);   // column distance
    
    mat4 t = mat4(1.0);
    t[3] = vec4(ci * cd, ri * rd, 0.0, 1.0);
    t[3] += vec4(-1.0, -1.0, 0.0, 0.0); // translate to lower left corner
    return t;
}

void main() {    
    gl_PointSize = 10.0;
    gl_Position = translation(aIndex) * vec4(aPoint, 0.0, 1.0);
    
    vColor = vec3(1.0, 0.0, 0.0);
}
