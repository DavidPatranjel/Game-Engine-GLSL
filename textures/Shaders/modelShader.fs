precision mediump float;
#define M_HALF_PI 1.570796;
varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 N;

uniform sampler2D u_texture_0;
uniform float u_r;
uniform float u_R;
uniform vec3 u_fog_color;
uniform vec3 u_pos_camera;

uniform int type; //0-point 1-directional 2-spot
uniform vec3 u_pos_light;
uniform vec3 u_direction_light;
uniform float u_angle;
uniform vec3 c_lightDiff;
uniform vec3 c_lightSpec;
uniform float SpecPower;
uniform vec3 c_amb;
uniform float ratio;	

void main()
{
	vec4 object_color = texture2D(u_texture_0, v_uv); 

	if(object_color.a < 0.2)
		discard;

	vec3 E = normalize(u_pos_camera - v_pos);
	vec3 L;
	if(type == 0 || type == 2)
	{
		L = normalize(v_pos - u_pos_light);
	}
	else if(type == 1)
	{
		L = normalize(u_direction_light);
	}
	vec3 R=normalize(reflect(L,N));
	vec3 N_norm = normalize(N);

	float cos_angle_obj, cos_angle_light;
	float attenuation = M_HALF_PI;
	if(type == 2)
	{
		float cos_angle_obj = dot(L, normalize(u_direction_light));
		float angle_obj = acos(cos_angle_obj);	
		if(angle_obj <= u_angle)
		{
			attenuation = angle_obj *  M_HALF_PI;
			attenuation = attenuation / u_angle;
		}
	}

	vec4 colorAmb = vec4(object_color.rgb * c_amb, object_color.a);
	vec4 Cdiff = object_color*vec4(c_lightDiff, 1.0) *max(dot(N_norm,-L), 0.0);
	vec4 Cspec = vec4(c_lightSpec * pow(max(dot(R,E), 0.0), SpecPower), 1.0);

	vec4 c_final = ratio * colorAmb;
	if(type == 2)
	 	c_final = c_final + cos(attenuation) * (1.0 - ratio) * (0.6 * Cdiff + 0.9*Cspec);
	else
		c_final = c_final +  (1.0 - ratio) * (0.6 * Cdiff + 0.9*Cspec);


	float d = distance(v_pos, u_pos_camera);  
	float alpha = clamp((d-u_r)/(u_R-u_r), 0.0, 1.0);
	vec4 fog_color = vec4(u_fog_color, 1.0);
	vec4 color=alpha * fog_color + (1.0-alpha) * c_final;
	gl_FragColor = color;
}
