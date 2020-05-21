#version 120

uniform sampler2D u_Texture;

varying vec2 v_UV;

void main()
{
    vec4 Color = texture2D( u_Texture, v_UV );
	vec3 BW = vec3(0.299, 0.587, 0.114);
	gl_FragColor = vec4( vec3(dot( Color.rgb, BW)), Color.a);
}
