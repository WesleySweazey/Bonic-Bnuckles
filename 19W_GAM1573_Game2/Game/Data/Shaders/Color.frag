#version 120
uniform sampler2D u_Texture;

uniform vec3 u_LightColor;
uniform vec3 u_MaterialColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPos;

varying vec2 v_UV;
varying vec3 v_SurfacePosition;
varying vec3 v_SurfaceNormal;

void main()
{  
    vec3 UnNormalizedDirectionVector = u_LightPosition - v_SurfacePosition;
	vec3 unNormalizedSurfacePosFromCamaeraPos = u_CameraPos - v_SurfacePosition;

	vec3 DirectionVector = normalize(UnNormalizedDirectionVector);
	vec3 SurfacePosFromCamaeraPos = normalize(unNormalizedSurfacePosFromCamaeraPos);
	vec3 SimulatedLightVector = normalize(DirectionVector + SurfacePosFromCamaeraPos);
	vec3 NormalizedSurfaceNormal = normalize(v_SurfaceNormal);

	float dist = length(UnNormalizedDirectionVector);

	float diffusePercent = dot(NormalizedSurfaceNormal, DirectionVector);
	max(0, diffusePercent);
	float specPercent = dot(SimulatedLightVector, normalize(v_SurfaceNormal));
	max(0, specPercent);

	float range = 32;
	float FallOff = 0.5;

	specPercent = pow(specPercent, range);
	float attenuation = 1 - pow(dist / range, FallOff);
	max(0, attenuation);

	vec3 diffuse = ((u_MaterialColor * u_LightColor) * diffusePercent) * attenuation;
	vec3 specular = (u_LightColor * specPercent) * attenuation;
	vec3 finalColor = diffuse+ specular;
	gl_FragColor =  vec4(finalColor, 1);
	//gl_FragColor =  texture2D(u_Texture,v_UV) * vec4(finalColor, 1);
}
