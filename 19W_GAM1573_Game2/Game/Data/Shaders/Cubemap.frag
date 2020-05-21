#version 120

struct Light
{
vec3 LightPos;
float LightRange;
float LightIntensity;
vec4 LightColor;
};

uniform sampler2D u_Texture;
uniform samplerCube u_TextureCubemap;
uniform vec3 u_CameraPos;
uniform Light u_Lights[5];
uniform float u_MaterialShine;

varying vec2 v_UV;
varying vec3 v_SurfaceWorldPos;
varying vec3 v_SurfaceNormal;
//varying vec3 v_LightPos;
varying vec3 v_ObjectPos;

void main()
{


//light variables
//float range = 20.0f;
//float intensity = 0.25f;
//float shiny = 100.0f;

vec4 FinalColor;
FinalColor.x = 0.0f;
FinalColor.y = 0.0f;
FinalColor.z = 0.0f;
FinalColor.w = 1.0f;
for(int i = 0; i < 5; i++)
{
//Pixel To Light Vector
vec3 UnnormalizedVectorFromPixelToLight = u_Lights[i].LightPos - v_SurfaceWorldPos;
vec3 DirectionVectorPixelToLight = normalize(UnnormalizedVectorFromPixelToLight);
float distanceToLight = length(UnnormalizedVectorFromPixelToLight);

//Pixel To Camera Vector : Specular
vec3 UnnormalizedVectorFromPixelToCamera = u_CameraPos - v_SurfaceWorldPos;
vec3 DirectionVectorPixelToCamera = normalize(UnnormalizedVectorFromPixelToCamera);

vec3 UnnormalizedVectorFromCameraToPixel = v_SurfaceWorldPos - u_CameraPos;
vec3 VectorFromCameraToPixel = normalize(UnnormalizedVectorFromCameraToPixel);

//Simulated Light Vector : Specular
vec3 UnnormalizedVectorSimulatedLight = DirectionVectorPixelToCamera + DirectionVectorPixelToLight;
vec3 DirectionVectorSimulatedLight = normalize(UnnormalizedVectorSimulatedLight);

float DiffusePercent = dot(DirectionVectorPixelToLight,v_SurfaceNormal);
DiffusePercent = max(0.0f, DiffusePercent);
float SpecularPercent = dot(DirectionVectorSimulatedLight,v_SurfaceNormal);
SpecularPercent = max(0.0f, SpecularPercent);
SpecularPercent = pow(SpecularPercent,u_MaterialShine);
float fallOff = max(0.0f, pow((1 -distanceToLight/u_Lights[i].LightRange),u_Lights[i].LightIntensity));

float finalPercent = DiffusePercent + SpecularPercent;

vec3 reflectedDirection = reflect(VectorFromCameraToPixel, v_SurfaceNormal);

vec4 v_MaterialColor =  texture2D( u_Texture, v_UV ) + (textureCube(u_TextureCubemap, reflectedDirection)* 0.1);
vec4 v_DiffuseColor = u_Lights[i].LightColor * v_MaterialColor * DiffusePercent * fallOff;
vec4 v_SpecularColor = u_Lights[i].LightColor * SpecularPercent * fallOff;

vec4 Color = v_DiffuseColor + v_SpecularColor;
FinalColor += Color;
//v_FinalColor.w = v_MaterialColor.w;
FinalColor.w = v_MaterialColor.w;
}
	gl_FragColor = FinalColor;
}
