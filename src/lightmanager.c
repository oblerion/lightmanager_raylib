#include "lightmanager.h"

// Create a light and get shader locations
Light CreateLight(int type, Vector3 position, Vector3 target, Color color, Shader shader)
{
    Light light = { 0 };
    light.enabled = true;
    light.type = type;
    light.position = position;
    light.target = target;
    light.color = color;
    int lightsCount = lightmanager.count;
    // NOTE: Lighting shader naming must be the provided ones
    light.enabledLoc = GetShaderLocation(shader, TextFormat("lights[%i].enabled", lightsCount));
    light.typeLoc = GetShaderLocation(shader, TextFormat("lights[%i].type", lightsCount));
    light.positionLoc = GetShaderLocation(shader, TextFormat("lights[%i].position", lightsCount));
    light.targetLoc = GetShaderLocation(shader, TextFormat("lights[%i].target", lightsCount));
    light.colorLoc = GetShaderLocation(shader, TextFormat("lights[%i].color", lightsCount));

    UpdateLightValues(shader, light);
    
    return light;
}

// Send light properties to shader
// NOTE: Light shader locations should be available 
void UpdateLightValues(Shader shader, Light light)
{
    // Send to shader light enabled state and type
    SetShaderValue(shader, light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
    SetShaderValue(shader, light.typeLoc, &light.type, SHADER_UNIFORM_INT);

    // Send to shader light position values
    float position[3] = { light.position.x, light.position.y, light.position.z };
    SetShaderValue(shader, light.positionLoc, position, SHADER_UNIFORM_VEC3);

    // Send to shader light target position values
    float target[3] = { light.target.x, light.target.y, light.target.z };
    SetShaderValue(shader, light.targetLoc, target, SHADER_UNIFORM_VEC3);

    // Send to shader light color values
    float color[4] = { (float)light.color.r/(float)255, (float)light.color.g/(float)255, 
                       (float)light.color.b/(float)255, (float)light.color.a/(float)255 };
    SetShaderValue(shader, light.colorLoc, color, SHADER_UNIFORM_VEC4);
}


#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
    #define GLSL_VERSION            330
#elif defined(__ANDROID__) || defined(PLATFORM_WEB) // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
Shader LLoadShader(const char *file)
{
    const char* path = TextFormat("asset/shaders/glsl%d/",GLSL_VERSION);
    char pathvs[30];
    const char* pathfs = TextFormat("%s%s.fs",path,file);
    strcpy(pathvs,TextFormat("%s%s.vs",path,file));
    if(!FileExists(pathvs)) 
        strcpy(pathvs,TextFormat("%sbase.vs",path));
   
    Shader shader = LoadShader(pathvs,pathfs);
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    // Ambient light level (some basic lighting)
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);
    return shader;
}

void LM_Init()
{
    lightmanager.count=0;
    lightmanager.lightshader=LLoadShader("lighting");
}

void LM_AddPointLight(Vector3 position, Vector3 target, Color color)
{
    if(lightmanager.count<MAX_LIGHTS)
    {
        lightmanager.lights[lightmanager.count] = CreateLight(LIGHT_POINT,position,target,color,lightmanager.lightshader);
        lightmanager.count++;
    }
}

void LM_AddDirectionalLight(Vector3 position, Vector3 target, Color color)
{
    if(lightmanager.count<MAX_LIGHTS)
    {
        lightmanager.lights[lightmanager.count] = CreateLight(LIGHT_DIRECTIONAL,position,target,color,lightmanager.lightshader);
        lightmanager.count++;
    }
}

void LM_AppliShader(Model* model)
{
    for(int i=0;i<model->materialCount;i++)
        model->materials[i].shader = lightmanager.lightshader;
}

void LM_Unload()
{
    UnloadShader(lightmanager.lightshader);
}
