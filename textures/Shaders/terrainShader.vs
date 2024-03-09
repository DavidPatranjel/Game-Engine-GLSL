attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv2;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform vec3 u_height;
uniform mat4 uMVP;
uniform sampler2D u_texture_3;
void main()
{
vec4 c_blend = texture2D(u_texture_3, a_uv2);

vec3 pos_nou = a_posL;
pos_nou.y += c_blend.r*u_height.r+c_blend.g*u_height.g+c_blend.b*u_height.b;
vec4 posL = vec4(pos_nou, 1.0);
gl_Position = uMVP * posL;
v_uv = a_uv;
v_uv2 = a_uv2;
}
