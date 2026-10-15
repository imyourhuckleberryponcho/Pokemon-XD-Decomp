// NonMatching: loadCamera matches; loadModel only differs in register allocation
// (target: index=r27, archive=r28, scene=r29, arg1=r30, arg2=r31).
#include <dolphin/types.h>

#pragma pool_strings off
#pragma peephole off

struct HSD_Archive;

struct SceneData {
    void** models;
    void* camera;
};

extern "C" {
void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, const char* symbol);
void* GScameraLoad(void* desc);
void GScameraFree(void* camera);
void* GSmodelLoad(void* desc, void* boundBox);
void GSmodelFree(void* model);
void GSresRegisterResource(void* resource, u32, u32, BOOL (*unload)(void*, u32, u32));
}

static BOOL _unloadCamera(void* camera, u32, u32);
static BOOL _unloadModel(void* model, u32, u32);

extern "C" {

void loadCamera(HSD_Archive* archive, u32 arg1, u32 arg2) {
    if (archive != NULL) {
        SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(archive, "scene_data");
        if (scene != NULL) {
            GSresRegisterResource(GScameraLoad(scene->camera), arg1, arg2, _unloadCamera);
        }
    }
}

void loadModel(HSD_Archive* archive, u32 arg1, u32 index, u32 arg2) {
    if (archive != NULL) {
        SceneData* scene = (SceneData*)HSD_ArchiveGetPublicAddress(archive, "scene_data");
        if (scene != NULL) {
            void* boundBox = index == 0 ? HSD_ArchiveGetPublicAddress(archive, "bound_box") : NULL;
            for (u32 i = 0; scene->models[i] != NULL; i++) {
                if (i == index) {
                    GSresRegisterResource(GSmodelLoad(scene->models[i], boundBox), arg1, arg2, _unloadModel);
                    return;
                }
            }
        }
    }
}

}

static BOOL _unloadCamera(void* camera, u32, u32) {
    GScameraFree(camera);
    return TRUE;
}

static BOOL _unloadModel(void* model, u32, u32) {
    GSmodelFree(model);
    return TRUE;
}
