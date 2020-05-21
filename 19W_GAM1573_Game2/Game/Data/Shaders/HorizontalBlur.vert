#version 120

attribute vec3 a_Position;

varying vec2 v_UV;
varying vec2 v_BlurTextureCoords[11];
uniform float u_targetWidth;

void main()
{
     float pixelSize = 1.0/u_targetWidth;
     vec2 centerTexCoord = a_Position.xy * 0.5 + 0.5;
     for(int i = -5; i <= 5; i++)
     {
        v_BlurTextureCoords[i+5] = centerTexCoord + vec2(pixelSize * i, 0.0);
     }

	  gl_Position = vec4(a_Position, 1);
}
