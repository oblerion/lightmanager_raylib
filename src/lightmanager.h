/**********************************************************************************************
*
*   raylib.lights - Some useful functions to deal with lights data
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2017-2024 Victor Fisac (@victorfisac) and Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/
// edited rlight version to work with lightmanager by oblerion

#pragma once
#include "raylib.h"

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
#define MAX_LIGHTS  4         // Max dynamic lights supported by shader
//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

// Light data
struct Light{   
    int type;
    bool enabled;
    Vector3 position;
    Vector3 target;
    Color color;
    float attenuation;
    
    // Shader locations
    int enabledLoc;
    int typeLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int attenuationLoc;
};
typedef struct Light Light;
// Light type
enum LightType{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT
};
typedef enum LightType LightType;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

Light CreateLight(int type, Vector3 position, Vector3 target, Color color, Shader shader);   // Create a light and get shader locations
void UpdateLightValues(Shader shader, Light light);         // Send light properties to shader

#ifdef __cplusplus
}
#endif
/**********************************************************************************************

   lightmanager - help to manage lights  

    LICENSE: MIT

    Copyright (c) 2024 oblerion

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

**********************************************************************************************/

#include <string.h>

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// static lightmanager data
struct LightManager
{
    int count;
    Light lights[MAX_LIGHTS];
    Shader lightshader;
} static lightmanager;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void LM_Init();
void LM_AddPointLight(Vector3 position,Vector3 target,Color color);
void LM_AddDirectionalLight(Vector3 position,Vector3 target,Color color);
void LM_AppliShader(Model* model);
void LM_Unload();