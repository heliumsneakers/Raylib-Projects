#include "raylib.h"
#include "rcamera.h"
#include "model_voxelizer.h"
#include "stdlib.h"
#include "stdint.h"
#include "time.h"

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Voxel Renderer");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f; 

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    bool captureMouse = true;
    DisableCursor();

    // Load the model
    Model model = LoadModelData("/Users/klo/projects/raylib/raylib-master/src/assets/barrel_large.obj");

    // Voxelization
    int voxelCount;
    int gridSize = 50;  // Set the desired grid size
    Voxel* voxels = VoxelizeModel(model, gridSize, &voxelCount);


    // Main game loop
    while (!WindowShouldClose()) { 
       
        // Update
        UpdateCamera(&camera, CAMERA_FREE); // Update camera
    
        if (IsKeyPressed(KEY_M)) {
            captureMouse = !captureMouse;
            if (captureMouse) {
                DisableCursor();        // Hide cursor
            } else {
                EnableCursor();         // Show cursor
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                
                // Draw the voxels
                for (int i = 0; i < voxelCount; i++) {
                    DrawCubeV(voxels[i].position, (Vector3){ 0.5f, 0.5f, 0.5f }, voxels[i].color);
                    DrawRay(voxels[i].debugRay, MAROON);   
                }

               // Optionally, draw the original model for reference
                DrawModel(model, (Vector3){ 5.0f, 5.0f, 5.0f }, 1.0f, BLUE); 

                EndMode3D();

            DrawText("Voxel Grid Example", 10, 40, 10, BLACK);
        EndDrawing();
    }

    // Cleanup
    free(voxels);
    UnloadModel(model);

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context
    return 0;
    }
    
