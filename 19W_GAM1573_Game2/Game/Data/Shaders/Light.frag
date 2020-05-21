#version 120

struct Light
{
vec3 LightPos;
float LightRange;
float LightIntensity;
vec4 LightColor;
};

uniform sampler2D u_Texture;
uniform vec3 u_CameraPos;
uniform Light u_Lights[5];
uniform float u_MaterialShine;

varying vec2 v_UV;
varying vec3 v_SurfaceWorldPos;
varying vec3 v_SurfaceNormal;

vec4 LightMath(vec3 ligthPos,vec3 cameraPos, vec3 surfaceWorldPos, vec3 surfaceNormal ,vec4 lightColor, float lightRange, float lightIntensity, vec4 materialColor)
{
//Pixel To Light Vector
vec3 UnnormalizedVectorFromPixelToLight = ligthPos - surfaceWorldPos;
vec3 DirectionVectorPixelToLight = normalize(UnnormalizedVectorFromPixelToLight);
float distanceToLight = length(UnnormalizedVectorFromPixelToLight);

//Pixel To Camera Vector : Specular
vec3 UnnormalizedVectorFromPixelToCamera = cameraPos - surfaceWorldPos;
vec3 DirectionVectorPixelToCamera = normalize(UnnormalizedVectorFromPixelToCamera);

//Simulated Light Vector : Specular
vec3 UnnormalizedVectorSimulatedLight = DirectionVectorPixelToCamera + DirectionVectorPixelToLight;
vec3 DirectionVectorSimulatedLight = normalize(UnnormalizedVectorSimulatedLight);

float DiffusePercent = dot(DirectionVectorPixelToLight,v_SurfaceNormal);
DiffusePercent = max(0.0f, DiffusePercent);
float SpecularPercent = dot(DirectionVectorSimulatedLight,v_SurfaceNormal);
SpecularPercent = max(0.0f, SpecularPercent);
SpecularPercent = pow(SpecularPercent,u_MaterialShine);
float fallOff = max(0.0f, pow((1 -distanceToLight/lightRange),lightIntensity));

float finalPercent = DiffusePercent + SpecularPercent;

vec4 v_AmbientLightColor = lightColor * materialColor * 0.1;
vec4 v_DiffuseColor = lightColor * materialColor * DiffusePercent * fallOff;
vec4 v_SpecularColor = lightColor * SpecularPercent * fallOff;

vec4 Color = v_DiffuseColor + v_SpecularColor + v_AmbientLightColor;
float intensity;
intensity = dot(DirectionVectorSimulatedLight,v_SurfaceNormal);

if(intensity > 0.3)
		Color *= vec4(1,1,1,1.0);
	else if (intensity > 0.2)
		Color *= vec4(0.5,0.5,0.5,1.0);
	else if (intensity > 0.1)
		Color *= vec4(0.3,0.3,0.3,1.0);
	else
		Color *= vec4(0.2,0.2,0.2,1.0);

return Color;
}
void main()
{
vec4 FinalColor;
FinalColor.x = 0.0f;
FinalColor.y = 0.0f;
FinalColor.z = 0.0f;
FinalColor.w = 1.0f;
vec4 v_MaterialColor = texture2D( u_Texture, v_UV );

for(int i = 0; i < 5; i++)
{
vec4 Color = LightMath(u_Lights[i].LightPos, u_CameraPos, v_SurfaceWorldPos, v_SurfaceNormal, u_Lights[i].LightColor, u_Lights[i].LightRange, u_Lights[i].LightIntensity,v_MaterialColor);
FinalColor += Color;
FinalColor.w = v_MaterialColor.w;
}
	gl_FragColor = FinalColor;
}
