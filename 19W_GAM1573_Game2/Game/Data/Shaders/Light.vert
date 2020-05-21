#version 120

attribute vec3 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;
attribute vec3 a_Normal;

//uniform vec4 u_LightColor;
//uniform vec4 u_MaterialColor;

uniform mat4 u_WorldMatrix;
uniform mat4 u_RotationMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform vec3 u_CameraPos;
//uniform vec3 u_LightPos[];

varying vec2 v_UV;
varying vec3 v_SurfaceWorldPos;
varying vec3 v_SurfaceNormal;
//varying vec3 v_LightPos;

void main()
{
//v_LightPos = vec3(0,2.0f,0);

//v_SurfaceNormal = vec3(0,1.0f,0);
vec4 normalTemp = vec4(a_Normal.x,a_Normal.y,a_Normal.z,0.0f);

	// Store object space position.
	vec4 objectPos = vec4(a_Position,1);

	//Calculate the surface normal
	vec4 surfaceNormalTemp = u_RotationMatrix * normalTemp;
	v_SurfaceNormal.xyz = surfaceNormalTemp.xyz;

	// Calculate world space position.
	vec4 worldPos = u_WorldMatrix * objectPos;

	//Calculate the surface pos
	v_SurfaceWorldPos = worldPos.xyz;

	// Calculate view space position.
	vec4 viewPos = u_ViewMatrix * worldPos;

	// Calculate clip space position.
	vec4 clipPos = u_ProjectionMatrix * viewPos;

	// Store final position in gl_Position
    gl_Position = clipPos;

	v_UV = a_UV;
}
