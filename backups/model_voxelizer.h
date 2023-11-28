#ifndef MODEL_VOXELIZER_H
#define MODEL_VOXELIZER_H

#include "raylib.h"

typedef struct Voxel {
    Vector3 position;
    Color color;
    Ray debugRay;
} Voxel;

// Function to load a model
Model LoadModelData(const char* filename);

// Function to voxelize a model
Voxel* VoxelizeModel(Model model, int gridSize, int* voxelCount);

#endif // MODEL_VOXELIZER_H
