attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec3 a_normv;
varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 N;
uniform mat4 uMVP;
uniform mat4 uM;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = uMVP * posL;
	v_uv = a_uv;

	vec4 posNoP = uM * posL;
	v_pos = posNoP.xyz;

	N = a_normv;
}
