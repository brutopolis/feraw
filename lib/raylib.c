#include "bruter.h"
#include "raylib.h"

/*
notes:
- everything vr-related is not tested and is not planned to be any soon
- everything audio-related needs some testing
- no *_v functions are implemented
*/

Vector2 vector2_constructor(BruterList *vec2)
{
    BruterFloat x = vec2->data[0].f;
    BruterFloat y = vec2->data[1].f;
    
    Vector2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

BruterList* vector2_to_list(Vector2 vec)
{
    BruterList *list = bruter_new(2, true, true);
    bruter_push_float(list, vec.x, "x", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, vec.y, "y", BRUTER_TYPE_FLOAT);
    return list;
}

Vector3 vector3_constructor(BruterList *vec3)
{
    float x = vec3->data[0].f;
    float y = vec3->data[1].f;
    float z = vec3->data[2].f;
    
    Vector3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

BruterList* vector3_to_list(Vector3 vec)
{
    BruterList *list = bruter_new(3, true, true);
    bruter_push_float(list, vec.x, "x", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, vec.y, "y", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, vec.z, "z", BRUTER_TYPE_FLOAT);
    return list;
}

Vector4 vector4_constructor(BruterList *vec4)
{
    float x = vec4->data[0].f;
    float y = vec4->data[1].f;
    float z = vec4->data[2].f;
    float w = vec4->data[3].f;
    
    Vector4 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}

BruterList* vector4_to_list(Vector4 vec)
{
    BruterList *list = bruter_new(4, true, true);
    bruter_push_float(list, vec.x, "x", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, vec.y, "y", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, vec.z, "z", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, vec.w, "w", BRUTER_TYPE_FLOAT);
    return list;
}

Matrix matrix_constructor(BruterList *matrix)
{
    float m[16];
    for (int i = 0; i < 16; i++) {
        m[i] = matrix->data[i].f;
    }
    
    Matrix mat;
    mat.m0 = m[0]; mat.m1 = m[1]; mat.m2 = m[2]; mat.m3 = m[3];
    mat.m4 = m[4]; mat.m5 = m[5]; mat.m6 = m[6]; mat.m7 = m[7];
    mat.m8 = m[8]; mat.m9 = m[9]; mat.m10 = m[10]; mat.m11 = m[11];
    mat.m12 = m[12]; mat.m13 = m[13]; mat.m14 = m[14]; mat.m15 = m[15];
    return mat;
}

BruterList* matrix_to_list(Matrix mat)
{
    BruterList *list = bruter_new(16, true, true);
    bruter_push_float(list, mat.m0, "m0", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m1, "m1", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m2, "m2", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m3, "m3", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m4, "m4", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m5, "m5", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m6, "m6", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m7, "m7", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m8, "m8", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m9, "m9", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m10, "m10", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m11, "m11", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m12, "m12", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m13, "m13", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m14, "m14", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, mat.m15, "m15", BRUTER_TYPE_FLOAT);
    return list;
}

Color color_from_int(int color)
{
    Color c;
    c.r = (color >> 24) & 0xFF;
    c.g = (color >> 16) & 0xFF;
    c.b = (color >> 8) & 0xFF;
    c.a = color & 0xFF;
    return c;
}

BruterInt color_to_int(Color color)
{
    BruterInt result = 0;
    memcpy(&result, &color, sizeof(Color));
    return result;
}

// avoid using this
Color color_constructor(BruterList *color)
{
    unsigned char r = color->data[0].i;
    unsigned char g = color->data[1].i;
    unsigned char b = color->data[2].i;
    unsigned char a = color->data[3].i;
    
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

// avoid using this too
BruterList* color_to_list(Color color)
{
    BruterList *list = bruter_new(4, true, true);
    bruter_push_int(list, color.r, "r", BRUTER_TYPE_ANY);
    bruter_push_int(list, color.g, "g", BRUTER_TYPE_ANY);
    bruter_push_int(list, color.b, "b", BRUTER_TYPE_ANY);
    bruter_push_int(list, color.a, "a", BRUTER_TYPE_ANY);
    return list;
}

Rectangle rectangle_constructor(BruterList *rect)
{
    float x = rect->data[0].f;
    float y = rect->data[1].f;
    float width = rect->data[2].f;
    float height = rect->data[3].f;
    
    Rectangle r;
    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;
    return r;
}

BruterList *rectangle_to_list(Rectangle rect)
{
    BruterList *list = bruter_new(4, true, true);
    bruter_push_float(list, rect.x, "x", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, rect.y, "y", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, rect.width, "width", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, rect.height, "height", BRUTER_TYPE_FLOAT);
    return list;
}

Image image_constructor(BruterList *image)
{
    unsigned char *data = image->data[0].p;
    int width = image->data[1].i;
    int height = image->data[2].i;
    int mipmaps = image->data[3].i;
    int format = image->data[4].i;
    Image img;
    img.data = data;
    img.width = width;
    img.height = height;
    img.mipmaps = mipmaps;
    img.format = format;
    return img;
}

BruterList *image_to_list(Image img)
{
    BruterList *list = bruter_new(5, true, true);
    bruter_push_pointer(list, img.data, "data", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, img.width, "width", BRUTER_TYPE_ANY);
    bruter_push_int(list, img.height, "height", BRUTER_TYPE_ANY);
    bruter_push_int(list, img.mipmaps, "mipmaps", BRUTER_TYPE_ANY);
    bruter_push_int(list, img.format, "format", BRUTER_TYPE_ANY);
    return list;
}

Texture texture_constructor(BruterList *texture)
{
    unsigned int id = texture->data[0].i;
    int width = texture->data[1].i;
    int height = texture->data[2].i;
    int mipmaps = texture->data[3].i;
    int format = texture->data[4].i;
    
    Texture2D tex;
    tex.id = id;
    tex.width = width;
    tex.height = height;
    tex.mipmaps = mipmaps;
    tex.format = format;
    return tex;
}

BruterList *texture_to_list(Texture2D tex)
{
    BruterList *list = bruter_new(5, true, true);
    bruter_push_int(list, tex.id, "id", BRUTER_TYPE_ANY);
    bruter_push_int(list, tex.width, "width", BRUTER_TYPE_ANY);
    bruter_push_int(list, tex.height, "height", BRUTER_TYPE_ANY);
    bruter_push_int(list, tex.mipmaps, "mipmaps", BRUTER_TYPE_ANY);
    bruter_push_int(list, tex.format, "format", BRUTER_TYPE_ANY);
    return list;
}


RenderTexture render_texture_constructor(BruterList *renderTexture)
{
    unsigned int id = renderTexture->data[0].i;
    RenderTexture2D rt;
    rt.id = id;
    rt.texture = texture_constructor(renderTexture->data[1].p);
    rt.depth = texture_constructor(renderTexture->data[2].p);
    return rt;
}

BruterList *render_texture_to_list(RenderTexture2D rt)
{
    BruterList *list = bruter_new(3, true, true);
    bruter_push_int(list, rt.id, "id", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, &rt.texture, "texture", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, &rt.depth, "depth", BRUTER_TYPE_BUFFER);
    return list;
}

NPatchInfo npatch_info_constructor(BruterList *npatchInfo)
{
    Rectangle source = rectangle_constructor(npatchInfo->data[0].p);
    int left = npatchInfo->data[1].i;
    int top = npatchInfo->data[2].i;
    int right = npatchInfo->data[3].i;
    int bottom = npatchInfo->data[4].i;
    int layout = npatchInfo->data[5].i;
    
    NPatchInfo info;
    info.source = source;
    info.left = left;
    info.top = top;
    info.right = right;
    info.bottom = bottom;
    info.layout = layout;
    return info;
}

BruterList *npatch_info_to_list(NPatchInfo info)
{
    BruterList *list = bruter_new(6, true, true);
    bruter_push_pointer(list, rectangle_to_list(info.source), "source", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, info.left, "left", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.top, "top", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.right, "right", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.bottom, "bottom", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.layout, "layout", BRUTER_TYPE_ANY);
    return list;
}

GlyphInfo glyph_info_constructor(BruterList *glyphInfo)
{
    int value = glyphInfo->data[0].i;
    int offsetX = glyphInfo->data[1].i;
    int offsetY = glyphInfo->data[2].i;
    int advanceX = glyphInfo->data[3].i;
    Image rec = image_constructor(glyphInfo->data[4].p);
    
    GlyphInfo info;
    info.value = value;
    info.offsetX = offsetX;
    info.offsetY = offsetY;
    info.advanceX = advanceX;
    info.image = rec;
    return info;
}

BruterList *glyph_info_to_list(GlyphInfo info)
{
    BruterList *list = bruter_new(5, true, true);
    bruter_push_int(list, info.value, "value", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.offsetX, "offsetX", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.offsetY, "offsetY", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.advanceX, "advanceX", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, image_to_list(info.image), "image", BRUTER_TYPE_LIST);
    return list;
}

Font font_constructor(BruterList *font)
{
    unsigned int baseSize = font->data[0].i;
    unsigned int glyphCount = font->data[1].i;
    unsigned int glyphPadding = font->data[2].i;
    Texture2D texture = texture_constructor(font->data[3].p);
    Rectangle *recs = font->data[4].p;
    GlyphInfo *glyphs = font->data[5].p;
    Font f;
    f.baseSize = baseSize;
    f.glyphCount = glyphCount;
    f.glyphs = glyphs;
    return f;
}

BruterList *font_to_list(Font font)
{
    BruterList *list = bruter_new(6, true, true);
    bruter_push_int(list, font.baseSize, "baseSize", BRUTER_TYPE_ANY);
    bruter_push_int(list, font.glyphCount, "glyphCount", BRUTER_TYPE_ANY);
    bruter_push_int(list, font.glyphPadding, "glyphPadding", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, texture_to_list(font.texture), "texture", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, font.recs, "recs", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, font.glyphs, "glyphs", BRUTER_TYPE_BUFFER);
    return list;
}

Camera3D camera3d_constructor(BruterList *camera3D)
{
    Vector3 position = vector3_constructor(camera3D->data[0].p);
    Vector3 target = vector3_constructor(camera3D->data[1].p);
    Vector3 up = vector3_constructor(camera3D->data[2].p);
    float fovy = camera3D->data[3].f;
    int projection = camera3D->data[4].i;
    
    Camera3D cam;
    cam.position = position;
    cam.target = target;
    cam.up = up;
    cam.fovy = fovy;
    cam.projection = projection;
    return cam;
}

BruterList *camera3D_to_list(Camera3D cam)
{
    BruterList *list = bruter_new(5, true, true);
    bruter_push_pointer(list, vector3_to_list(cam.position), "position", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(cam.target), "target", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(cam.up), "up", BRUTER_TYPE_LIST);
    bruter_push_float(list, cam.fovy, "fovy", BRUTER_TYPE_FLOAT);
    bruter_push_int(list, cam.projection, "projection", BRUTER_TYPE_ANY);
    return list;
}

Camera2D camera2d_constructor(BruterList *camera2D)
{
    Vector2 offset = vector2_constructor(camera2D->data[0].p);
    Vector2 target = vector2_constructor(camera2D->data[1].p);
    float rotation = camera2D->data[2].f;
    float zoom = camera2D->data[3].f;
    
    Camera2D cam;
    cam.offset = offset;
    cam.target = target;
    cam.rotation = rotation;
    cam.zoom = zoom;
    return cam;
}

BruterList *camera2D_to_list(Camera2D cam)
{
    BruterList *list = bruter_new(4, true, true);
    bruter_push_pointer(list, vector2_to_list(cam.offset), "offset", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector2_to_list(cam.target), "target", BRUTER_TYPE_LIST);
    bruter_push_float(list, cam.rotation, "rotation", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, cam.zoom, "zoom", BRUTER_TYPE_FLOAT);
    return list;
}

// need revision!!
Mesh mesh_constructor(BruterList *mesh)
{
    Mesh m;
    m.vertexCount = mesh->data[0].i;
    m.triangleCount = mesh->data[1].i;

    m.vertices = (float*)mesh->data[2].p;
    m.texcoords = (float*)mesh->data[3].p;
    m.texcoords2 = (float*)mesh->data[4].p;
    m.normals = (float*)mesh->data[5].p;
    m.tangents = (float*)mesh->data[6].p;
    m.colors = (unsigned char*)mesh->data[7].p;
    m.indices = (unsigned short*)mesh->data[8].p;
    m.animVertices = (float*)mesh->data[9].p;
    m.animNormals = (float*)mesh->data[10].p;
    m.boneIds = (unsigned char*)mesh->data[11].p;
    m.boneWeights = (float*)mesh->data[12].p;
    m.boneMatrices = (Matrix*)mesh->data[13].p;
    m.boneCount = mesh->data[14].i;
    
    m.vaoId = mesh->data[15].i;
    m.vboId = mesh->data[16].p;
    return m;
}

BruterList *mesh_to_list(Mesh m)
{
    BruterList *list = bruter_new(17, true, true);
    bruter_push_int(list, m.vertexCount, "vertexCount", BRUTER_TYPE_ANY);
    bruter_push_int(list, m.triangleCount, "triangleCount", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, m.vertices, "vertices", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.texcoords, "texcoords", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.texcoords2, "texcoords2", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.normals, "normals", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.tangents, "tangents", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.colors, "colors", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.indices, "indices", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.animVertices, "animVertices", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.animNormals, "animNormals", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.boneIds, "boneIds", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.boneWeights, "boneWeights", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.boneMatrices, "boneMatrices", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, m.boneCount, "boneCount", BRUTER_TYPE_ANY);
    
    // vaoId and vboId are not pointers
    bruter_push_int(list, m.vaoId, "vaoId", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, m.vboId, "vboId", BRUTER_TYPE_BUFFER);

    return list;
}

// need revision
Shader shader_constructor(BruterList *shader)
{
    unsigned int id = shader->data[0].i;
    unsigned int locsCount = shader->data[1].i;
    int *locs = (int*)bruter_pop_pointer(shader->data[2].p);
    
    Shader sh;
    sh.id = id;
    sh.locs = locs;
    return sh;
}

BruterList *shader_to_list(Shader sh)
{
    BruterList *list = bruter_new(3, true, true);
    bruter_push_int(list, sh.id, "id", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, sh.locs, "locs", BRUTER_TYPE_BUFFER);
    return list;
}

MaterialMap material_map_constructor(BruterList *materialMap)
{
    Texture2D texture = texture_constructor(materialMap->data[0].p);
    Color color = color_from_int(materialMap->data[1].i);
    float value = materialMap->data[2].f;
    MaterialMap map;
    map.texture = texture;
    map.color = color;
    map.value = value;
    return map;
}

BruterList *material_map_to_list(MaterialMap map)
{
    BruterList *list = bruter_new(3, true, true);
    bruter_push_pointer(list, texture_to_list(map.texture), "texture", BRUTER_TYPE_LIST);
    bruter_push_int(list, color_to_int(map.color), "color", BRUTER_TYPE_ANY);
    bruter_push_float(list, map.value, "value", BRUTER_TYPE_FLOAT);
    return list;
}

// need revision
Material material_constructor(BruterList *material)
{
    BruterList *paramsList = material->data[2].p;

    Shader shader = shader_constructor(material->data[0].p);
    MaterialMap *maps = material->data[1].p;
    
    
    Material mat;
    mat.shader = shader;
    mat.maps = maps;
    
    for (int i = 0; i < paramsList->size && i < 4; i++) 
    {
        mat.params[i] = paramsList->data[i].f;
    }
    
    return mat;
}

BruterList *material_to_list(Material mat)
{
    BruterList *list = bruter_new(3, true, true);
    bruter_push_pointer(list, shader_to_list(mat.shader), "shader", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, mat.maps, "maps", BRUTER_TYPE_BUFFER);
    
    BruterList *paramsList = bruter_new(4, true, true);
    for (int i = 0; i < 4; i++) 
    {
        bruter_push_float(paramsList, mat.params[i], "param", BRUTER_TYPE_FLOAT);
    }
    
    bruter_push_pointer(list, paramsList, "params", BRUTER_TYPE_LIST);
    return list;
}

Transform transform_constructor(BruterList *transform)
{
    Vector3 translation = vector3_constructor(transform->data[0].p);
    Quaternion rotation = vector4_constructor(transform->data[1].p);
    Vector3 scale = vector3_constructor(transform->data[2].p);
    
    Transform t;
    t.translation = translation;
    t.rotation = rotation;
    t.scale = scale;
    return t;
}

BruterList *transform_to_list(Transform t)
{
    BruterList *list = bruter_new(3, true, true);
    bruter_push_pointer(list, vector3_to_list(t.translation), "translation", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector4_to_list(t.rotation), "rotation", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(t.scale), "scale", BRUTER_TYPE_LIST);
    return list;
}

BoneInfo bone_info_constructor(BruterList *boneInfo)
{
    char* name = boneInfo->data[0].p;
    int parent = boneInfo->data[1].i;


    BoneInfo info;
    info.parent = parent;

    if (strlen(name) > 32)
    {
        // copy only the first 31 chars + null
        name[31] = '\0';
        memcpy(info.name, name, 31);
    }
    else
    {
        // copy the whole name
        strcpy(info.name, name);
    }
    return info;
}

BruterList *bone_info_to_list(BoneInfo info)
{
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, info.name, "name", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, info.parent, "parent", BRUTER_TYPE_ANY);
    return list;
}

// need revision!
Model model_constructor(BruterList *model)
{
    Matrix transform = matrix_constructor(model->data[0].p);

    int meshCount = model->data[1].i;
    int materialCount = model->data[2].i;
    Mesh* meshes = model->data[3].p;
    Material *materials = model->data[4].p;
    int* meshMaterial = model->data[5].p;

    int boneCount = model->data[6].i;
    BoneInfo *bones = model->data[7].p;
    Transform *bindPose = model->data[8].p;

    Model m;
    m.transform = transform;
    m.meshCount = meshCount;
    m.materialCount = materialCount;
    m.meshes = meshes;
    m.materials = materials;
    m.meshMaterial = meshMaterial;
    m.boneCount = boneCount;
    m.bones = bones;
    m.bindPose = bindPose;

    return m;
}

BruterList *model_to_list(Model m)
{
    BruterList *list = bruter_new(9, true, true);
    bruter_push_pointer(list, matrix_to_list(m.transform), "transform", BRUTER_TYPE_LIST);
    bruter_push_int(list, m.meshCount, "meshCount", BRUTER_TYPE_ANY);
    bruter_push_int(list, m.materialCount, "materialCount", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, m.meshes, "meshes", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.materials, "materials", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.meshMaterial, "meshMaterial", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, m.boneCount, "boneCount", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, m.bones, "bones", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, m.bindPose, "bindPose", BRUTER_TYPE_BUFFER);
    
    return list;
}

// need revision!
ModelAnimation model_animation_constructor(BruterList *modelAnimation)
{
    int boneCount = modelAnimation->data[0].i;
    int frameCount = modelAnimation->data[1].i;
    BoneInfo *bones = modelAnimation->data[2].p;
    Transform **framePoses = modelAnimation->data[3].p;
    char *name = modelAnimation->data[5].p;

    ModelAnimation anim;
    anim.boneCount = boneCount;
    anim.frameCount = frameCount;
    anim.bones = bones;
    anim.framePoses = framePoses;

    // name 
    if (strlen(name) > 32)
    {
        // copy only the first 31 chars + null
        name[31] = '\0';
        memcpy(anim.name, name, 31);
    }
    else
    {
        // copy the whole name
        strcpy(anim.name, name);
    }

    return anim;
}

BruterList *model_animation_to_list(ModelAnimation anim)
{
    BruterList *list = bruter_new(6, true, true);
    bruter_push_int(list, anim.boneCount, "boneCount", BRUTER_TYPE_ANY);
    bruter_push_int(list, anim.frameCount, "frameCount", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, anim.bones, "bones", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, anim.framePoses, "framePoses", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, anim.name, "name", BRUTER_TYPE_BUFFER);
    return list;
}

Ray ray_constructor(BruterList *ray)
{
    Vector3 position = vector3_constructor(ray->data[0].p);
    Vector3 direction = vector3_constructor(ray->data[1].p);
    
    Ray r;
    r.position = position;
    r.direction = direction;
    return r;
}

BruterList *ray_to_list(Ray r)
{
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, vector3_to_list(r.position), "position", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(r.direction), "direction", BRUTER_TYPE_LIST);
    return list;
}

RayCollision ray_collision_constructor(BruterList *rayCollision)
{
    bool hit = rayCollision->data[0].i;
    float distance = rayCollision->data[1].f;
    Vector3 point = vector3_constructor(rayCollision->data[2].p);
    Vector3 normal = vector3_constructor(rayCollision->data[3].p);

    RayCollision rc;
    rc.hit = hit;
    rc.distance = distance;
    rc.point = point;
    rc.normal = normal;
    return rc;
}

BruterList *ray_collision_to_list(RayCollision rc)
{
    BruterList *list = bruter_new(4, true, true);
    bruter_push_int(list, rc.hit, "hit", BRUTER_TYPE_ANY);
    bruter_push_float(list, rc.distance, "distance", BRUTER_TYPE_FLOAT);
    bruter_push_pointer(list, vector3_to_list(rc.point), "point", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(rc.normal), "normal", BRUTER_TYPE_LIST);
    return list;
}

BoundingBox bounding_box_constructor(BruterList *boundingBox)
{
    Vector3 min = vector3_constructor(boundingBox->data[0].p);
    Vector3 max = vector3_constructor(boundingBox->data[1].p);
    
    BoundingBox box;
    box.min = min;
    box.max = max;
    return box;
}

BruterList *bounding_box_to_list(BoundingBox box)
{
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, vector3_to_list(box.min), "min", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(box.max), "max", BRUTER_TYPE_LIST);
    return list;
}

Wave wave_constructor(BruterList *wave)
{
    unsigned int frameCount = wave->data[0].i;
    unsigned int sampleRate = wave->data[1].i;
    unsigned int sampleSize = wave->data[2].i;
    unsigned int channels = wave->data[3].i;
    unsigned char *data = wave->data[4].p;

    Wave w;
    w.frameCount = frameCount;
    w.sampleRate = sampleRate;
    w.sampleSize = sampleSize;
    w.channels = channels;
    w.data = data;
    return w;
}

BruterList *wave_to_list(Wave w)
{
    BruterList *list = bruter_new(5, true, true);
    bruter_push_int(list, w.frameCount, "frameCount", BRUTER_TYPE_ANY);
    bruter_push_int(list, w.sampleRate, "sampleRate", BRUTER_TYPE_ANY);
    bruter_push_int(list, w.sampleSize, "sampleSize", BRUTER_TYPE_ANY);
    bruter_push_int(list, w.channels, "channels", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, w.data, "data", BRUTER_TYPE_BUFFER);
    return list;
}

// need revision!!
AudioStream audio_stream_constructor(BruterList *audioStream)
{
    rAudioBuffer *buffer = audioStream->data[0].p;
    rAudioProcessor *processor = audioStream->data[1].p;

    unsigned int sampleRate = audioStream->data[2].i;
    unsigned int sampleSize = audioStream->data[3].i;
    unsigned int channels = audioStream->data[4].i;
    
    AudioStream stream;
    stream.buffer = buffer;
    stream.processor = processor;
    stream.sampleRate = sampleRate;
    stream.sampleSize = sampleSize;
    stream.channels = channels;
    return stream;
}

BruterList *audio_stream_to_list(AudioStream stream)
{
    BruterList *list = bruter_new(5, true, true);
    bruter_push_pointer(list, stream.buffer, "buffer", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, stream.processor, "processor", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, stream.sampleRate, "sampleRate", BRUTER_TYPE_ANY);
    bruter_push_int(list, stream.sampleSize, "sampleSize", BRUTER_TYPE_ANY);
    bruter_push_int(list, stream.channels, "channels", BRUTER_TYPE_ANY);
    return list;
}

Sound sound_constructor(BruterList *sound)
{
    AudioStream stream = audio_stream_constructor(sound->data[0].p);
    unsigned int frameCount = sound->data[1].i;

    Sound snd;
    snd.stream = stream;
    snd.frameCount = frameCount;
    return snd;
}

BruterList *sound_to_list(Sound snd)
{
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, audio_stream_to_list(snd.stream), "stream", BRUTER_TYPE_LIST);
    bruter_push_int(list, snd.frameCount, "frameCount", BRUTER_TYPE_ANY);
    return list;
}

// need revision
Music music_constructor(BruterList *music)
{
    AudioStream stream = audio_stream_constructor(music->data[0].p);
    unsigned int frameCount = music->data[1].i;
    bool looping = music->data[2].i;

    int ctxType = music->data[3].i;
    void *ctxData = music->data[4].p;
    
    Music mus;
    mus.stream = stream;
    mus.frameCount = frameCount;
    mus.looping = looping;
    mus.ctxType = ctxType;
    mus.ctxData = ctxData;
    return mus;
}

BruterList *music_to_list(Music mus)
{
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, audio_stream_to_list(mus.stream), "stream", BRUTER_TYPE_LIST);
    bruter_push_int(list, mus.frameCount, "frameCount", BRUTER_TYPE_ANY);
    bruter_push_int(list, mus.looping, "looping", BRUTER_TYPE_ANY);
    bruter_push_int(list, mus.ctxType, "ctxType", BRUTER_TYPE_ANY);
    bruter_push_pointer(list, mus.ctxData, "ctxData", BRUTER_TYPE_BUFFER);
    return list;
}

VrDeviceInfo vr_device_info_constructor(BruterList *vrDeviceInfo)
{
    int hResolution = vrDeviceInfo->data[0].i;
    int vResolution = vrDeviceInfo->data[1].i;
    float hScreenSize = vrDeviceInfo->data[2].f;
    float vScreenSize = vrDeviceInfo->data[3].f;
    float eyeToScreenDistance = vrDeviceInfo->data[4].f;
    float lensSeparationDistance = vrDeviceInfo->data[5].f;
    float interpupillaryDistance = vrDeviceInfo->data[6].f;
    BruterList *lensDistortionValues = vrDeviceInfo->data[7].p;
    BruterList *chromaAbCorrection = vrDeviceInfo->data[8].p;

    VrDeviceInfo info;
    info.hResolution = hResolution;
    info.vResolution = vResolution;
    info.hScreenSize = hScreenSize;
    info.vScreenSize = vScreenSize;
    info.eyeToScreenDistance = eyeToScreenDistance;
    info.lensSeparationDistance = lensSeparationDistance;
    info.interpupillaryDistance = interpupillaryDistance;

    for (int i = 0; i < lensDistortionValues->size && i < 4; i++) 
    {
        info.lensDistortionValues[i] = lensDistortionValues->data[i].f;
    }

    for (int i = 0; i < chromaAbCorrection->size && i < 4; i++) 
    {
        info.chromaAbCorrection[i] = chromaAbCorrection->data[i].f;
    }

    return info;
}


// need revision!!!!
BruterList *vr_device_info_to_list(VrDeviceInfo info)
{
    BruterList *list = bruter_new(9, true, true);
    bruter_push_int(list, info.hResolution, "hResolution", BRUTER_TYPE_ANY);
    bruter_push_int(list, info.vResolution, "vResolution", BRUTER_TYPE_ANY);
    bruter_push_float(list, info.hScreenSize, "hScreenSize", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, info.vScreenSize, "vScreenSize", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, info.eyeToScreenDistance, "eyeToScreenDistance", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, info.lensSeparationDistance, "lensSeparationDistance", BRUTER_TYPE_FLOAT);
    bruter_push_float(list, info.interpupillaryDistance, "interpupillaryDistance", BRUTER_TYPE_FLOAT);

    BruterList *lensDistortionValues = bruter_new(4, true, true);
    for (int i = 0; i < 4; i++) 
    {
        bruter_push_float(lensDistortionValues, info.lensDistortionValues[i], "lensDistortionValue", BRUTER_TYPE_FLOAT);
    }
    
    BruterList *chromaAbCorrection = bruter_new(4, true, true);
    for (int i = 0; i < 4; i++) 
    {
        bruter_push_float(chromaAbCorrection, info.chromaAbCorrection[i], "chromaAbCorrection", BRUTER_TYPE_FLOAT);
    }

    bruter_push_pointer(list, lensDistortionValues, "lensDistortionValues", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, chromaAbCorrection, "chromaAbCorrection", BRUTER_TYPE_LIST);

    return list;
}

VrStereoConfig vr_stereo_config_constructor(BruterList *vrStereoConfig)
{
    BruterList *projecton_list = vrStereoConfig->data[0].p;
    BruterList *viewOffset_list = vrStereoConfig->data[1].p;
    BruterList *leftLensCenter_list = vrStereoConfig->data[2].p;
    BruterList *rightLensCenter_list = vrStereoConfig->data[3].p;
    BruterList *leftScreenCenter_list = vrStereoConfig->data[4].p;
    BruterList *rightScreenCenter_list = vrStereoConfig->data[5].p;
    BruterList *scale_list = vrStereoConfig->data[6].p;
    BruterList *scaleIn_list = vrStereoConfig->data[7].p;

    VrStereoConfig config;

    for (int i = 0; i < 2; i++)
    {
        config.projection[i] = matrix_constructor(projecton_list->data[i].p);
        config.viewOffset[i] = matrix_constructor(viewOffset_list->data[i].p);
        config.leftLensCenter[i] = leftLensCenter_list->data[i].f;
        config.rightLensCenter[i] = rightLensCenter_list->data[i].f;
        config.leftScreenCenter[i] = leftScreenCenter_list->data[i].f;
        config.rightScreenCenter[i] = rightScreenCenter_list->data[i].f;
        config.scale[i] = scale_list->data[i].f;
        config.scaleIn[i] = scaleIn_list->data[i].f;
    }

    return config;
}

// need revision!!!!!!
BruterList *vr_stereo_config_to_list(VrStereoConfig config)
{
    BruterList *list = bruter_new(BRUTER_DEFAULT_SIZE, true, true);

    BruterList *projection_list = bruter_new(2, true, true);
    for (int i = 0; i < 2; i++)
    {
        bruter_push_pointer(projection_list, matrix_to_list(config.projection[i]), "projection", BRUTER_TYPE_LIST);
    }
    bruter_push_pointer(list, projection_list, "projection", BRUTER_TYPE_LIST);

    BruterList *viewOffset_list = bruter_new(2, true, true);
    for (int i = 0; i < 2; i++)
    {
        bruter_push_pointer(viewOffset_list, matrix_to_list(config.viewOffset[i]), "viewOffset", BRUTER_TYPE_LIST);
    }
    bruter_push_pointer(list, viewOffset_list, "viewOffset", BRUTER_TYPE_LIST);

    for (int i = 0; i < 2; i++)
    {
        bruter_push_float(list, config.leftLensCenter[i], "leftLensCenter", BRUTER_TYPE_FLOAT);
        bruter_push_float(list, config.rightLensCenter[i], "rightLensCenter", BRUTER_TYPE_FLOAT);
        bruter_push_float(list, config.leftScreenCenter[i], "leftScreenCenter", BRUTER_TYPE_FLOAT);
        bruter_push_float(list, config.rightScreenCenter[i], "rightScreenCenter", BRUTER_TYPE_FLOAT);
        bruter_push_float(list, config.scale[i], "scale", BRUTER_TYPE_FLOAT);
        bruter_push_float(list, config.scaleIn[i], "scaleIn", BRUTER_TYPE_FLOAT);
    }

    return list;
}

// need revision
FilePathList file_path_list_constructor(BruterList *filePathList)
{
    unsigned int capacity = filePathList->data[0].i;
    unsigned int count = filePathList->data[1].i;
    char **paths = filePathList->data[2].p;

    FilePathList list;
    list.capacity = capacity;
    list.count = count;
    list.paths = paths;

    return list;
}

// need revision, maybe using a regular bruter list for this is not a bad idea
BruterList *file_path_list_to_list(FilePathList list)
{
    BruterList *bruterList = bruter_new(3, true, true);
    bruter_push_int(bruterList, list.capacity, "capacity", BRUTER_TYPE_ANY);
    bruter_push_int(bruterList, list.count, "count", BRUTER_TYPE_ANY);
    bruter_push_pointer(bruterList, list.paths, "paths", BRUTER_TYPE_BUFFER);
    return bruterList;
}

AutomationEvent automation_event_constructor(BruterList *automationEvent)
{
    unsigned int frame = automationEvent->data[0].i;
    unsigned int type = automationEvent->data[1].i;
    BruterList *params_list = automationEvent->data[2].p;

    AutomationEvent event;
    event.frame = frame;
    event.type = type;

    for (int i = 0; i < params_list->size && i < 4; i++) 
    {
        event.params[i] = params_list->data[i].i;
    }

    return event;
}

BruterList *automation_event_to_list(AutomationEvent event)
{
    BruterList *list = bruter_new(3, true, true);
    bruter_push_int(list, event.frame, "frame", BRUTER_TYPE_ANY);
    bruter_push_int(list, event.type, "type", BRUTER_TYPE_ANY);

    BruterList *params_list = bruter_new(4, true, true);
    for (int i = 0; i < 4; i++) 
    {
        bruter_push_int(params_list, event.params[i], "param", BRUTER_TYPE_ANY);
    }
    
    bruter_push_pointer(list, params_list, "params", BRUTER_TYPE_LIST);
    return list;
}

// need revision
AutomationEventList automation_event_list_constructor(BruterList *automationEventList)
{
    unsigned int capacity = automationEventList->data[0].i;
    unsigned int count = automationEventList->data[1].i;
    AutomationEvent *events = automationEventList->data[2].p;

    AutomationEventList list;
    list.capacity = capacity;
    list.count = count;
    list.events = events;

    return list;
}

// maybe using a regular bruter list for this is not a bad idea
BruterList *automation_event_list_to_list(AutomationEventList list)
{
    BruterList *bruterList = bruter_new(3, true, true);
    bruter_push_int(bruterList, list.capacity, "capacity", BRUTER_TYPE_ANY);
    bruter_push_int(bruterList, list.count, "count", BRUTER_TYPE_ANY);
    bruter_push_pointer(bruterList, list.events, "events", BRUTER_TYPE_BUFFER);
    return bruterList;
}

// raylib functions
function(feraw_InitWindow)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    char *title = (char*)bruter_pop_pointer(stack);
    InitWindow(width, height, title);
}

function(feraw_CloseWindow)
{
    CloseWindow();
}

function(feraw_WindowShouldClose)
{
    bool shouldClose = WindowShouldClose();
    bruter_push_int(stack, shouldClose, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowReady)
{
    bool isReady = IsWindowReady();
    bruter_push_int(stack, isReady, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowFullscreen)
{
    bool isFullscreen = IsWindowFullscreen();
    bruter_push_int(stack, isFullscreen, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowHidden)
{
    bool isHidden = IsWindowHidden();
    bruter_push_int(stack, isHidden, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowMinimized)
{
    bool isMinimized = IsWindowMinimized();
    bruter_push_int(stack, isMinimized, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowMaximized)
{
    bool isMaximized = IsWindowMaximized();
    bruter_push_int(stack, isMaximized, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowFocused)
{
    bool isFocused = IsWindowFocused();
    bruter_push_int(stack, isFocused, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowResized)
{
    bool isResized = IsWindowResized();
    bruter_push_int(stack, isResized, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsWindowState)
{
    int flags = bruter_pop_int(stack);
    bool isState = IsWindowState(flags);
    bruter_push_int(stack, isState, NULL, BRUTER_TYPE_ANY);
}

function(feraw_SetWindowState)
{
    int flags = bruter_pop_int(stack);
    SetWindowState(flags);
}

function(feraw_ClearWindowState)
{
    int flags = bruter_pop_int(stack);
    ClearWindowState(flags);
}

function(feraw_ToggleFullscreen)
{
    ToggleFullscreen();
}

function(feraw_ToggleBorderlessWindowed)
{
    ToggleBorderlessWindowed();
}

function(feraw_MaximizeWindow)
{
    MaximizeWindow();
}

function(feraw_MinimizeWindow)
{
    MinimizeWindow();
}

function(feraw_RestoreWindow)
{
    RestoreWindow();
}

function(feraw_SetWindowIcon)
{
    Image icon = image_constructor(bruter_pop_pointer(stack));
    SetWindowIcon(icon);
}

function(feraw_SetWindowIcons)
{
    Image *icons = (Image*)bruter_pop_pointer(stack);
    int count = bruter_pop_int(stack);
    SetWindowIcons(icons, count);
}

function(feraw_SetWindowTitle)
{
    char *title = (char*)bruter_pop_pointer(stack);
    SetWindowTitle(title);
}

function(feraw_SetWindowPosition)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    SetWindowPosition(x, y);
}

function(feraw_SetWindowMonitor)
{
    int monitor = bruter_pop_int(stack);
    SetWindowMonitor(monitor);
}

function(feraw_SetWindowMinSize)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowMinSize(width, height);
}

function(feraw_SetWindowMaxSize)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowMaxSize(width, height);
}

function(feraw_SetWindowSize)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowSize(width, height);
}

function(feraw_SetWindowOpacity)
{
    float opacity = bruter_pop_float(stack);
    SetWindowOpacity(opacity);
}

function(feraw_SetWindowFocused)
{
    SetWindowFocused();
}

function(feraw_GetWindowHandle)
{
    bruter_push_pointer(stack, GetWindowHandle(), NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetScreenWidth)
{
    int width = GetScreenWidth();
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetScreenHeight)
{
    int height = GetScreenHeight();
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMonitorCount)
{
    int count = GetMonitorCount();
    bruter_push_int(stack, count, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetCurrentMonitor)
{
    int monitor = GetCurrentMonitor();
    bruter_push_int(stack, monitor, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMonitorPosition)
{
    int monitor = bruter_pop_int(stack);
    Vector2 position = GetMonitorPosition(monitor);
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetMonitorWidth)
{
    int monitor = bruter_pop_int(stack);
    int width = GetMonitorWidth(monitor);
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMonitorHeight)
{
    int monitor = bruter_pop_int(stack);
    int height = GetMonitorHeight(monitor);
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMonitorPhysicalWidth)
{
    int monitor = bruter_pop_int(stack);
    int width = GetMonitorPhysicalWidth(monitor);
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMonitorPhysicalHeight)
{
    int monitor = bruter_pop_int(stack);
    int height = GetMonitorPhysicalHeight(monitor);
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMonitorRefreshRate)
{
    int monitor = bruter_pop_int(stack);
    int refreshRate = GetMonitorRefreshRate(monitor);
    bruter_push_int(stack, refreshRate, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetWindowPosition)
{
    Vector2 position = GetWindowPosition();
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetWindowScaleDpi)
{
    Vector2 scale = GetWindowScaleDPI();
    bruter_push_pointer(stack, vector2_to_list(scale), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetMonitorName)
{
    int monitor = bruter_pop_int(stack);
    const char *name = GetMonitorName(monitor);
    bruter_push_pointer(stack, strdup(name), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_SetClipboardText)
{
    char *text = (char*)bruter_pop_pointer(stack);
    SetClipboardText(text);
}

function(feraw_GetClipboardText)
{
    const char *text = GetClipboardText();
    bruter_push_pointer(stack, strdup(text), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_GetClipboardImage)
{
    Image image = GetClipboardImage();
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_EnableEventWaiting)
{
    EnableEventWaiting();
}

function(feraw_DisableEventWaiting)
{
    DisableEventWaiting();
}

// Cursor-related functions
function(feraw_ShowCursor)
{
    ShowCursor();
}

function(feraw_HideCursor)
{
    HideCursor();
}

function(feraw_IsCursorHidden)
{
    bool isHidden = IsCursorHidden();
    bruter_push_int(stack, isHidden, NULL, BRUTER_TYPE_ANY);
}

function(feraw_EnableCursor)
{
    EnableCursor();
}

function(feraw_DisableCursor)
{
    DisableCursor();
}

function(feraw_IsCursorOnScreen)
{
    bool isOnScreen = IsCursorOnScreen();
    bruter_push_int(stack, isOnScreen, NULL, BRUTER_TYPE_ANY);
}

// Drawing-related functions
function(feraw_ClearBackground)
{
    Color color = color_from_int(bruter_pop_int(stack));
    ClearBackground(color);
}

function(feraw_BeginDrawing)
{
    BeginDrawing();
}

function(feraw_EndDrawing)
{
    EndDrawing();
}

function(feraw_BeginMode2D)
{
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    BeginMode2D(camera);
}

function(feraw_EndMode2D)
{
    EndMode2D();
}

function(feraw_BeginMode3D)
{
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    BeginMode3D(camera);
}

function(feraw_EndMode3D)
{
    EndMode3D();
}

function(feraw_BeginShaderMode)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    BeginShaderMode(shader);
}

function(feraw_EndShaderMode)
{
    EndShaderMode();
}

function(feraw_BeginBlendMode)
{
    int mode = bruter_pop_int(stack);
    BeginBlendMode(mode);
}

function(feraw_EndBlendMode)
{
    EndBlendMode();
}

function(feraw_BeginScissorMode)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    BeginScissorMode(x, y, width, height);
}

function(feraw_EndScissorMode)
{
    EndScissorMode();
}

function(feraw_BeginVrStereoMode)
{
    VrStereoConfig config = vr_stereo_config_constructor(bruter_pop_pointer(stack));
    BeginVrStereoMode(config);
}

function(feraw_EndVrStereoMode)
{
    EndVrStereoMode();
}

function(feraw_LoadVrStereoConfig)
{
    VrDeviceInfo info = vr_device_info_constructor(bruter_pop_pointer(stack));
    VrStereoConfig config = LoadVrStereoConfig(info);
    bruter_push_pointer(stack, vr_stereo_config_to_list(config), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadVrStereoConfig)
{
    VrStereoConfig config = vr_stereo_config_constructor(bruter_pop_pointer(stack));
    UnloadVrStereoConfig(config);
}

function(feraw_LoadShader)
{
    char *vsFileName = (char*)bruter_pop_pointer(stack);
    char *fsFileName = (char*)bruter_pop_pointer(stack);
    Shader shader = LoadShader(vsFileName, fsFileName);
    bruter_push_pointer(stack, shader_to_list(shader), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadShaderFromMemory)
{
    char *vsCode = (char*)bruter_pop_pointer(stack);
    char *fsCode = (char*)bruter_pop_pointer(stack);
    Shader shader = LoadShaderFromMemory(vsCode, fsCode);
    bruter_push_pointer(stack, shader_to_list(shader), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsShaderValid)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    bool isValid = IsShaderValid(shader);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetShaderLocation)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    char *uniformName = (char*)bruter_pop_pointer(stack);
    int location = GetShaderLocation(shader, uniformName);
    bruter_push_int(stack, location, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetShaderLocationAttrib)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    char *attribName = (char*)bruter_pop_pointer(stack);
    int location = GetShaderLocationAttrib(shader, attribName);
    bruter_push_int(stack, location, NULL, BRUTER_TYPE_ANY);
}

function(feraw_SetShaderValue)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    const void *value = bruter_pop_pointer(stack);
    int uniformType = bruter_pop_int(stack);

    SetShaderValue(shader, locIndex, value, uniformType);
}

function(feraw_SetShaderValueMatrix)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    Matrix mat = matrix_constructor(bruter_pop_pointer(stack));

    SetShaderValueMatrix(shader, locIndex, mat);
}

function(feraw_SetShaderValueTexture)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));

    SetShaderValueTexture(shader, locIndex, texture);
}

function(feraw_UnloadShader)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    UnloadShader(shader);
}

function(feraw_GetScreenToWorldRay)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Ray ray = GetScreenToWorldRay(position, camera);
    bruter_push_pointer(stack, ray_to_list(ray), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetScreenToWorldRayEx)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Ray ray = GetScreenToWorldRayEx(position, camera, width, height);
    bruter_push_pointer(stack, ray_to_list(ray), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetWorldToScreen)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Vector2 screenPos = GetWorldToScreen(position, camera);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetWorldToScreenEx)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Vector2 screenPos = GetWorldToScreenEx(position, camera, width, height);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetWorldToScreen2D)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Vector2 screenPos = GetWorldToScreen2D(position, camera);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetScreenToWorld2D)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Vector2 worldPos = GetScreenToWorld2D(position, camera);
    bruter_push_pointer(stack, vector2_to_list(worldPos), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetCameraMatrix)
{
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Matrix matrix = GetCameraMatrix(camera);
    bruter_push_pointer(stack, matrix_to_list(matrix), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetCameraMatrix2D)
{
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Matrix matrix = GetCameraMatrix2D(camera);
    bruter_push_pointer(stack, matrix_to_list(matrix), NULL, BRUTER_TYPE_LIST);
}

// Timing-related functions
function(feraw_SetTargetFPS)
{
    int fps = bruter_pop_int(stack);
    SetTargetFPS(fps);
}

function(feraw_GetFrameTime)
{
    float frameTime = GetFrameTime();
    bruter_push_float(stack, frameTime, NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_GetTime)
{
    double time = GetTime();
    bruter_push_float(stack, (float)time, NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_GetFPS)
{
    int fps = GetFPS();
    bruter_push_int(stack, fps, NULL, BRUTER_TYPE_ANY);
}

// Custom frame control functions
function(feraw_SwapScreenBuffer)
{
    SwapScreenBuffer();
}

function(feraw_PollInputEvents)
{
    PollInputEvents();
}

function(feraw_WaitTime)
{
    float seconds = bruter_pop_float(stack);
    WaitTime(seconds);
}

// Random values generation functions
function(feraw_SetRandomSeed)
{
    unsigned int seed = bruter_pop_int(stack);
    SetRandomSeed(seed);
}

function(feraw_GetRandomValue)
{
    int min = bruter_pop_int(stack);
    int max = bruter_pop_int(stack);
    int value = GetRandomValue(min, max);
    bruter_push_int(stack, value, NULL, BRUTER_TYPE_ANY);
}

function(feraw_LoadRandomSequence)
{
    unsigned int count = bruter_pop_int(stack);
    int min = bruter_pop_int(stack);
    int max = bruter_pop_int(stack);
    int *sequence = LoadRandomSequence(count, min, max);
    bruter_push_pointer(stack, sequence, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_UnloadRandomSequence)
{
    int *sequence = (int*)bruter_pop_pointer(stack);
    UnloadRandomSequence(sequence);
}

// Misc. functions
function(feraw_TakeScreenshot)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    TakeScreenshot(fileName);
}

function(feraw_SetConfigFlags)
{
    unsigned int flags = bruter_pop_int(stack);
    SetConfigFlags(flags);
}

function(feraw_OpenUrl)
{
    char *url = (char*)bruter_pop_pointer(stack);
    OpenURL(url);
}

// utils functions
function(feraw_TraceLog)
{
    printf("feraw_TraceLog is not implemented in bruter yet\n");
}

function(feraw_SetTraceLogLevel)
{
    int logLevel = bruter_pop_int(stack);
    SetTraceLogLevel(logLevel);
}

function(feraw_MemAlloc)
{
    unsigned int size = bruter_pop_int(stack);
    void *ptr = MemAlloc(size);
    bruter_push_pointer(stack, ptr, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_MemRealloc)
{
    void *ptr = bruter_pop_pointer(stack);
    unsigned int size = bruter_pop_int(stack);
    void *newPtr = MemRealloc(ptr, size);
    bruter_push_pointer(stack, newPtr, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_MemFree)
{
    void *ptr = bruter_pop_pointer(stack);
    MemFree(ptr);
}

// custom callbacks, probably not working
function(feraw_SetTracelogCallback)
{
    TraceLogCallback callback = (TraceLogCallback)bruter_pop_pointer(stack);
    SetTraceLogCallback(callback);
}

function(feraw_SetLoadFileDataCallback)
{
    LoadFileDataCallback callback = (LoadFileDataCallback)bruter_pop_pointer(stack);
    SetLoadFileDataCallback(callback);
}

function(feraw_SetSaveFileDataCallback)
{
    SaveFileDataCallback callback = (SaveFileDataCallback)bruter_pop_pointer(stack);
    SetSaveFileDataCallback(callback);
}

function(feraw_SetLoadFileTextCallback)
{
    LoadFileTextCallback callback = (LoadFileTextCallback)bruter_pop_pointer(stack);
    SetLoadFileTextCallback(callback);
}

function(feraw_SetSaveFileTextCallback)
{
    SaveFileTextCallback callback = (SaveFileTextCallback)bruter_pop_pointer(stack);
    SetSaveFileTextCallback(callback);
}

// Files management functions
function(feraw_LoadFileData)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int bytesRead = 0;
    void *data = LoadFileData(fileName, &bytesRead);
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, data, "data", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, bytesRead, "bytesRead", BRUTER_TYPE_ANY);
    bruter_push_pointer(stack, list, NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadFileData)
{
    void *data = bruter_pop_pointer(stack);
    UnloadFileData(data);
}

function(feraw_SaveFileData)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    unsigned int bytesToWrite = bruter_pop_int(stack);
    bool success = SaveFileData(fileName, data, bytesToWrite);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(feraw_ExportDataAsCode)
{
    unsigned char *data = (unsigned char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportDataAsCode(data, dataSize, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(feraw_LoadFileText)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *text = LoadFileText(fileName);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_UnloadFileText)
{
    char *text = (char*)bruter_pop_pointer(stack);
    UnloadFileText(text);
}

function(feraw_SaveFileText)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *text = (char*)bruter_pop_pointer(stack);
    bool success = SaveFileText(fileName, text);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// File system functions
function(feraw_FileExists)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool exists = FileExists(fileName);
    bruter_push_int(stack, exists, NULL, BRUTER_TYPE_ANY);
}

function(feraw_DirectoryExists)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool exists = DirectoryExists(dirPath);
    bruter_push_int(stack, exists, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsFileExtension)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *ext = (char*)bruter_pop_pointer(stack);
    bool isExt = IsFileExtension(fileName, ext);
    bruter_push_int(stack, isExt, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetFileLength)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    unsigned int length = GetFileLength(fileName);
    bruter_push_int(stack, length, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetFileExtension)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    const char *ext = GetFileExtension(fileName);
    bruter_push_pointer(stack, strdup(ext), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_GetFileName)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *fileName = GetFileName(filePath);
    bruter_push_pointer(stack, strdup(fileName), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_GetFileNameWithoutExt)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *fileNameWithoutExt = GetFileNameWithoutExt(filePath);
    bruter_push_pointer(stack, strdup(fileNameWithoutExt), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_GetDirectoryPath)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *dirPath = GetDirectoryPath(filePath);
    bruter_push_pointer(stack, strdup(dirPath), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_GetPrevDirectoryPath)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *prevDirPath = GetPrevDirectoryPath(filePath);
    bruter_push_pointer(stack, strdup(prevDirPath), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_GetWorkingDirectory)
{
    const char *workingDir = GetWorkingDirectory();
    bruter_push_pointer(stack, strdup(workingDir), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_GetApplicationDirectory)
{
    const char *appDir = GetApplicationDirectory();
    bruter_push_pointer(stack, strdup(appDir), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_MakeDirectory)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool success = MakeDirectory(dirPath);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(feraw_ChangeDirectory)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool success = ChangeDirectory(dirPath);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsPathFile)
{
    char *path = (char*)bruter_pop_pointer(stack);
    bool isFile = IsPathFile(path);
    bruter_push_int(stack, isFile, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsFilenameValid)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool isValid = IsFileNameValid(fileName);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_LoadDirectoryFiles)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    FilePathList filePathList = LoadDirectoryFiles(dirPath);
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadDirectoryFilesEx)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    const char* filter = (const char*)bruter_pop_pointer(stack);
    bool scanSubdirs = bruter_pop_int(stack);
    FilePathList filePathList = LoadDirectoryFilesEx(dirPath, filter, scanSubdirs);
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadDirectoryFiles)
{
    FilePathList filePathList = file_path_list_constructor(bruter_pop_pointer(stack));
    UnloadDirectoryFiles(filePathList);
}

function(feraw_IsFileDropped)
{
    bool isDropped = IsFileDropped();
    bruter_push_int(stack, isDropped, NULL, BRUTER_TYPE_ANY);
}

function(feraw_LoadDroppedFiles)
{
    FilePathList filePathList = LoadDroppedFiles();
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadDroppedFiles)
{
    FilePathList filePathList = file_path_list_constructor(bruter_pop_pointer(stack));
    UnloadDroppedFiles(filePathList);
}

function(feraw_GetFileModTime)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    long modTime = GetFileModTime(fileName);
    bruter_push_int(stack, (int)modTime, NULL, BRUTER_TYPE_ANY);
}

// Compression/Encoding functionality
function(feraw_CompressData)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *compDataSize = (int*)bruter_pop_pointer(stack);
    void *compressedData = CompressData(data, dataSize, compDataSize);
    bruter_push_pointer(stack, compressedData, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_DecompressData)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *decompDataSize = (int*)bruter_pop_pointer(stack);
    void *decompressedData = DecompressData(data, dataSize, decompDataSize);
    bruter_push_pointer(stack, decompressedData, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_EncodeDataBase64)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *outputSize = (int*)bruter_pop_pointer(stack);
    char *encodedData = EncodeDataBase64(data, dataSize, outputSize);
    bruter_push_pointer(stack, encodedData, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_DecodeDataBase64)
{
    const unsigned char *encodedData = (const unsigned char*)bruter_pop_pointer(stack);
    int *decodedDataSize = (int*)bruter_pop_pointer(stack);
    void *decodedData = DecodeDataBase64(encodedData, decodedDataSize);
    bruter_push_pointer(stack, decodedData, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_ComputeCrc32)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    unsigned int crc = ComputeCRC32(data, dataSize);
    bruter_push_int(stack, crc, NULL, BRUTER_TYPE_ANY);
}

function(feraw_ComputeMd5)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    ComputeMD5(data, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_ComputeSha1)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    ComputeSHA1(data, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

// Automation events functionality
function(feraw_LoadAutomationEventList)
{
    BruterList *automation_event_list = bruter_pop_pointer(stack);
    AutomationEventList eventList = automation_event_list_constructor(automation_event_list);
    bruter_push_pointer(stack, automation_event_list_to_list(eventList), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadAutomationEventList)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    UnloadAutomationEventList(eventList);
}

function(feraw_ExportAutomationEventList)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportAutomationEventList(eventList, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// needs revision!!!!!
function(feraw_SetAutomationEventList)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    SetAutomationEventList(&eventList);
}

function(feraw_SetAutomationEventBaseFrame)
{
    int baseFrame = bruter_pop_int(stack);
    SetAutomationEventBaseFrame(baseFrame);
}

function(feraw_StartAutomationEventRecording)
{
    StartAutomationEventRecording();
}

function(feraw_StopAutomationEventRecording)
{
    StopAutomationEventRecording();
}

function(feraw_PlayAutomationEvent)
{
    AutomationEvent eventList = automation_event_constructor(bruter_pop_pointer(stack));
    PlayAutomationEvent(eventList);
}

// input-related functions: keyboard
function(feraw_IsKeyPressed)
{
    int key = bruter_pop_int(stack);
    bool isPressed = IsKeyPressed(key);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsKeyPressedRepeat)
{
    int key = bruter_pop_int(stack);
    bool isPressedRepeat = IsKeyPressedRepeat(key);
    bruter_push_int(stack, isPressedRepeat, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsKeyDown)
{
    int key = bruter_pop_int(stack);
    bool isDown = IsKeyDown(key);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsKeyReleased)
{
    int key = bruter_pop_int(stack);
    bool isReleased = IsKeyReleased(key);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsKeyUp)
{
    int key = bruter_pop_int(stack);
    bool isUp = IsKeyUp(key);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetKeyPressed)
{
    int key = GetKeyPressed();
    bruter_push_int(stack, key, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetCharPressed)
{
    int charCode = GetCharPressed();
    bruter_push_int(stack, charCode, NULL, BRUTER_TYPE_ANY);
}

function(feraw_SetExitKey)
{
    int key = bruter_pop_int(stack);
    SetExitKey(key);
}

// input-related functions: gamepads
function(feraw_IsGamepadAvailable)
{
    int gamepad = bruter_pop_int(stack);
    bool isAvailable = IsGamepadAvailable(gamepad);
    bruter_push_int(stack, isAvailable, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetGamepadName)
{
    int gamepad = bruter_pop_int(stack);
    const char *name = GetGamepadName(gamepad);
    bruter_push_pointer(stack, strdup(name), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_IsGamepadButtonPressed)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isPressed = IsGamepadButtonPressed(gamepad, button);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsGamepadButtonDown)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isDown = IsGamepadButtonDown(gamepad, button);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsGamepadButtonReleased)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isReleased = IsGamepadButtonReleased(gamepad, button);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsGamepadButtonUp)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isUp = IsGamepadButtonUp(gamepad, button);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetGamepadButtonPressed)
{
    int gamepad = bruter_pop_int(stack);
    int button = GetGamepadButtonPressed();
    bruter_push_int(stack, button, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetGamepadAxisCount)
{
    int gamepad = bruter_pop_int(stack);
    int axisCount = GetGamepadAxisCount(gamepad);
    bruter_push_int(stack, axisCount, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetGamepadAxisMovement)
{
    int gamepad = bruter_pop_int(stack);
    int axis = bruter_pop_int(stack);
    float movement = GetGamepadAxisMovement(gamepad, axis);
    bruter_push_float(stack, movement, NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_SetGamepadMappings)
{
    char *mapping = (char*)bruter_pop_pointer(stack);
    bool success = SetGamepadMappings(mapping);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(feraw_SetGamepadVibration)
{
    int gamepad = bruter_pop_int(stack);
    float leftVibration = bruter_pop_float(stack);
    float rightVibration = bruter_pop_float(stack);
    float duration = bruter_pop_float(stack);
    SetGamepadVibration(gamepad, leftVibration, rightVibration, duration);
}

// input-related functions: mouse
function(feraw_IsMouseButtonPressed)
{
    int button = bruter_pop_int(stack);
    bool isPressed = IsMouseButtonPressed(button);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsMouseButtonDown)
{
    int button = bruter_pop_int(stack);
    bool isDown = IsMouseButtonDown(button);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsMouseButtonReleased)
{
    int button = bruter_pop_int(stack);
    bool isReleased = IsMouseButtonReleased(button);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

function(feraw_IsMouseButtonUp)
{
    int button = bruter_pop_int(stack);
    bool isUp = IsMouseButtonUp(button);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMouseX)
{
    int x = GetMouseX();
    bruter_push_int(stack, x, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMouseY)
{
    int y = GetMouseY();
    bruter_push_int(stack, y, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMousePosition)
{
    Vector2 position = GetMousePosition();
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetMouseDelta)
{
    Vector2 delta = GetMouseDelta();
    bruter_push_pointer(stack, vector2_to_list(delta), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetMousePosition)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    SetMousePosition(x, y);
}

function(feraw_SetMouseOffset)
{
    int offsetX = bruter_pop_int(stack);
    int offsetY = bruter_pop_int(stack);
    SetMouseOffset(offsetX, offsetY);
}

function(feraw_SetMouseScale)
{
    float scaleX = bruter_pop_float(stack);
    float scaleY = bruter_pop_float(stack);
    SetMouseScale(scaleX, scaleY);
}

function(feraw_GetMouseWheelMove)
{
    float wheelMove = GetMouseWheelMove();
    bruter_push_float(stack, wheelMove, NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_SetMouseCursor)
{
    int cursor = bruter_pop_int(stack);
    SetMouseCursor(cursor);
}

// input-related functions: touch

function(feraw_GetTouchX)
{
    int touchX = GetTouchX();
    bruter_push_int(stack, touchX, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetTouchY)
{
    int touchY = GetTouchY();
    bruter_push_int(stack, touchY, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetTouchPosition)
{
    int index = bruter_pop_int(stack);
    Vector2 position = GetTouchPosition(index);
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetTouchPointId)
{
    int index = bruter_pop_int(stack);
    int id = GetTouchPointId(index);
    bruter_push_int(stack, id, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetTouchPointCount)
{
    int count = GetTouchPointCount();
    bruter_push_int(stack, count, NULL, BRUTER_TYPE_ANY);
}

// Gestures and Touch Handling functions
function(feraw_SetGesturesEnabled)
{
    unsigned int gestureFlags = bruter_pop_int(stack);
    SetGesturesEnabled(gestureFlags);
}

function(feraw_IsGestureDetected)
{
    int gesture = bruter_pop_int(stack);
    bool detected = IsGestureDetected(gesture);
    bruter_push_int(stack, detected, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetGestureDetected)
{
    int gesture = GetGestureDetected();
    bruter_push_int(stack, gesture, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetGestureHoldDuration)
{
    float duration = GetGestureHoldDuration();
    bruter_push_float(stack, duration, NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_GetGestureDragVector)
{
    Vector2 dragVector = GetGestureDragVector();
    bruter_push_pointer(stack, vector2_to_list(dragVector), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetGestureDragAngle)
{
    float angle = GetGestureDragAngle();
    bruter_push_float(stack, angle, NULL, BRUTER_TYPE_FLOAT);
}

function(feraw_GetGesturePinchVector)
{
    Vector2 pinchVector = GetGesturePinchVector();
    bruter_push_pointer(stack, vector2_to_list(pinchVector), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetGesturePinchAngle)
{
    float angle = GetGesturePinchAngle();
    bruter_push_float(stack, angle, NULL, BRUTER_TYPE_FLOAT);
}

// Camera system functions
function(feraw_UpdateCamera)
{
    Camera3D *camera = (Camera3D*)bruter_pop_pointer(stack);
    int mode = bruter_pop_int(stack);
    UpdateCamera(camera, mode);
}

function(feraw_UpdateCameraPro)
{
    Camera3D *camera = (Camera3D*)bruter_pop_pointer(stack);
    Vector3 move = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotation = vector3_constructor(bruter_pop_pointer(stack));
    float zoom = bruter_pop_float(stack);
    UpdateCameraPro(camera, move, rotation, zoom);
}

// basic shapes drawing functions
function(feraw_SetShapesTexture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle source = rectangle_constructor(bruter_pop_pointer(stack));
    SetShapesTexture(texture, source);
}

function(feraw_GetShapesTexture)
{
    Texture2D texture = GetShapesTexture();
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetShapesTextureRectangle)
{
    Rectangle source = GetShapesTextureRectangle();
    bruter_push_pointer(stack, rectangle_to_list(source), NULL, BRUTER_TYPE_LIST);
}

// basic shapes drawing functions
function(feraw_DrawPixel)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPixel(posX, posY, color);
}

function(feraw_DrawLine)
{
    int startX = bruter_pop_int(stack);
    int startY = bruter_pop_int(stack);
    int endX = bruter_pop_int(stack);
    int endY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLine(startX, startY, endX, endY, color);
}

function(feraw_DrawLineEx)
{
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineEx(start, end, thick, color);
}

function(feraw_DrawLineStrip)
{
    Vector2 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineStrip(points, pointCount, color);
}

function(feraw_DrawLineBezier)
{
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineBezier(start, end, thick, color);
}

function(feraw_DrawCircle)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircle(centerX, centerY, radius, color);
}

function(feraw_DrawCircleSector)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    float startAngle = bruter_pop_float(stack);
    float endAngle = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
}

function(feraw_DrawCircleSectorLines)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    float startAngle = bruter_pop_float(stack);
    float endAngle = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
}

function(feraw_DrawCircleGradient)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    Color innerColor = color_from_int(bruter_pop_int(stack));
    Color outerColor = color_from_int(bruter_pop_int(stack));
    DrawCircleGradient(centerX, centerY, radius, innerColor, outerColor);
}

function(feraw_DrawCircleLines)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleLines(centerX, centerY, radius, color);
}

function(feraw_DrawRectangle)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangle(posX, posY, width, height, color);
}
function(feraw_DrawRectangleRec)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRec(rec, color);
}

function(feraw_DrawRectanglePro)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectanglePro(rec, origin, rotation, color);
}

function(feraw_DrawRectangleGradientH)
{
    int posx = bruter_pop_int(stack);
    int posy = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color left = color_from_int(bruter_pop_int(stack));
    Color right = color_from_int(bruter_pop_int(stack));
    DrawRectangleGradientH(posx, posy, width, height, left, right);
}

function(feraw_DrawRectangleGradientEx)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    Color color3 = color_from_int(bruter_pop_int(stack));
    Color color4 = color_from_int(bruter_pop_int(stack));
    DrawRectangleGradientEx(rec, color1, color2, color3, color4);
}

function(feraw_DrawRectangleLines)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleLines(posX, posY, width, height, color);
}

function(feraw_DrawRectangleLinesEx)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleLinesEx(rec, thick, color);
}

function(feraw_DrawRectangleRounded)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRounded(rec, roundness, segments, color);
}

function(feraw_DrawRectangleRoundedLines)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRoundedLines(rec, roundness, segments, color);
}

function(feraw_DrawRectangleRoundedLinesEx)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRoundedLinesEx(rec, roundness, segments, thick, color);
}

function(feraw_DrawTriangle)
{
    Vector2 v1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangle(v1, v2, v3, color);
}

function(feraw_DrawTriangleLines)
{
    Vector2 v1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleLines(v1, v2, v3, color);
}

function(feraw_DrawTriangleFan)
{
    Vector2 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleFan(points, pointCount, color);
}

function(feraw_DrawTriangleStrip)
{
    Vector2 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleStrip(points, pointCount, color);
}

function(feraw_DrawPoly)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPoly(center, sides, radius, rotation, color);
}

function(feraw_DrawPolyLines)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPolyLines(center, sides, radius, rotation, color);
}

function(feraw_DrawPolyLinesEx)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    float rotation = bruter_pop_float(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPolyLinesEx(center, sides, radius, rotation, thick, color);
}

// splines drawing functions
function(feraw_DrawSplineLinear)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineLinear(points, pointCount, thick, color);
}

function(feraw_DrawSplineBasis)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBasis(points, pointCount, thick, color);
}

function(feraw_DrawSplineCatmullRom)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineCatmullRom(points, pointCount, thick, color);
}

function(feraw_DrawSplineBezierQuadratic)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBezierQuadratic(points, pointCount, thick, color);
}

function(feraw_DrawSplineBezierCubic)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBezierCubic(points, pointCount, thick, color);
}

function(feraw_DrawSplineSegmentLinear)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentLinear(p1, p2, thick, color);
}

function(feraw_DrawSplineSegmentBasis)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
}

function(feraw_DrawSplineSegmentCatmullRom)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
}

function(feraw_DrawSplineSegmentBezierQuadratic)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentBezierQuadratic(p1, p2, p3, thick, color);
}

function(feraw_DrawSplineSegmentBezierCubic)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentBezierCubic(p1, p2, p3, p4, thick, color);
}

// spline segment point evaluation functions
function(feraw_GetSplinePointLinear)
{
    Vector2 startPos = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 endPos = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointLinear(startPos, endPos, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetSplinePointBasis)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointBasis(p1, p2, p3, p4, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetSplinePointCatmullRom)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointCatmullRom(p1, p2, p3, p4, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetSplinePointBezierQuad)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointBezierQuad(p1, p2, p3, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetSplinePointBezierCubic)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointBezierCubic(p1, p2, p3, p4, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

// basic shapes collision detection functions
function(feraw_CheckCollisionRecs)
{
    Rectangle rec1 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle rec2 = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionRecs(rec1, rec2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionCircles)
{
    Vector2 center1 = vector2_constructor(bruter_pop_pointer(stack));
    float radius1 = bruter_pop_float(stack);
    Vector2 center2 = vector2_constructor(bruter_pop_pointer(stack));
    float radius2 = bruter_pop_float(stack);
    bool collision = CheckCollisionCircles(center1, radius1, center2, radius2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionCircleRec)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionCircleRec(center, radius, rec);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionCircleLine)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionCircleLine(center, radius, start, end);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionPointRec)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionPointRec(point, rec);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionPointCircle)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    bool collision = CheckCollisionPointCircle(point, center, radius);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionPointTriangle)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionPointTriangle(point, p1, p2, p3);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionPointLine)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    bool collision = CheckCollisionPointLine(point, start, end, threshold);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionPointPoly)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    bool collision = CheckCollisionPointPoly(point, points, pointCount);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionLines)
{
    Vector2 start1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 start2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 collisionPoint;
    bool collision = CheckCollisionLines(start1, end1, start2, end2, &collisionPoint);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
    bruter_push_pointer(stack, vector2_to_list(collisionPoint), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetCollisionRec)
{
    Rectangle rec1 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle rec2 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle collisionRec = GetCollisionRec(rec1, rec2);
    bruter_push_pointer(stack, rectangle_to_list(collisionRec), NULL, BRUTER_TYPE_LIST);
}

// image loading functions
function(feraw_LoadImage)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Image image = LoadImage(fileName);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadImageRaw)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int format = bruter_pop_int(stack);
    int headerSize = bruter_pop_int(stack);
    Image image = LoadImageRaw(fileName, width, height, format, headerSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadImageAnim)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *framesCount = (int*)bruter_pop_pointer(stack);
    Image images = LoadImageAnim(fileName, framesCount);
    bruter_push_pointer(stack, &images, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_LoadImageAnimFromMemory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    const unsigned char *fileData = (const unsigned char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *framesCount = (int*)bruter_pop_pointer(stack);
    Image images = LoadImageAnimFromMemory(fileType, fileData, dataSize, framesCount);
    bruter_push_pointer(stack, &images, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_LoadImageFromMemory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    const unsigned char *fileData = (const unsigned char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Image image = LoadImageFromMemory(fileType, fileData, dataSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadImageFromTexture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Image image = LoadImageFromTexture(texture);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadImageFromScreen)
{
    Image image = LoadImageFromScreen();
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsImageValid)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    bool isValid = IsImageValid(image);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UnloadImage)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    UnloadImage(image);
}

function(feraw_ExportImage)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportImage(image, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(feraw_ExportImageToMemory)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileType = (char*)bruter_pop_pointer(stack);
    int *dataSize = (int*)bruter_pop_pointer(stack);
    unsigned char *data = ExportImageToMemory(image, fileType, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_ExportImageAsCode)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportImageAsCode(image, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// image generation functions
function(feraw_GenImageColor)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    Image image = GenImageColor(width, height, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageGradientLinear)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int direction = bruter_pop_int(stack);
    Color start = color_from_int(bruter_pop_int(stack));
    Color end = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientLinear(width, height, direction, start, end);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageGradientRadial)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float density = bruter_pop_float(stack);
    Color inner = color_from_int(bruter_pop_int(stack));
    Color outer = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientRadial(width, height, density, inner, outer);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageGradientSquare)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float density = bruter_pop_float(stack);
    Color inner = color_from_int(bruter_pop_int(stack));
    Color outer = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientSquare(width, height, density, inner, outer);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageChecked)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int checksX = bruter_pop_int(stack);
    int checksY = bruter_pop_int(stack);
    Color col1 = color_from_int(bruter_pop_int(stack));
    Color col2 = color_from_int(bruter_pop_int(stack));
    Image image = GenImageChecked(width, height, checksX, checksY, col1, col2);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageWhiteNoise)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float factor = bruter_pop_float(stack);
    Image image = GenImageWhiteNoise(width, height, factor);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImagePerlinNoise)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int offsetX = bruter_pop_int(stack);
    int offsetY = bruter_pop_int(stack);
    float scale = bruter_pop_float(stack);
    Image image = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageCellular)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int tileSize = bruter_pop_int(stack);
    Image image = GenImageCellular(width, height, tileSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageText)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    char *text = (char*)bruter_pop_pointer(stack);
    Image image = GenImageText(width, height, text);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

// image manipulation functions

function(feraw_ImageCopy)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image copiedImage = ImageCopy(image);
    bruter_push_pointer(stack, image_to_list(copiedImage), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageFromImage)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Image subImage = ImageFromImage(image, rec);
    bruter_push_pointer(stack, image_to_list(subImage), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageFromChannel)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int channel = bruter_pop_int(stack);
    Image channelImage = ImageFromChannel(image, channel);
    bruter_push_pointer(stack, image_to_list(channelImage), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageText)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    Image image = ImageText(text, fontSize, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageTextEx)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    Image image = ImageTextEx(font, text, fontSize, spacing, tint);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageFormat)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newFormat = bruter_pop_int(stack);
    ImageFormat(&image, newFormat);
}

function(feraw_ImageToPot)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color fill = color_from_int(bruter_pop_int(stack));
    ImageToPOT(&image, fill);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageCrop)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle crop = rectangle_constructor(bruter_pop_pointer(stack));
    ImageCrop(&image, crop);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageAlphaCrop)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    ImageAlphaCrop(&image, threshold);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageAlphaClear)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    float threshold = bruter_pop_float(stack);
    ImageAlphaClear(&image, color, threshold);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageAlphaMask)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image mask = image_constructor(bruter_pop_pointer(stack));
    ImageAlphaMask(&image, mask);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageAlphaPremultiply)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageAlphaPremultiply(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageBlurGlaussian)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int blurSize = bruter_pop_int(stack);
    ImageBlurGaussian(&image, blurSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageKernelConvolution)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float *kernel = (float*)bruter_pop_pointer(stack);
    int kernelsize = bruter_pop_int(stack);
    ImageKernelConvolution(&image, kernel, kernelsize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageResize)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newWidth = bruter_pop_int(stack);
    int newHeight = bruter_pop_int(stack);
    ImageResize(&image, newWidth, newHeight);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageResizeNn)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newWidth = bruter_pop_int(stack);
    int newHeight = bruter_pop_int(stack);
    ImageResizeNN(&image, newWidth, newHeight);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageResizeCanvas)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newWidth = bruter_pop_int(stack);
    int newHeight = bruter_pop_int(stack);
    int offsetX = bruter_pop_int(stack);
    int offsetY = bruter_pop_int(stack);
    Color fill = color_from_int(bruter_pop_int(stack));
    ImageResizeCanvas(&image, newWidth, newHeight, offsetX, offsetY, fill);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageMipmaps)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageMipmaps(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDither)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int rBpp = bruter_pop_int(stack);
    int gBpp = bruter_pop_int(stack);
    int bBpp = bruter_pop_int(stack);
    int aBpp = bruter_pop_int(stack);
    ImageDither(&image, rBpp, gBpp, bBpp, aBpp);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageFlipVertical)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageFlipVertical(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageFlipHorizontal)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageFlipHorizontal(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageRotate)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float degrees = bruter_pop_float(stack);
    ImageRotate(&image, degrees);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageRotateCw)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageRotateCW(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageRotateCcw)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageRotateCCW(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageColorTint)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageColorTint(&image, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageColorInvert)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageColorInvert(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageColorGrayscale)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageColorGrayscale(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageColorContrast)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float contrast = bruter_pop_float(stack);
    ImageColorContrast(&image, contrast);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageColorBrightness)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int brightness = bruter_pop_int(stack);
    ImageColorBrightness(&image, brightness);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageColorReplace)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    Color replace = color_from_int(bruter_pop_int(stack));
    ImageColorReplace(&image, color, replace);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadImageColors)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color *colors = LoadImageColors(image);
    int colorCount = image.width * image.height;
    bruter_push_pointer(stack, colors, NULL, BRUTER_TYPE_BUFFER);
    bruter_push_int(stack, colorCount, NULL, BRUTER_TYPE_ANY);
}

function(feraw_LoadImagePalette)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int maxPaletteSize = bruter_pop_int(stack);
    int *colorCount = (int*)bruter_pop_pointer(stack);
    Color *palette = LoadImagePalette(image, maxPaletteSize, colorCount);
    bruter_push_pointer(stack, palette, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_UnloadImageColors)
{
    UnloadImageColors((Color*)bruter_pop_pointer(stack));
}

function(feraw_UnloadImagePalette)
{
    Color *palette = (Color*)bruter_pop_pointer(stack);
    UnloadImagePalette(palette);
}

function(feraw_GetImageAlphaBorder)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    Rectangle rec = GetImageAlphaBorder(image, threshold);
    bruter_push_pointer(stack, rectangle_to_list(rec), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetImageColor)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    Color color = GetImageColor(image, x, y);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

// image drawing functions
function(feraw_ImageClearBackground)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageClearBackground(&image, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawPixel)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawPixel(&image, posX, posY, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawLine)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int startX = bruter_pop_int(stack);
    int startY = bruter_pop_int(stack);
    int endX = bruter_pop_int(stack);
    int endY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawLine(&image, startX, startY, endX, endY, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawLineEx)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawLineEx(&image, start, end, thick, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawCircle)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircle(&image, centerX, centerY, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawCircleLines)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircleLines(&image, centerX, centerY, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawRectangle)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangle(&image, posX, posY, width, height, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawRectangleRec)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangleRec(&image, rec, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawRectangleLines)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    int thick = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangleLines(&image, rec, thick, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawTriangle)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangle(&image, p1, p2, p3, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawTriangleEx)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    Color color3 = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleEx(&image, p1, p2, p3, color1, color2, color3);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawTriangleLines)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleLines(&image, p1, p2, p3, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawTriangleFan)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleFan(&image, points, pointCount, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawTriangleStrip)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleStrip(&image, points, pointCount, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDraw)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image src = image_constructor(bruter_pop_pointer(stack));
    Rectangle srcRec = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle destRec = rectangle_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    ImageDraw(&image, src, srcRec, destRec, tint);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawText)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawText(&image, text, posX, posY, fontSize, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ImageDrawTextEx)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    ImageDrawTextEx(&image, font, text, position, fontSize, spacing, tint);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

// Texture

function(feraw_LoadTexture)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Texture2D texture = LoadTexture(fileName);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadTextureFromImage)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Texture2D texture = LoadTextureFromImage(image);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadTextureCubemap)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int layout = bruter_pop_int(stack); // Assuming layout is an int representing the cubemap layout
    TextureCubemap texture = LoadTextureCubemap(image, layout);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}


function(feraw_LoadRenderRexture)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    RenderTexture2D renderTexture = LoadRenderTexture(width, height);
    bruter_push_pointer(stack, render_texture_to_list(renderTexture), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsTextureValid)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    bool isValid = IsTextureValid(texture);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UnloadTexture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    UnloadTexture(texture);
}

function(feraw_IsRenderTextureValid)
{
    RenderTexture2D renderTexture = render_texture_constructor(bruter_pop_pointer(stack));
    bool isValid = IsRenderTextureValid(renderTexture);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UnloadRenderTexture)
{
    RenderTexture2D renderTexture = render_texture_constructor(bruter_pop_pointer(stack));
    UnloadRenderTexture(renderTexture);
}

function(feraw_UpdateTexture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    unsigned char *pixels = (unsigned char*)bruter_pop_pointer(stack);
    UpdateTexture(texture, pixels);
}

function(feraw_UpdateTextureRec)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    unsigned char *pixels = (unsigned char*)bruter_pop_pointer(stack);
    UpdateTextureRec(texture, rec, pixels);
}

// texture configuration functions
function(feraw_GenTextureMipmaps)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    GenTextureMipmaps(&texture);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetTextureFilter)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int filter = bruter_pop_int(stack);
    SetTextureFilter(texture, filter);
}

function(feraw_SetTextureWrap)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int wrap = bruter_pop_int(stack);
    SetTextureWrap(texture, wrap);
}

// texture drawing functions
function(feraw_DrawTexture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTexture(texture, posX, posY, tint);
}

function(feraw_DrawTextureEx)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureEx(texture, position, rotation, scale, tint);
}

function(feraw_DrawTextureRec)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureRec(texture, sourceRec, position, tint);
}

function(feraw_DrawTexturePro)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle destRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
}

function(feraw_DrawTextureNpatch)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    NPatchInfo nPatchInfo = npatch_info_constructor(bruter_pop_pointer(stack));
    Rectangle destRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureNPatch(texture, nPatchInfo, destRec, origin, rotation, tint);
}

// color/pixel related functions

function(feraw_ColorIsEqual)
{
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    bool isEqual = ColorIsEqual(color1, color2);
    bruter_push_int(stack, isEqual, NULL, BRUTER_TYPE_ANY);
}

function(feraw_FadeColor)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float alpha = bruter_pop_float(stack);
    Color fadedColor = Fade(color, alpha);
    bruter_push_int(stack, color_to_int(fadedColor), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorToInt)
{
    Color color = color_from_int(bruter_pop_int(stack));
    int colorInt = ColorToInt(color);
    bruter_push_int(stack, colorInt, NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorNormalize)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Vector4 normalizedColor = ColorNormalize(color);
    bruter_push_pointer(stack, vector4_to_list(normalizedColor), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ColorFromNormalized)
{
    Vector4 normalizedColor = vector4_constructor(bruter_pop_pointer(stack));
    Color color = ColorFromNormalized(normalizedColor);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorToHsv)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Vector3 hsv = ColorToHSV(color);
    bruter_push_pointer(stack, vector3_to_list(hsv), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ColorFromHsv)
{
    float hue = bruter_pop_float(stack);
    float saturation = bruter_pop_float(stack);
    float value = bruter_pop_float(stack);
    Color color = ColorFromHSV(hue, saturation, value);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorTint)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    Color tintedColor = ColorTint(color, tint);
    bruter_push_int(stack, color_to_int(tintedColor), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorBrightness)
{
    Color color = color_from_int(bruter_pop_int(stack));
    int brightness = bruter_pop_int(stack);
    Color brightenedColor = ColorBrightness(color, brightness);
    bruter_push_int(stack, color_to_int(brightenedColor), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorContrast)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float contrast = bruter_pop_float(stack);
    Color contrastedColor = ColorContrast(color, contrast);
    bruter_push_int(stack, color_to_int(contrastedColor), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorAlpha)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float alpha = bruter_pop_float(stack);
    Color alphaColor = ColorAlpha(color, alpha);
    bruter_push_int(stack, color_to_int(alphaColor), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorAlphaBlend)
{
    Color dst = color_from_int(bruter_pop_int(stack));
    Color src = color_from_int(bruter_pop_int(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    Color blendedColor = ColorAlphaBlend(dst, src, tint);
    bruter_push_int(stack, color_to_int(blendedColor), NULL, BRUTER_TYPE_ANY);
}

function(feraw_ColorLerp)
{
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    float amount = bruter_pop_float(stack);
    Color lerpedColor = ColorLerp(color1, color2, amount);
    bruter_push_int(stack, color_to_int(lerpedColor), NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetColor)
{
    int hexColor = bruter_pop_int(stack);
    Color color = GetColor(hexColor);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetPixelColor)
{
    void* data = bruter_pop_pointer(stack);
    int format = bruter_pop_int(stack);
    Color color = GetPixelColor(data, format);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(feraw_SetPixelColor)
{
    void *data = bruter_pop_pointer(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    int format = bruter_pop_int(stack);
    SetPixelColor(data, color, format);
}

function(feraw_GetPixelDataSize)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int format = bruter_pop_int(stack);
    int size = GetPixelDataSize(width, height, format);
    bruter_push_int(stack, size, NULL, BRUTER_TYPE_ANY);
}

// font loading/unloading functions

function(feraw_GetFontDefault)
{
    Font font = GetFontDefault();
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadFont)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Font font = LoadFont(fileName);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadFontEx)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    int *fontChars = (int*)bruter_pop_pointer(stack);
    int charsCount = bruter_pop_int(stack);
    Font font = LoadFontEx(fileName, fontSize, fontChars, charsCount);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadFontFromImage)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color key = color_from_int(bruter_pop_int(stack));
    int firstChar = bruter_pop_int(stack);
    Font font = LoadFontFromImage(image, key, firstChar);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadFontFromMemory)
{
    const char* fileType = (const char*)bruter_pop_pointer(stack);
    unsigned char *fileData = (unsigned char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    int *fontChars = (int*)bruter_pop_pointer(stack);
    int charsCount = bruter_pop_int(stack);
    Font font = LoadFontFromMemory(fileType, fileData, dataSize, fontSize, fontChars, charsCount);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsFontValid)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    bool isValid = IsFontValid(font);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_LoadFontData)
{
    void *fileData = (void*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    int *codepoints = (int*)bruter_pop_pointer(stack);
    int codepointCount = bruter_pop_int(stack);
    int type = bruter_pop_int(stack); // Assuming type is an int representing the font type
    GlyphInfo *fontData = LoadFontData(fileData, dataSize, fontSize, codepoints, codepointCount, type);
    bruter_push_pointer(stack, fontData, NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenImageFontAtlas)
{
    const GlyphInfo *fontData = (const GlyphInfo*)bruter_pop_pointer(stack);
    Rectangle **glyphRects = (Rectangle**)bruter_pop_pointer(stack);
    int glyphCount = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    int padding = bruter_pop_int(stack);
    int packMethod = bruter_pop_int(stack); // Assuming packMethod is an int representing the packing method
    Image atlas = GenImageFontAtlas(fontData, glyphRects, glyphCount, fontSize, padding, packMethod);
    bruter_push_pointer(stack, image_to_list(atlas), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadFontData)
{
    GlyphInfo *fontData = (GlyphInfo*)bruter_pop_pointer(stack);
    int glyphCount = bruter_pop_int(stack);
    UnloadFontData(fontData, glyphCount);
}

function(feraw_UnloadFont)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    UnloadFont(font);
}

function(feraw_ExportFontAsCode)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportFontAsCode(font, fileName);
}

// text drawing functions
function(feraw_DrawFPS)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    DrawFPS(posX, posY);
}

function(feraw_DrawText)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawText(text, posX, posY, fontSize, color);
}

function(feraw_DrawTextEx)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextEx(font, text, position, fontSize, spacing, tint);
}

function(feraw_DrawTextPro)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, tint);
}

function(feraw_DrawTextCodepoint)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextCodepoint(font, codepoint, position, fontSize, tint);
}

function(feraw_DrawTextCodepoints)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    const int *codepoints = (const int*)bruter_pop_pointer(stack);
    int codepointCount = bruter_pop_int(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextCodepoints(font, codepoints, codepointCount, position, fontSize, spacing, tint);
}

// text font info functions
function(feraw_SetTextLineSpacing)
{
    float spacing = bruter_pop_float(stack);
    SetTextLineSpacing(spacing);
}

function(feraw_MeasureText)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    int size = MeasureText(text, fontSize);
    bruter_push_int(stack, size, NULL, BRUTER_TYPE_ANY);
}

function(feraw_MeasureTextEx)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Vector2 size = MeasureTextEx(font, text, fontSize, spacing);
    bruter_push_pointer(stack, vector2_to_list(size), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetGlyphIndex)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    int glyphIndex = GetGlyphIndex(font, codepoint);
    bruter_push_int(stack, glyphIndex, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetGlyphInfo)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    GlyphInfo glyphInfo = GetGlyphInfo(font, codepoint);
    bruter_push_pointer(stack, glyph_info_to_list(glyphInfo), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetGlyphAtlasRec)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    Rectangle rec = GetGlyphAtlasRec(font, codepoint);
    bruter_push_pointer(stack, rectangle_to_list(rec), NULL, BRUTER_TYPE_LIST);
}

// text string managment functions
function(feraw_TextCopy)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *src = (char*)bruter_pop_pointer(stack);
    TextCopy(text, src);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextIsEqual)
{
    char *text1 = (char*)bruter_pop_pointer(stack);
    char *text2 = (char*)bruter_pop_pointer(stack);
    bool isEqual = TextIsEqual(text1, text2);
    bruter_push_int(stack, isEqual, NULL, BRUTER_TYPE_ANY);
}

function(feraw_TextLength)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int length = TextLength(text);
    bruter_push_int(stack, length, NULL, BRUTER_TYPE_ANY);
}

function(feraw_TextFormat)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *formattedText = strdup(TextFormat(text));
    bruter_push_pointer(stack, formattedText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextSubtext)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    int length = bruter_pop_int(stack);
    char *subText = strdup(TextSubtext(text, position, length));
    bruter_push_pointer(stack, subText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextReplace)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *find = (char*)bruter_pop_pointer(stack);
    char *replace = (char*)bruter_pop_pointer(stack);
    char *replacedText = TextReplace(text, find, replace);
    bruter_push_pointer(stack, replacedText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextInsert)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *insert = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    char *insertedText = TextInsert(text, insert, position);
    bruter_push_pointer(stack, insertedText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextJoin)
{
    const char **textList = bruter_pop_pointer(stack);
    int count = bruter_pop_int(stack);
    char *delimiter = (char*)bruter_pop_pointer(stack);
    const char *joinedText = TextJoin(textList, count, delimiter);
    bruter_push_pointer(stack, strdup(joinedText), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextSplit)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char delimiter = bruter_pop_int(stack);
    int count = 0;
    const char **splited = TextSplit(text, delimiter, &count);
    BruterList *splitedList = bruter_new(count, false, false);
    for (int i = 0; i < count; i++)
    {
        bruter_push_pointer(splitedList, strdup(splited[i]), NULL, BRUTER_TYPE_BUFFER);
    }
    bruter_push_pointer(stack, splitedList, NULL, BRUTER_TYPE_LIST);
}

function(feraw_TextAppend)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *appendText = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    TextAppend(text, appendText, &position);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextFindIndex)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *find = (char*)bruter_pop_pointer(stack);
    int index = TextFindIndex(text, find);
    bruter_push_int(stack, index, NULL, BRUTER_TYPE_ANY);
}

function(feraw_TextToUpper)
{
    char *text = (char*)bruter_pop_pointer(stack);
    const char *upperText = TextToUpper(text);
    bruter_push_pointer(stack, strdup(upperText), NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextToLower)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *lowerText = strdup(TextToLower(text));
    bruter_push_pointer(stack, lowerText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextToPascal)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *pascalText = strdup(TextToPascal(text));
    bruter_push_pointer(stack, pascalText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextToSnake)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *snakeText = strdup(TextToSnake(text));
    bruter_push_pointer(stack, snakeText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextToCamel)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *camelText = strdup(TextToCamel(text));
    bruter_push_pointer(stack, camelText, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_TextToInteger)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int value = TextToInteger(text);
    bruter_push_int(stack, value, NULL, BRUTER_TYPE_ANY);
}

function(feraw_TextToFloat)
{
    char *text = (char*)bruter_pop_pointer(stack);
    float value = TextToFloat(text);
    bruter_push_float(stack, value, NULL, BRUTER_TYPE_ANY);
}

// basic geometric 3D shapes drawing functions

function(feraw_DrawLine3D)
{
    Vector3 start = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 end = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLine3D(start, end, color);
}

function(feraw_DrawPoint3D)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPoint3D(position, color);
}

function(feraw_DrawCircle3D)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
}

function(feraw_DrawTriangle3D)
{
    Vector3 p1 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p2 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p3 = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangle3D(p1, p2, p3, color);
}

function(feraw_DrawTriangleStrip3D)
{
    const Vector3 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleStrip3D(points, pointCount, color);
}

function(feraw_DrawCube)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCube(position, width, height, length, color);
}

function(feraw_DrawCubeWires)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCubeWires(position, width, height, length, color);
}

function(feraw_DrawSphere)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphere(center, radius, color);
}

function(feraw_DrawSphereEx)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphereEx(center, radius, rings, slices, color);
}

function(feraw_DrawSphereWires)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphereWires(center, radius, rings, slices, color);
}

function(feraw_DrawCylinder)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
}

function(feraw_DrawCylinderEx)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderEx(startPos, endPos, radiusTop, radiusBottom, slices, color);
}

function(feraw_DrawCylinderWires)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
}

function(feraw_DrawCylinderWiresEx)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderWiresEx(startPos, endPos, radiusTop, radiusBottom, slices, color);
}

function(feraw_DrawCapsule)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    int rings = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCapsule(startPos, endPos, radius, slices, rings, color);
}

function(feraw_DrawPlane)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPlane(center, size, color);
}

function(feraw_DrawRay)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRay(ray, color);
}

function(feraw_DrawGrid)
{
    int slices = bruter_pop_int(stack);
    float spacing = bruter_pop_float(stack);
    DrawGrid(slices, spacing);
}

// model managment functions

function(feraw_LoadModel)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Model model = LoadModel(fileName);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadModelFromMesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Model model = LoadModelFromMesh(mesh);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsModelValid)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    bool isValid = IsModelValid(model);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UnloadModel)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    UnloadModel(model);
}

function(feraw_GetModelBoundingBox)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    BoundingBox boundingBox = GetModelBoundingBox(model);
    bruter_push_pointer(stack, bounding_box_to_list(boundingBox), NULL, BRUTER_TYPE_LIST);
}

// model drawing functions
function(feraw_DrawModel)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModel(model, position, scale, tint);
}

function(feraw_DrawModelEx)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

function(feraw_DrawModelWires)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelWires(model, position, scale, tint);
}

function(feraw_DrawModelWiresEx)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

function(feraw_DrawPoints)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelPoints(model, position, scale, tint);
}

function(feraw_DrawPointsEx)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelPointsEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

function(feraw_DrawBoudingBox)
{
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawBoundingBox(box, color);
}

function(feraw_DrawBillboard)
{
    Camera camera = camera3d_constructor(bruter_pop_pointer(stack));
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float size = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawBillboard(camera, texture, position, size, tint);
}

function(feraw_DrawBillboardRec)
{
    Camera camera = camera3d_constructor(bruter_pop_pointer(stack));
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawBillboardRec(camera, texture, sourceRec, position, size, tint);
}

function(feraw_DrawBillboardPro)
{
    Camera camera = camera3d_constructor(bruter_pop_pointer(stack));
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 up = vector3_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawBillboardPro(camera, texture, sourceRec, position, up, size, origin, rotation, tint);
}

// mesh management functions
function(feraw_UploadMesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    bool dynamic = bruter_pop_int(stack);
    UploadMesh(&mesh, dynamic);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UpdateMeshBuffer)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    int index = bruter_pop_int(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int offset = bruter_pop_int(stack);
    UpdateMeshBuffer(mesh, index, data, dataSize, offset);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadMesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    UnloadMesh(mesh);
}

function(feraw_DrawMesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Material material = material_constructor(bruter_pop_pointer(stack));
    Matrix transform = matrix_constructor(bruter_pop_pointer(stack));
    DrawMesh(mesh, material, transform);
}

function(feraw_DrawMeshInstanced)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Material material = material_constructor(bruter_pop_pointer(stack));
    Matrix *transforms = (Matrix*)bruter_pop_pointer(stack);
    int instanceCount = bruter_pop_int(stack);
    DrawMeshInstanced(mesh, material, transforms, instanceCount);
}

function(feraw_GetMeshBoundingBox)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    BoundingBox boundingBox = GetMeshBoundingBox(mesh);
    bruter_push_pointer(stack, bounding_box_to_list(boundingBox), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshTangents)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    GenMeshTangents(&mesh);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_ExportMesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportMesh(mesh, fileName);
}

function(feraw_ExportMeshAsCode)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportMeshAsCode(mesh, fileName);
}

// mesh generation functions
function(feraw_GenMeshPoly)
{
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    Mesh mesh = GenMeshPoly(sides, radius);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshPlane)
{
    float width = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    int resX = bruter_pop_int(stack);
    int resZ = bruter_pop_int(stack);
    Mesh mesh = GenMeshPlane(width, length, resX, resZ);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshCube)
{
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Mesh mesh = GenMeshCube(width, height, length);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshSphere)
{
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshSphere(radius, rings, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshHemiSphere)
{
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshHemiSphere(radius, rings, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshCylinder)
{
    float radius = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshCylinder(radius, height, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshCone)
{
    float radius = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshCone(radius, height, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshTorus)
{
    float radius = bruter_pop_float(stack);
    float tubeRadius = bruter_pop_float(stack);
    int radialSegments = bruter_pop_int(stack);
    int tubularSegments = bruter_pop_int(stack);
    Mesh mesh = GenMeshTorus(radius, tubeRadius, radialSegments, tubularSegments);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshKnot)
{
    float radius = bruter_pop_float(stack);
    float tubeRadius = bruter_pop_float(stack);
    int radialSegments = bruter_pop_int(stack);
    int sides = bruter_pop_int(stack);
    Mesh mesh = GenMeshKnot(radius, tubeRadius, radialSegments, sides);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshHeightmap)
{
    Image heightmap = image_constructor(bruter_pop_pointer(stack));
    Vector3 size = vector3_constructor(bruter_pop_pointer(stack));
    Mesh mesh = GenMeshHeightmap(heightmap, size);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GenMeshCubicmap)
{
    Image cubicmap = image_constructor(bruter_pop_pointer(stack));
    Vector3 cubeSize = vector3_constructor(bruter_pop_pointer(stack));
    Mesh mesh = GenMeshCubicmap(cubicmap, cubeSize);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

// material loading/unloading functions
function(feraw_LoadMaterials)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *materialCount = (int*)bruter_pop_pointer(stack);
    bruter_push_pointer(stack, LoadMaterials(fileName, materialCount), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadMaterialDefault)
{
    Material material = LoadMaterialDefault();
    bruter_push_pointer(stack, material_to_list(material), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsMaterialValid)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    bool isValid = IsMaterialValid(material);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UnloadMaterial)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    UnloadMaterial(material);
}

function(feraw_SetMaterialTexture)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    int mapType = bruter_pop_int(stack); // Assuming mapType is an int representing the texture type
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    SetMaterialTexture(&material, mapType, texture);
    bruter_push_pointer(stack, material_to_list(material), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetModelMeshMaterial)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    int meshId = bruter_pop_int(stack);
    int materialId = bruter_pop_int(stack);
    SetModelMeshMaterial(&model, meshId, materialId);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

// model animations loading/unloading functions
function(feraw_LoadModelAnimations)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *animCount = (int*)bruter_pop_pointer(stack);
    ModelAnimation *animations = LoadModelAnimations(fileName, animCount);
    bruter_push_pointer(stack, animations, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_UpdateModelAnimation)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    int frame = bruter_pop_int(stack);
    UpdateModelAnimation(model, animation, frame);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UpdateModelAnimationBones)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    int frame = bruter_pop_int(stack);
    UpdateModelAnimationBones(model, animation, frame);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadModelAnimation)
{
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    UnloadModelAnimation(animation);
}

function(feraw_UnloadModelAnimations)
{
    ModelAnimation *animations = (ModelAnimation*)bruter_pop_pointer(stack);
    int animCount = bruter_pop_int(stack);
    UnloadModelAnimations(animations, animCount);
}

function(feraw_IsModelAnimationValid)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    bool isValid = IsModelAnimationValid(model, animation);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

// collision detection functions

function(feraw_CheckCollisionSpheres)
{
    Vector3 center1 = vector3_constructor(bruter_pop_pointer(stack));
    float radius1 = bruter_pop_float(stack);
    Vector3 center2 = vector3_constructor(bruter_pop_pointer(stack));
    float radius2 = bruter_pop_float(stack);
    bool collision = CheckCollisionSpheres(center1, radius1, center2, radius2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionBoxes)
{
    BoundingBox box1 = bounding_box_constructor(bruter_pop_pointer(stack));
    BoundingBox box2 = bounding_box_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionBoxes(box1, box2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_CheckCollisionBoxSphere)
{
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    bool collision = CheckCollisionBoxSphere(box, center, radius);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetRayCollisionSphere)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    RayCollision collision = GetRayCollisionSphere(ray, center, radius);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetRayCollisionBox)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionBox(ray, box);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetRayCollisionMesh)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Matrix transform = matrix_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionMesh(ray, mesh, transform);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetRayCollisionTriangle)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Vector3 p1 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p2 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p3 = vector3_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionTriangle(ray, p1, p2, p3);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetRayCollisionQuad)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Vector3 p1 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p2 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p3 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p4 = vector3_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionQuad(ray, p1, p2, p3, p4);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

// audio loading/unloading functions
function(feraw_InitAudioDevice)
{
    InitAudioDevice();
}

function(feraw_CloseAudioDevice)
{
    CloseAudioDevice();
}

function(feraw_IsAudioDeviceReady)
{
    bool isReady = IsAudioDeviceReady();
    bruter_push_int(stack, isReady, NULL, BRUTER_TYPE_ANY);
}

function(feraw_SetMasterVolume)
{
    float volume = bruter_pop_float(stack);
    SetMasterVolume(volume);
}

function(feraw_GetMasterVolume)
{
    float volume = GetMasterVolume();
    bruter_push_float(stack, volume, NULL, BRUTER_TYPE_ANY);
}

// wave/sound loading/unloading functions

function(feraw_LoadWave)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Wave wave = LoadWave(fileName);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadWaveFromMemory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Wave wave = LoadWaveFromMemory(fileType, data, dataSize);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsWaveValid)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    bool isValid = IsWaveValid(wave);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_LoadSound)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Sound sound = LoadSound(fileName);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadSoundFromWave)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    Sound sound = LoadSoundFromWave(wave);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadSoundAlias)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    Sound aliasSound = LoadSoundAlias(sound);
    bruter_push_pointer(stack, sound_to_list(aliasSound), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsSoundValid)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    bool isValid = IsSoundValid(sound);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UpdateSound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    void *data = bruter_pop_pointer(stack);
    int samplesCount = bruter_pop_int(stack);
    UpdateSound(sound, data, samplesCount);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(feraw_UnloadWave)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    UnloadWave(wave);
}

function(feraw_UnloadSound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    UnloadSound(sound);
}

function(feraw_UnloadSoundAlias)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    UnloadSoundAlias(sound);
}

function(feraw_ExportWave)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportWave(wave, fileName);
}

function(feraw_ExportWaveAsCode)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportWaveAsCode(wave, fileName);
}

// wave/sound management functions
function(feraw_PlaySound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    PlaySound(sound);
}

function(feraw_StopSound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    StopSound(sound);
}

function(feraw_PauseSound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    PauseSound(sound);
}

function(feraw_ResumeSound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    ResumeSound(sound);
}

function(feraw_IsSoundPlaying)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    bool isPlaying = IsSoundPlaying(sound);
    bruter_push_int(stack, isPlaying, NULL, BRUTER_TYPE_ANY);
}

function(feraw_SetSoundVolume)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetSoundVolume(sound, volume);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetSoundPitch)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetSoundPitch(sound, pitch);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetSoundPan)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetSoundPan(sound, pan);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(feraw_WaveCopy)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    Wave copiedWave = WaveCopy(wave);
    bruter_push_pointer(stack, wave_to_list(copiedWave), NULL, BRUTER_TYPE_LIST);
}

function(feraw_WaveCrop)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    int initSample = bruter_pop_int(stack);
    int finalSample = bruter_pop_int(stack);
    WaveCrop(&wave, initSample, finalSample);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(feraw_WaveFormat)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    int sampleRate = bruter_pop_int(stack);
    int sampleSize = bruter_pop_int(stack);
    int channels = bruter_pop_int(stack);
    WaveFormat(&wave, sampleRate, sampleSize, channels);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadWaveSamples)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    void *samples = LoadWaveSamples(wave);
    bruter_push_pointer(stack, samples, NULL, BRUTER_TYPE_BUFFER);
}

function(feraw_UnloadWaveSamples)
{
    void *samples = bruter_pop_pointer(stack);
    UnloadWaveSamples(samples);
}

// music management functions
function(feraw_LoadMusicStream)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Music music = LoadMusicStream(fileName);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(feraw_LoadMusicStreamFromMemory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Music music = LoadMusicStreamFromMemory(fileType, data, dataSize);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsMusicValid)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    bool isValid = IsMusicValid(music);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UnloadMusicStream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    UnloadMusicStream(music);
}

function(feraw_PlayMusicStream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    PlayMusicStream(music);
}

function(feraw_IsMusicStreamPlaying)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    bool isPlaying = IsMusicStreamPlaying(music);
    bruter_push_int(stack, isPlaying, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UpdateMusicStream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    UpdateMusicStream(music);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(feraw_StopMusicStream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    StopMusicStream(music);
}

function(feraw_PauseMusicStream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    PauseMusicStream(music);
}

function(feraw_ResumeMusicStream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    ResumeMusicStream(music);
}

function(feraw_SeekMusicStream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float position = bruter_pop_float(stack);
    SeekMusicStream(music, position);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetMusicVolume)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetMusicVolume(music, volume);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetMusicPitch)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetMusicPitch(music, pitch);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetMusicPan)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetMusicPan(music, pan);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(feraw_GetMusicTimeLength)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float length = GetMusicTimeLength(music);
    bruter_push_float(stack, length, NULL, BRUTER_TYPE_ANY);
}

function(feraw_GetMusicTimePlayed)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float playedTime = GetMusicTimePlayed(music);
    bruter_push_float(stack, playedTime, NULL, BRUTER_TYPE_ANY);
}

// audiostream management functions
function(feraw_LoadAudioStream)
{
    int sampleRate = bruter_pop_int(stack);
    int sampleSize = bruter_pop_int(stack);
    int channels = bruter_pop_int(stack);
    AudioStream stream = LoadAudioStream(sampleRate, sampleSize, channels);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsAudioStreamValid)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    bool isValid = IsAudioStreamValid(stream);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(feraw_UnloadAudioStream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    UnloadAudioStream(stream);
}

function(feraw_UpdateAudioStream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    void *data = bruter_pop_pointer(stack);
    int samplesCount = bruter_pop_int(stack);
    UpdateAudioStream(stream, data, samplesCount);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_IsAudioStreamProcessed)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    bool isProcessed = IsAudioStreamProcessed(stream);
    bruter_push_int(stack, isProcessed, NULL, BRUTER_TYPE_ANY);
}

function(feraw_PlayAudioStream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    PlayAudioStream(stream);
}

function(feraw_PauseAudioStream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    StopAudioStream(stream);
}

function(feraw_StopAudioStream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    PauseAudioStream(stream);
}

function(feraw_ResumeAudioStream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    ResumeAudioStream(stream);
}

function(feraw_SetAudioStreamVolume)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetAudioStreamVolume(stream, volume);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetAudioStreamPitch)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetAudioStreamPitch(stream, pitch);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetAudioStreamPan)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetAudioStreamPan(stream, pan);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_SetAudioStreamBufferSizeDefault)
{
    int size = bruter_pop_int(stack);
    SetAudioStreamBufferSizeDefault(size);
}

function(feraw_SetAudioStreamCallback)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback callback = (AudioCallback)bruter_pop_pointer(stack);
    SetAudioStreamCallback(stream, callback);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_AttachAudioStreamProcessor)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    AttachAudioStreamProcessor(stream, processor);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_DetachAudioStreamProcessor)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    DetachAudioStreamProcessor(stream, processor);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(feraw_AttachAudioMixedProcessor)
{
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    AttachAudioMixedProcessor(processor);
}

function(feraw_DetachAudioMixedProcessor)
{
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    DetachAudioMixedProcessor(processor);
}