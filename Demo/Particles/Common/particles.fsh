#ifdef GL_ES
precision highp float;
#endif

const vec4 RED = vec4(1.0, 0.0, 0.0, 1.0);

varying vec2 vVelocity;

void main() {
    vec2 point = gl_PointCoord * 2.0 - 1.0;
    float alpha = smoothstep(0.8, 1.0, length(point));
    vec4 color = mix(RED, vec4(0.0), length(vVelocity) * 20.0);
    
    gl_FragColor = mix(color, vec4(0.0), alpha);
}
