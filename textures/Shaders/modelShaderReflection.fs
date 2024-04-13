precision mediump float;
varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 v_normW;
uniform sampler2D u_texture_0;
uniform samplerCube u_texture_1;
uniform float u_r;
uniform float u_R;
uniform vec3 u_fog_color;
uniform vec3 u_pos_camera;
uniform float u_alpha_reflection;
void main()
{
vec4 object_color = texture2D(u_texture_0, v_uv); 

if(object_color.a < 0.2)
	discard;

vec3 vectCam = u_pos_camera - v_pos;
vec3 dirReflect = normalize(reflect(normalize(vectCam), normalize(v_normW)));
vec4 texture_color = textureCube(u_texture_1, dirReflect);
vec4 c_final = texture_color * u_alpha_reflection + object_color * (1.0 - u_alpha_reflection);
c_final.a = 1.0;

float d = distance(v_pos, u_pos_camera);  
float alpha = clamp((d-u_r)/(u_R-u_r), 0.0, 1.0);
vec4 fog_color = vec4(u_fog_color, 1.0);
vec4 color=alpha * fog_color + (1.0-alpha) * c_final;

gl_FragColor = color;
}
