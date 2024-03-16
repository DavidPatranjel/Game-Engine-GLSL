precision mediump float;
varying vec3 v_coord;
uniform samplerCube u_texture_0;
void main()
{
vec4 color = textureCube(u_texture_0, v_coord);
gl_FragColor = color;
}
