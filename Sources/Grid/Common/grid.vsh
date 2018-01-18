#ifdef GL_ES
precision highp float;
#endif

uniform vec2 uResolution;
uniform vec2 uGrid;
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

void main() {
    // index
    float xi = mod(aIndex, uGrid.x);
    float yi = floor(aIndex / uGrid.x);
    
    // distance
    float xd = 1.0 / (uGrid.x - 1.0);
    float yd = 1.0 / (uGrid.y - 1.0);
    
    // offset
    float xo = sin(uTime + 3.0 * yi * yd) * 0.1;
    float yo = sin(uTime + 4.0 * xi * xd) * 0.1;
    float so = sin(uTime + xi * xd + yi * yd) * 15.0;
    
    mat4 m = mat4(1.0);
    m[3] = vec4(xi * xd, yi * yd, 0.0, 1.0);
    m[3] *= vec4(2.0, 2.0, 1.0, 1.0);   // scaling
    m[3] += vec4(-1.0, -1.0, 0.0, 0.0); // translating
    m[3] += vec4(xo, yo, 0.0, 0.0);     // translating
    m[3] *= vec4(0.7, 0.7, 0.0, 1.0);   // scaling
    
    gl_Position = m * vec4(aPoint, 0.0, 1.0);
    gl_PointSize = 15.0 + so;
    
    // color
    float r = sin(uTime + xi * xd);
    float g = sin(uTime + yi * yd);
    float b = sin(uTime/2.0);
    vColor = vec3(r, g, b);
}
