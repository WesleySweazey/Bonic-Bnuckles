#version 120

attribute vec3 a_Position;

varying vec2 v_UV;
varying vec2 v_BlurTextureCoords[11];
uniform float u_targetHeight;

void main()
{
     float pixelSize = 1.0/u_targetHeight;
     vec2 centerTexCoord = a_Position.xy * 0.5 + 0.5;
     for(int i = -5; i <= 5; i++)
     {
        v_BlurTextureCoords[i+5] = centerTexCoord + vec2(0.0, pixelSize * i);
     }

     gl_Position = vec4(a_Position, 1);
}