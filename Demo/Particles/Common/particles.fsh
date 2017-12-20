#ifdef GL_ES
precision highp float;
#endif

varying vec2 vVelocity;
varying vec4 vColor;

void main() {
    vec2 point = gl_PointCoord * 2.0 - 1.0;
    float alpha = smoothstep(0.5, 1.0, length(point));
    
    gl_FragColor = pow(mix(vColor, vec4(0.0), alpha), vec4(length(vVelocity)/3.0));
}
