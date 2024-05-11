precision mediump float;
varying vec2 v_uv;
varying vec3 v_pos;
uniform sampler2D u_texture_0;
uniform float u_r;
uniform float u_R;
uniform vec3 u_fog_color;
uniform vec3 u_pos_camera;
void main()
{
vec4 object_color = texture2D(u_texture_0, v_uv); 

if(object_color.a < 0.2)
	discard;

float d = distance(v_pos, u_pos_camera);  
float alpha = clamp((d-u_r)/(u_R-u_r), 0.0, 1.0);
vec4 fog_color = vec4(u_fog_color, 1.0);
vec4 color=alpha * fog_color + (1.0-alpha) * object_color;
gl_FragColor = color;
}