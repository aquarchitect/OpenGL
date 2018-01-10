#ifdef GL_ES
precision highp float;
#endif

const vec4 RED = vec4(1.0, 0.0, 0.0, 1.0);

varying vec2 vVelocity;

void main() {
    vec2 point = gl_PointCoord * 2.0 - 1.0;
    float alpha = smoothstep(0.8, 1.0, length(point));
    
    gl_FragColor = pow(mix(RED, vec4(0.0), alpha), vec4(length(vVelocity)/10.0));
}
