precision mediump float;
varying vec2 v_uv;
varying vec3 v_pos;
uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;

uniform float u_time;
uniform float u_DispMax;
void main()
{
vec2 disp = texture2D(u_texture_2, vec2(v_uv.x + u_time, v_uv.y)).rg;
vec2 offset = (disp * 2.0 - vec2(1.0)) * u_DispMax;
vec2 v_uv_displaced = v_uv + offset;

vec4 c_fire = texture2D(u_texture_0, v_uv_displaced); 
vec4 mask_color = texture2D(u_texture_1, v_uv);
c_fire.a = c_fire.a * mask_color.r;

gl_FragColor = c_fire;
}
