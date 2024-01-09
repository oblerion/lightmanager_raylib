# lightmanager_raylib
lightmanager for raylib

use edited rlight.h from shader raylib example<br>
use shader lighting from shader raylib example

## example 
```cpp
#include "raylib.h"
#include "lightmanager.h"
int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 1000; //GetMonitorWidth(0);
    const int screenHeight = 600;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    Camera camera = { 0 };
    camera.position = (Vector3){ 40.0f, 40.0f, 0.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    Vector3 position = { 0.0f, 0.0f, 0.0f };
    camera.projection=CAMERA_PERSPECTIVE;

    Model mod = LoadModel("asset/ship_Awing_gene.glb");
    float rot = 0;
   
    LM_Init();// light manager init
    LM_AddPointLight((Vector3){15,15,15},(Vector3){0,0,0},WHITE); // add light point
    LM_AddPointLight((Vector3){-15,15,15},(Vector3){0,0,0},GREEN);
    LM_AppliShader(&mod);// appli shader to model
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        DrawModelEx(mod,(Vector3){0,0,0},(Vector3){0,1,0},rot,(Vector3){1,1,1},WHITE);
        rot = rot +5*GetFrameTime();
        EndMode3D();

        EndDrawing();
    }
    UnloadModel(mod);
    LM_Unload();// unload light shader
    CloseWindow();        // Close window and OpenGL
    return 0;
}


```
