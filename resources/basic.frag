#version 330

uniform float uTime;

out vec4 oColor;

vec2 hash2(vec2 uv)
{
    uv = vec2(dot(uv, vec2(12.9898, 78.233)),
              dot(uv, vec2(139.234, 98.187)));

    return -1.0 + 2.0 * fract( sin( uv ) * 43758.5453123);
}

vec2 quinticHermine(vec2 x)
{
    return x * x * x * (x * (x * 6.0 - 15.0) + 10.0);
}

float noise(vec2 uv)
{
    vec2 i = floor(uv);
    vec2 f = fract(uv);

    vec2 a = hash2(i + vec2(0.0, 0.0));
    vec2 b = hash2(i + vec2(1.0, 0.0));
    vec2 c = hash2(i + vec2(0.0, 1.0));
    vec2 d = hash2(i + vec2(1.0, 1.0));
    vec2 u = quinticHermine(f);

    float val = mix( mix( dot( a, f - vec2(0.0,0.0) ),
                          dot( b, f - vec2(1.0,0.0) ), u.x),
                     mix( dot( c, f - vec2(0.0,1.0) ),
                          dot( d, f - vec2(1.0,1.0) ), u.x), u.y);
    return val * 0.5 + 0.5;
}

void main()
{
  vec2 uv = gl_FragCoord.xy / vec2(600.0, 800.0);
  float n = noise(uv * 40.0 + uTime);
  oColor = vec4(vec3(n), 1.0);
}
