#version 120

uniform sampler2D u_Texture;

varying vec2 v_UV;
varying vec2 v_BlurTextureCoords[11];

void main()
{
    vec4 FinalColor = vec4(0.0f,0.0f,0.0f,0.0f);
	FinalColor += texture2D(u_Texture, v_BlurTextureCoords[0]) * 0.0093;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[1]) * 0.028002;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[2]) * 0.065984;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[3]) * 0.121703;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[4]) * 0.175713;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[5]) * 0.198596;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[6]) * 0.175713;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[7]) * 0.121703;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[8]) * 0.065984;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[9]) * 0.028002;
    FinalColor += texture2D(u_Texture, v_BlurTextureCoords[10]) * 0.0093;

	gl_FragColor = FinalColor;
}
