#include "model_voxelizer.h"
#include "raylib.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"

Model LoadModelData(const char* filename) {
    // Load and return the model
    return LoadModel(filename);
}

bool IsPointInsideModel(Vector3 point, Model model) {

    BoundingBox vbox = GetModelBoundingBox(model);
    Vector3 directions[] = {
        { 1.0f, 0.0f, 0.0f }, // X-axis
        { 0.0f, 1.0f, 0.0f }, // Y-axis
        { 0.0f, 0.0f, 1.0f }, // Z-axis
        // Add more directions if needed
    };
    int directionsCount = sizeof(directions) / sizeof(directions[0]);

    int hitCount = 0;
    for (int i = 0; i < directionsCount; i++) {
        Ray ray = { .position = point, .direction = directions[i] };
        RayCollision collision = GetRayCollisionBox(ray, vbox);
        if (collision.hit) {
            hitCount++;
            printf("Ray Hit!\n");
        }
    }

    // Determine if inside based on hit count (you can refine this logic)
    return (hitCount > 0);
}

Voxel* VoxelizeModel(Model model, int gridSize, int* voxelCount) {
    // Allocate memory for voxels
    Voxel* voxels = malloc(sizeof(Voxel) * gridSize * gridSize * gridSize);
    *voxelCount = 0;

    // Determine the model's bounding box to scale the voxel grid accordingly
    BoundingBox bbox = GetModelBoundingBox(model);
    float maxDimension = fmaxf(fmaxf(bbox.max.x - bbox.min.x, bbox.max.y - bbox.min.y), bbox.max.z - bbox.min.z);

    // Calculate the size of each voxel
    float voxelSize = maxDimension / gridSize;

    // Voxelization logic
    for (int x = 0; x < gridSize; x++) {
        for (int y = 0; y < gridSize; y++) {
            for (int z = 0; z < gridSize; z++) {
                Vector3 voxelCenter = {
                    bbox.min.x + x * voxelSize + voxelSize / 2,
                    bbox.min.y + y * voxelSize + voxelSize / 2,
                    bbox.min.z + z * voxelSize + voxelSize / 2
                };

                // Create a ray for debugging
                Ray debugRay = { voxelCenter, (Vector3){ 1.0f, 0.0f, 0.0f } }; // Example: ray along the X-axis

                // Store the ray in the voxel structure
                voxels[*voxelCount].debugRay = debugRay;

                if (IsPointInsideModel(voxelCenter, model)) {
                    voxels[*voxelCount].position = voxelCenter;
                    voxels[*voxelCount].color = RED; // Assign a color or generate one randomly
                    (*voxelCount)++;
                }
            }
        }
    }

    printf("Voxel Count: %d\n", *voxelCount);        
    return voxels;
}
