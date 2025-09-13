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
void feraw_InitWindow(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    char *title = (char*)bruter_pop_pointer(stack);
    InitWindow(width, height, title);
}

void feraw_CloseWindow(BruterList* stack)
{
    CloseWindow();
}

void feraw_WindowShouldClose(BruterList* stack)
{
    bool shouldClose = WindowShouldClose();
    bruter_push_int(stack, shouldClose, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowReady(BruterList* stack)
{
    bool isReady = IsWindowReady();
    bruter_push_int(stack, isReady, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowFullscreen(BruterList* stack)
{
    bool isFullscreen = IsWindowFullscreen();
    bruter_push_int(stack, isFullscreen, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowHidden(BruterList* stack)
{
    bool isHidden = IsWindowHidden();
    bruter_push_int(stack, isHidden, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowMinimized(BruterList* stack)
{
    bool isMinimized = IsWindowMinimized();
    bruter_push_int(stack, isMinimized, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowMaximized(BruterList* stack)
{
    bool isMaximized = IsWindowMaximized();
    bruter_push_int(stack, isMaximized, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowFocused(BruterList* stack)
{
    bool isFocused = IsWindowFocused();
    bruter_push_int(stack, isFocused, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowResized(BruterList* stack)
{
    bool isResized = IsWindowResized();
    bruter_push_int(stack, isResized, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsWindowState(BruterList* stack)
{
    int flags = bruter_pop_int(stack);
    bool isState = IsWindowState(flags);
    bruter_push_int(stack, isState, NULL, BRUTER_TYPE_ANY);
}

void feraw_SetWindowState(BruterList* stack)
{
    int flags = bruter_pop_int(stack);
    SetWindowState(flags);
}

void feraw_ClearWindowState(BruterList* stack)
{
    int flags = bruter_pop_int(stack);
    ClearWindowState(flags);
}

void feraw_ToggleFullscreen(BruterList* stack)
{
    ToggleFullscreen();
}

void feraw_ToggleBorderlessWindowed(BruterList* stack)
{
    ToggleBorderlessWindowed();
}

void feraw_MaximizeWindow(BruterList* stack)
{
    MaximizeWindow();
}

void feraw_MinimizeWindow(BruterList* stack)
{
    MinimizeWindow();
}

void feraw_RestoreWindow(BruterList* stack)
{
    RestoreWindow();
}

void feraw_SetWindowIcon(BruterList* stack)
{
    Image icon = image_constructor(bruter_pop_pointer(stack));
    SetWindowIcon(icon);
}

void feraw_SetWindowIcons(BruterList* stack)
{
    Image *icons = (Image*)bruter_pop_pointer(stack);
    int count = bruter_pop_int(stack);
    SetWindowIcons(icons, count);
}

void feraw_SetWindowTitle(BruterList* stack)
{
    char *title = (char*)bruter_pop_pointer(stack);
    SetWindowTitle(title);
}

void feraw_SetWindowPosition(BruterList* stack)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    SetWindowPosition(x, y);
}

void feraw_SetWindowMonitor(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    SetWindowMonitor(monitor);
}

void feraw_SetWindowMinSize(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowMinSize(width, height);
}

void feraw_SetWindowMaxSize(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowMaxSize(width, height);
}

void feraw_SetWindowSize(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowSize(width, height);
}

void feraw_SetWindowOpacity(BruterList* stack)
{
    float opacity = bruter_pop_float(stack);
    SetWindowOpacity(opacity);
}

void feraw_SetWindowFocused(BruterList* stack)
{
    SetWindowFocused();
}

void feraw_GetWindowHandle(BruterList* stack)
{
    bruter_push_pointer(stack, GetWindowHandle(), NULL, BRUTER_TYPE_ANY);
}

void feraw_GetScreenWidth(BruterList* stack)
{
    int width = GetScreenWidth();
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetScreenHeight(BruterList* stack)
{
    int height = GetScreenHeight();
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMonitorCount(BruterList* stack)
{
    int count = GetMonitorCount();
    bruter_push_int(stack, count, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetCurrentMonitor(BruterList* stack)
{
    int monitor = GetCurrentMonitor();
    bruter_push_int(stack, monitor, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMonitorPosition(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    Vector2 position = GetMonitorPosition(monitor);
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetMonitorWidth(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    int width = GetMonitorWidth(monitor);
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMonitorHeight(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    int height = GetMonitorHeight(monitor);
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMonitorPhysicalWidth(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    int width = GetMonitorPhysicalWidth(monitor);
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMonitorPhysicalHeight(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    int height = GetMonitorPhysicalHeight(monitor);
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMonitorRefreshRate(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    int refreshRate = GetMonitorRefreshRate(monitor);
    bruter_push_int(stack, refreshRate, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetWindowPosition(BruterList* stack)
{
    Vector2 position = GetWindowPosition();
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetWindowScaleDpi(BruterList* stack)
{
    Vector2 scale = GetWindowScaleDPI();
    bruter_push_pointer(stack, vector2_to_list(scale), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetMonitorName(BruterList* stack)
{
    int monitor = bruter_pop_int(stack);
    const char *name = GetMonitorName(monitor);
    bruter_push_pointer(stack, strdup(name), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_SetClipboardText(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    SetClipboardText(text);
}

void feraw_GetClipboardText(BruterList* stack)
{
    const char *text = GetClipboardText();
    bruter_push_pointer(stack, strdup(text), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_GetClipboardImage(BruterList* stack)
{
    Image image = GetClipboardImage();
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_EnableEventWaiting(BruterList* stack)
{
    EnableEventWaiting();
}

void feraw_DisableEventWaiting(BruterList* stack)
{
    DisableEventWaiting();
}

// Cursor-related functions
void feraw_ShowCursor(BruterList* stack)
{
    ShowCursor();
}

void feraw_HideCursor(BruterList* stack)
{
    HideCursor();
}

void feraw_IsCursorHidden(BruterList* stack)
{
    bool isHidden = IsCursorHidden();
    bruter_push_int(stack, isHidden, NULL, BRUTER_TYPE_ANY);
}

void feraw_EnableCursor(BruterList* stack)
{
    EnableCursor();
}

void feraw_DisableCursor(BruterList* stack)
{
    DisableCursor();
}

void feraw_IsCursorOnScreen(BruterList* stack)
{
    bool isOnScreen = IsCursorOnScreen();
    bruter_push_int(stack, isOnScreen, NULL, BRUTER_TYPE_ANY);
}

// Drawing-related functions
void feraw_ClearBackground(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    ClearBackground(color);
}

void feraw_BeginDrawing(BruterList* stack)
{
    BeginDrawing();
}

void feraw_EndDrawing(BruterList* stack)
{
    EndDrawing();
}

void feraw_BeginMode2D(BruterList* stack)
{
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    BeginMode2D(camera);
}

void feraw_EndMode2D(BruterList* stack)
{
    EndMode2D();
}

void feraw_BeginMode3D(BruterList* stack)
{
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    BeginMode3D(camera);
}

void feraw_EndMode3D(BruterList* stack)
{
    EndMode3D();
}

void feraw_BeginShaderMode(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    BeginShaderMode(shader);
}

void feraw_EndShaderMode(BruterList* stack)
{
    EndShaderMode();
}

void feraw_BeginBlendMode(BruterList* stack)
{
    int mode = bruter_pop_int(stack);
    BeginBlendMode(mode);
}

void feraw_EndBlendMode(BruterList* stack)
{
    EndBlendMode();
}

void feraw_BeginScissorMode(BruterList* stack)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    BeginScissorMode(x, y, width, height);
}

void feraw_EndScissorMode(BruterList* stack)
{
    EndScissorMode();
}

void feraw_BeginVrStereoMode(BruterList* stack)
{
    VrStereoConfig config = vr_stereo_config_constructor(bruter_pop_pointer(stack));
    BeginVrStereoMode(config);
}

void feraw_EndVrStereoMode(BruterList* stack)
{
    EndVrStereoMode();
}

void feraw_LoadVrStereoConfig(BruterList* stack)
{
    VrDeviceInfo info = vr_device_info_constructor(bruter_pop_pointer(stack));
    VrStereoConfig config = LoadVrStereoConfig(info);
    bruter_push_pointer(stack, vr_stereo_config_to_list(config), NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadVrStereoConfig(BruterList* stack)
{
    VrStereoConfig config = vr_stereo_config_constructor(bruter_pop_pointer(stack));
    UnloadVrStereoConfig(config);
}

void feraw_LoadShader(BruterList* stack)
{
    char *vsFileName = (char*)bruter_pop_pointer(stack);
    char *fsFileName = (char*)bruter_pop_pointer(stack);
    Shader shader = LoadShader(vsFileName, fsFileName);
    bruter_push_pointer(stack, shader_to_list(shader), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadShaderFromMemory(BruterList* stack)
{
    char *vsCode = (char*)bruter_pop_pointer(stack);
    char *fsCode = (char*)bruter_pop_pointer(stack);
    Shader shader = LoadShaderFromMemory(vsCode, fsCode);
    bruter_push_pointer(stack, shader_to_list(shader), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsShaderValid(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    bool isValid = IsShaderValid(shader);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetShaderLocation(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    char *uniformName = (char*)bruter_pop_pointer(stack);
    int location = GetShaderLocation(shader, uniformName);
    bruter_push_int(stack, location, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetShaderLocationAttrib(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    char *attribName = (char*)bruter_pop_pointer(stack);
    int location = GetShaderLocationAttrib(shader, attribName);
    bruter_push_int(stack, location, NULL, BRUTER_TYPE_ANY);
}

void feraw_SetShaderValue(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    const void *value = bruter_pop_pointer(stack);
    int uniformType = bruter_pop_int(stack);

    SetShaderValue(shader, locIndex, value, uniformType);
}

void feraw_SetShaderValueMatrix(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    Matrix mat = matrix_constructor(bruter_pop_pointer(stack));

    SetShaderValueMatrix(shader, locIndex, mat);
}

void feraw_SetShaderValueTexture(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));

    SetShaderValueTexture(shader, locIndex, texture);
}

void feraw_UnloadShader(BruterList* stack)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    UnloadShader(shader);
}

void feraw_GetScreenToWorldRay(BruterList* stack)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Ray ray = GetScreenToWorldRay(position, camera);
    bruter_push_pointer(stack, ray_to_list(ray), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetScreenToWorldRayEx(BruterList* stack)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Ray ray = GetScreenToWorldRayEx(position, camera, width, height);
    bruter_push_pointer(stack, ray_to_list(ray), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetWorldToScreen(BruterList* stack)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Vector2 screenPos = GetWorldToScreen(position, camera);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetWorldToScreenEx(BruterList* stack)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Vector2 screenPos = GetWorldToScreenEx(position, camera, width, height);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetWorldToScreen2D(BruterList* stack)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Vector2 screenPos = GetWorldToScreen2D(position, camera);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetScreenToWorld2D(BruterList* stack)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Vector2 worldPos = GetScreenToWorld2D(position, camera);
    bruter_push_pointer(stack, vector2_to_list(worldPos), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetCameraMatrix(BruterList* stack)
{
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Matrix matrix = GetCameraMatrix(camera);
    bruter_push_pointer(stack, matrix_to_list(matrix), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetCameraMatrix2D(BruterList* stack)
{
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Matrix matrix = GetCameraMatrix2D(camera);
    bruter_push_pointer(stack, matrix_to_list(matrix), NULL, BRUTER_TYPE_LIST);
}

// Timing-related functions
void feraw_SetTargetFPS(BruterList* stack)
{
    int fps = bruter_pop_int(stack);
    SetTargetFPS(fps);
}

void feraw_GetFrameTime(BruterList* stack)
{
    float frameTime = GetFrameTime();
    bruter_push_float(stack, frameTime, NULL, BRUTER_TYPE_FLOAT);
}

void feraw_GetTime(BruterList* stack)
{
    double time = GetTime();
    bruter_push_float(stack, (float)time, NULL, BRUTER_TYPE_FLOAT);
}

void feraw_GetFPS(BruterList* stack)
{
    int fps = GetFPS();
    bruter_push_int(stack, fps, NULL, BRUTER_TYPE_ANY);
}

// Custom frame control functions
void feraw_SwapScreenBuffer(BruterList* stack)
{
    SwapScreenBuffer();
}

void feraw_PollInputEvents(BruterList* stack)
{
    PollInputEvents();
}

void feraw_WaitTime(BruterList* stack)
{
    float seconds = bruter_pop_float(stack);
    WaitTime(seconds);
}

// Random values generation functions
void feraw_SetRandomSeed(BruterList* stack)
{
    unsigned int seed = bruter_pop_int(stack);
    SetRandomSeed(seed);
}

void feraw_GetRandomValue(BruterList* stack)
{
    int min = bruter_pop_int(stack);
    int max = bruter_pop_int(stack);
    int value = GetRandomValue(min, max);
    bruter_push_int(stack, value, NULL, BRUTER_TYPE_ANY);
}

void feraw_LoadRandomSequence(BruterList* stack)
{
    unsigned int count = bruter_pop_int(stack);
    int min = bruter_pop_int(stack);
    int max = bruter_pop_int(stack);
    int *sequence = LoadRandomSequence(count, min, max);
    bruter_push_pointer(stack, sequence, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_UnloadRandomSequence(BruterList* stack)
{
    int *sequence = (int*)bruter_pop_pointer(stack);
    UnloadRandomSequence(sequence);
}

// Misc. functions
void feraw_TakeScreenshot(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    TakeScreenshot(fileName);
}

void feraw_SetConfigFlags(BruterList* stack)
{
    unsigned int flags = bruter_pop_int(stack);
    SetConfigFlags(flags);
}

void feraw_OpenUrl(BruterList* stack)
{
    char *url = (char*)bruter_pop_pointer(stack);
    OpenURL(url);
}

// utils functions
void feraw_TraceLog(BruterList* stack)
{
    printf("feraw_TraceLog is not implemented in bruter yet\n");
}

void feraw_SetTraceLogLevel(BruterList* stack)
{
    int logLevel = bruter_pop_int(stack);
    SetTraceLogLevel(logLevel);
}

void feraw_MemAlloc(BruterList* stack)
{
    unsigned int size = bruter_pop_int(stack);
    void *ptr = MemAlloc(size);
    bruter_push_pointer(stack, ptr, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_MemRealloc(BruterList* stack)
{
    void *ptr = bruter_pop_pointer(stack);
    unsigned int size = bruter_pop_int(stack);
    void *newPtr = MemRealloc(ptr, size);
    bruter_push_pointer(stack, newPtr, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_MemFree(BruterList* stack)
{
    void *ptr = bruter_pop_pointer(stack);
    MemFree(ptr);
}

// custom callbacks, probably not working
void feraw_SetTracelogCallback(BruterList* stack)
{
    TraceLogCallback callback = (TraceLogCallback)bruter_pop_pointer(stack);
    SetTraceLogCallback(callback);
}

void feraw_SetLoadFileDataCallback(BruterList* stack)
{
    LoadFileDataCallback callback = (LoadFileDataCallback)bruter_pop_pointer(stack);
    SetLoadFileDataCallback(callback);
}

void feraw_SetSaveFileDataCallback(BruterList* stack)
{
    SaveFileDataCallback callback = (SaveFileDataCallback)bruter_pop_pointer(stack);
    SetSaveFileDataCallback(callback);
}

void feraw_SetLoadFileTextCallback(BruterList* stack)
{
    LoadFileTextCallback callback = (LoadFileTextCallback)bruter_pop_pointer(stack);
    SetLoadFileTextCallback(callback);
}

void feraw_SetSaveFileTextCallback(BruterList* stack)
{
    SaveFileTextCallback callback = (SaveFileTextCallback)bruter_pop_pointer(stack);
    SetSaveFileTextCallback(callback);
}

// Files management functions
void feraw_LoadFileData(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int bytesRead = 0;
    void *data = LoadFileData(fileName, &bytesRead);
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, data, "data", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, bytesRead, "bytesRead", BRUTER_TYPE_ANY);
    bruter_push_pointer(stack, list, NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadFileData(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    UnloadFileData(data);
}

void feraw_SaveFileData(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    unsigned int bytesToWrite = bruter_pop_int(stack);
    bool success = SaveFileData(fileName, data, bytesToWrite);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

void feraw_ExportDataAsCode(BruterList* stack)
{
    unsigned char *data = (unsigned char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportDataAsCode(data, dataSize, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

void feraw_LoadFileText(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *text = LoadFileText(fileName);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_UnloadFileText(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    UnloadFileText(text);
}

void feraw_SaveFileText(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *text = (char*)bruter_pop_pointer(stack);
    bool success = SaveFileText(fileName, text);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// File system functions
void feraw_FileExists(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool exists = FileExists(fileName);
    bruter_push_int(stack, exists, NULL, BRUTER_TYPE_ANY);
}

void feraw_DirectoryExists(BruterList* stack)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool exists = DirectoryExists(dirPath);
    bruter_push_int(stack, exists, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsFileExtension(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *ext = (char*)bruter_pop_pointer(stack);
    bool isExt = IsFileExtension(fileName, ext);
    bruter_push_int(stack, isExt, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetFileLength(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    unsigned int length = GetFileLength(fileName);
    bruter_push_int(stack, length, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetFileExtension(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    const char *ext = GetFileExtension(fileName);
    bruter_push_pointer(stack, strdup(ext), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_GetFileName(BruterList* stack)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *fileName = GetFileName(filePath);
    bruter_push_pointer(stack, strdup(fileName), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_GetFileNameWithoutExt(BruterList* stack)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *fileNameWithoutExt = GetFileNameWithoutExt(filePath);
    bruter_push_pointer(stack, strdup(fileNameWithoutExt), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_GetDirectoryPath(BruterList* stack)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *dirPath = GetDirectoryPath(filePath);
    bruter_push_pointer(stack, strdup(dirPath), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_GetPrevDirectoryPath(BruterList* stack)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    const char *prevDirPath = GetPrevDirectoryPath(filePath);
    bruter_push_pointer(stack, strdup(prevDirPath), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_GetWorkingDirectory(BruterList* stack)
{
    const char *workingDir = GetWorkingDirectory();
    bruter_push_pointer(stack, strdup(workingDir), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_GetApplicationDirectory(BruterList* stack)
{
    const char *appDir = GetApplicationDirectory();
    bruter_push_pointer(stack, strdup(appDir), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_MakeDirectory(BruterList* stack)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool success = MakeDirectory(dirPath);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

void feraw_ChangeDirectory(BruterList* stack)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool success = ChangeDirectory(dirPath);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsPathFile(BruterList* stack)
{
    char *path = (char*)bruter_pop_pointer(stack);
    bool isFile = IsPathFile(path);
    bruter_push_int(stack, isFile, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsFilenameValid(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool isValid = IsFileNameValid(fileName);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_LoadDirectoryFiles(BruterList* stack)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    FilePathList filePathList = LoadDirectoryFiles(dirPath);
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadDirectoryFilesEx(BruterList* stack)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    const char* filter = (const char*)bruter_pop_pointer(stack);
    bool scanSubdirs = bruter_pop_int(stack);
    FilePathList filePathList = LoadDirectoryFilesEx(dirPath, filter, scanSubdirs);
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadDirectoryFiles(BruterList* stack)
{
    FilePathList filePathList = file_path_list_constructor(bruter_pop_pointer(stack));
    UnloadDirectoryFiles(filePathList);
}

void feraw_IsFileDropped(BruterList* stack)
{
    bool isDropped = IsFileDropped();
    bruter_push_int(stack, isDropped, NULL, BRUTER_TYPE_ANY);
}

void feraw_LoadDroppedFiles(BruterList* stack)
{
    FilePathList filePathList = LoadDroppedFiles();
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadDroppedFiles(BruterList* stack)
{
    FilePathList filePathList = file_path_list_constructor(bruter_pop_pointer(stack));
    UnloadDroppedFiles(filePathList);
}

void feraw_GetFileModTime(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    long modTime = GetFileModTime(fileName);
    bruter_push_int(stack, (int)modTime, NULL, BRUTER_TYPE_ANY);
}

// Compression/Encoding functionality
void feraw_CompressData(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *compDataSize = (int*)bruter_pop_pointer(stack);
    void *compressedData = CompressData(data, dataSize, compDataSize);
    bruter_push_pointer(stack, compressedData, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_DecompressData(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *decompDataSize = (int*)bruter_pop_pointer(stack);
    void *decompressedData = DecompressData(data, dataSize, decompDataSize);
    bruter_push_pointer(stack, decompressedData, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_EncodeDataBase64(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *outputSize = (int*)bruter_pop_pointer(stack);
    char *encodedData = EncodeDataBase64(data, dataSize, outputSize);
    bruter_push_pointer(stack, encodedData, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_DecodeDataBase64(BruterList* stack)
{
    const unsigned char *encodedData = (const unsigned char*)bruter_pop_pointer(stack);
    int *decodedDataSize = (int*)bruter_pop_pointer(stack);
    void *decodedData = DecodeDataBase64(encodedData, decodedDataSize);
    bruter_push_pointer(stack, decodedData, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_ComputeCrc32(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    unsigned int crc = ComputeCRC32(data, dataSize);
    bruter_push_int(stack, crc, NULL, BRUTER_TYPE_ANY);
}

void feraw_ComputeMd5(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    ComputeMD5(data, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_ComputeSha1(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    ComputeSHA1(data, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

// Automation events functionality
void feraw_LoadAutomationEventList(BruterList* stack)
{
    BruterList *automation_event_list = bruter_pop_pointer(stack);
    AutomationEventList eventList = automation_event_list_constructor(automation_event_list);
    bruter_push_pointer(stack, automation_event_list_to_list(eventList), NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadAutomationEventList(BruterList* stack)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    UnloadAutomationEventList(eventList);
}

void feraw_ExportAutomationEventList(BruterList* stack)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportAutomationEventList(eventList, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// needs revision!!!!!
void feraw_SetAutomationEventList(BruterList* stack)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    SetAutomationEventList(&eventList);
}

void feraw_SetAutomationEventBaseFrame(BruterList* stack)
{
    int baseFrame = bruter_pop_int(stack);
    SetAutomationEventBaseFrame(baseFrame);
}

void feraw_StartAutomationEventRecording(BruterList* stack)
{
    StartAutomationEventRecording();
}

void feraw_StopAutomationEventRecording(BruterList* stack)
{
    StopAutomationEventRecording();
}

void feraw_PlayAutomationEvent(BruterList* stack)
{
    AutomationEvent eventList = automation_event_constructor(bruter_pop_pointer(stack));
    PlayAutomationEvent(eventList);
}

// input-related functions: keyboard
void feraw_IsKeyPressed(BruterList* stack)
{
    int key = bruter_pop_int(stack);
    bool isPressed = IsKeyPressed(key);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsKeyPressedRepeat(BruterList* stack)
{
    int key = bruter_pop_int(stack);
    bool isPressedRepeat = IsKeyPressedRepeat(key);
    bruter_push_int(stack, isPressedRepeat, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsKeyDown(BruterList* stack)
{
    int key = bruter_pop_int(stack);
    bool isDown = IsKeyDown(key);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsKeyReleased(BruterList* stack)
{
    int key = bruter_pop_int(stack);
    bool isReleased = IsKeyReleased(key);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsKeyUp(BruterList* stack)
{
    int key = bruter_pop_int(stack);
    bool isUp = IsKeyUp(key);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetKeyPressed(BruterList* stack)
{
    int key = GetKeyPressed();
    bruter_push_int(stack, key, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetCharPressed(BruterList* stack)
{
    int charCode = GetCharPressed();
    bruter_push_int(stack, charCode, NULL, BRUTER_TYPE_ANY);
}

void feraw_SetExitKey(BruterList* stack)
{
    int key = bruter_pop_int(stack);
    SetExitKey(key);
}

// input-related functions: gamepads
void feraw_IsGamepadAvailable(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    bool isAvailable = IsGamepadAvailable(gamepad);
    bruter_push_int(stack, isAvailable, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetGamepadName(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    const char *name = GetGamepadName(gamepad);
    bruter_push_pointer(stack, strdup(name), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_IsGamepadButtonPressed(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isPressed = IsGamepadButtonPressed(gamepad, button);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsGamepadButtonDown(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isDown = IsGamepadButtonDown(gamepad, button);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsGamepadButtonReleased(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isReleased = IsGamepadButtonReleased(gamepad, button);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsGamepadButtonUp(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isUp = IsGamepadButtonUp(gamepad, button);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetGamepadButtonPressed(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    int button = GetGamepadButtonPressed();
    bruter_push_int(stack, button, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetGamepadAxisCount(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    int axisCount = GetGamepadAxisCount(gamepad);
    bruter_push_int(stack, axisCount, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetGamepadAxisMovement(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    int axis = bruter_pop_int(stack);
    float movement = GetGamepadAxisMovement(gamepad, axis);
    bruter_push_float(stack, movement, NULL, BRUTER_TYPE_FLOAT);
}

void feraw_SetGamepadMappings(BruterList* stack)
{
    char *mapping = (char*)bruter_pop_pointer(stack);
    bool success = SetGamepadMappings(mapping);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

void feraw_SetGamepadVibration(BruterList* stack)
{
    int gamepad = bruter_pop_int(stack);
    float leftVibration = bruter_pop_float(stack);
    float rightVibration = bruter_pop_float(stack);
    float duration = bruter_pop_float(stack);
    SetGamepadVibration(gamepad, leftVibration, rightVibration, duration);
}

// input-related functions: mouse
void feraw_IsMouseButtonPressed(BruterList* stack)
{
    int button = bruter_pop_int(stack);
    bool isPressed = IsMouseButtonPressed(button);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsMouseButtonDown(BruterList* stack)
{
    int button = bruter_pop_int(stack);
    bool isDown = IsMouseButtonDown(button);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsMouseButtonReleased(BruterList* stack)
{
    int button = bruter_pop_int(stack);
    bool isReleased = IsMouseButtonReleased(button);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

void feraw_IsMouseButtonUp(BruterList* stack)
{
    int button = bruter_pop_int(stack);
    bool isUp = IsMouseButtonUp(button);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMouseX(BruterList* stack)
{
    int x = GetMouseX();
    bruter_push_int(stack, x, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMouseY(BruterList* stack)
{
    int y = GetMouseY();
    bruter_push_int(stack, y, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMousePosition(BruterList* stack)
{
    Vector2 position = GetMousePosition();
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetMouseDelta(BruterList* stack)
{
    Vector2 delta = GetMouseDelta();
    bruter_push_pointer(stack, vector2_to_list(delta), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetMousePosition(BruterList* stack)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    SetMousePosition(x, y);
}

void feraw_SetMouseOffset(BruterList* stack)
{
    int offsetX = bruter_pop_int(stack);
    int offsetY = bruter_pop_int(stack);
    SetMouseOffset(offsetX, offsetY);
}

void feraw_SetMouseScale(BruterList* stack)
{
    float scaleX = bruter_pop_float(stack);
    float scaleY = bruter_pop_float(stack);
    SetMouseScale(scaleX, scaleY);
}

void feraw_GetMouseWheelMove(BruterList* stack)
{
    float wheelMove = GetMouseWheelMove();
    bruter_push_float(stack, wheelMove, NULL, BRUTER_TYPE_FLOAT);
}

void feraw_SetMouseCursor(BruterList* stack)
{
    int cursor = bruter_pop_int(stack);
    SetMouseCursor(cursor);
}

// input-related functions: touch

void feraw_GetTouchX(BruterList* stack)
{
    int touchX = GetTouchX();
    bruter_push_int(stack, touchX, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetTouchY(BruterList* stack)
{
    int touchY = GetTouchY();
    bruter_push_int(stack, touchY, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetTouchPosition(BruterList* stack)
{
    int index = bruter_pop_int(stack);
    Vector2 position = GetTouchPosition(index);
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetTouchPointId(BruterList* stack)
{
    int index = bruter_pop_int(stack);
    int id = GetTouchPointId(index);
    bruter_push_int(stack, id, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetTouchPointCount(BruterList* stack)
{
    int count = GetTouchPointCount();
    bruter_push_int(stack, count, NULL, BRUTER_TYPE_ANY);
}

// Gestures and Touch Handling functions
void feraw_SetGesturesEnabled(BruterList* stack)
{
    unsigned int gestureFlags = bruter_pop_int(stack);
    SetGesturesEnabled(gestureFlags);
}

void feraw_IsGestureDetected(BruterList* stack)
{
    int gesture = bruter_pop_int(stack);
    bool detected = IsGestureDetected(gesture);
    bruter_push_int(stack, detected, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetGestureDetected(BruterList* stack)
{
    int gesture = GetGestureDetected();
    bruter_push_int(stack, gesture, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetGestureHoldDuration(BruterList* stack)
{
    float duration = GetGestureHoldDuration();
    bruter_push_float(stack, duration, NULL, BRUTER_TYPE_FLOAT);
}

void feraw_GetGestureDragVector(BruterList* stack)
{
    Vector2 dragVector = GetGestureDragVector();
    bruter_push_pointer(stack, vector2_to_list(dragVector), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetGestureDragAngle(BruterList* stack)
{
    float angle = GetGestureDragAngle();
    bruter_push_float(stack, angle, NULL, BRUTER_TYPE_FLOAT);
}

void feraw_GetGesturePinchVector(BruterList* stack)
{
    Vector2 pinchVector = GetGesturePinchVector();
    bruter_push_pointer(stack, vector2_to_list(pinchVector), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetGesturePinchAngle(BruterList* stack)
{
    float angle = GetGesturePinchAngle();
    bruter_push_float(stack, angle, NULL, BRUTER_TYPE_FLOAT);
}

// Camera system functions
void feraw_UpdateCamera(BruterList* stack)
{
    Camera3D *camera = (Camera3D*)bruter_pop_pointer(stack);
    int mode = bruter_pop_int(stack);
    UpdateCamera(camera, mode);
}

void feraw_UpdateCameraPro(BruterList* stack)
{
    Camera3D *camera = (Camera3D*)bruter_pop_pointer(stack);
    Vector3 move = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotation = vector3_constructor(bruter_pop_pointer(stack));
    float zoom = bruter_pop_float(stack);
    UpdateCameraPro(camera, move, rotation, zoom);
}

// basic shapes drawing functions
void feraw_SetShapesTexture(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle source = rectangle_constructor(bruter_pop_pointer(stack));
    SetShapesTexture(texture, source);
}

void feraw_GetShapesTexture(BruterList* stack)
{
    Texture2D texture = GetShapesTexture();
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetShapesTextureRectangle(BruterList* stack)
{
    Rectangle source = GetShapesTextureRectangle();
    bruter_push_pointer(stack, rectangle_to_list(source), NULL, BRUTER_TYPE_LIST);
}

// basic shapes drawing functions
void feraw_DrawPixel(BruterList* stack)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPixel(posX, posY, color);
}

void feraw_DrawLine(BruterList* stack)
{
    int startX = bruter_pop_int(stack);
    int startY = bruter_pop_int(stack);
    int endX = bruter_pop_int(stack);
    int endY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLine(startX, startY, endX, endY, color);
}

void feraw_DrawLineEx(BruterList* stack)
{
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineEx(start, end, thick, color);
}

void feraw_DrawLineStrip(BruterList* stack)
{
    Vector2 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineStrip(points, pointCount, color);
}

void feraw_DrawLineBezier(BruterList* stack)
{
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineBezier(start, end, thick, color);
}

void feraw_DrawCircle(BruterList* stack)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircle(centerX, centerY, radius, color);
}

void feraw_DrawCircleSector(BruterList* stack)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    float startAngle = bruter_pop_float(stack);
    float endAngle = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
}

void feraw_DrawCircleSectorLines(BruterList* stack)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    float startAngle = bruter_pop_float(stack);
    float endAngle = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
}

void feraw_DrawCircleGradient(BruterList* stack)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    Color innerColor = color_from_int(bruter_pop_int(stack));
    Color outerColor = color_from_int(bruter_pop_int(stack));
    DrawCircleGradient(centerX, centerY, radius, innerColor, outerColor);
}

void feraw_DrawCircleLines(BruterList* stack)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleLines(centerX, centerY, radius, color);
}

void feraw_DrawRectangle(BruterList* stack)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangle(posX, posY, width, height, color);
}
void feraw_DrawRectangleRec(BruterList* stack)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRec(rec, color);
}

void feraw_DrawRectanglePro(BruterList* stack)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectanglePro(rec, origin, rotation, color);
}

void feraw_DrawRectangleGradientH(BruterList* stack)
{
    int posx = bruter_pop_int(stack);
    int posy = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color left = color_from_int(bruter_pop_int(stack));
    Color right = color_from_int(bruter_pop_int(stack));
    DrawRectangleGradientH(posx, posy, width, height, left, right);
}

void feraw_DrawRectangleGradientEx(BruterList* stack)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    Color color3 = color_from_int(bruter_pop_int(stack));
    Color color4 = color_from_int(bruter_pop_int(stack));
    DrawRectangleGradientEx(rec, color1, color2, color3, color4);
}

void feraw_DrawRectangleLines(BruterList* stack)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleLines(posX, posY, width, height, color);
}

void feraw_DrawRectangleLinesEx(BruterList* stack)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleLinesEx(rec, thick, color);
}

void feraw_DrawRectangleRounded(BruterList* stack)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRounded(rec, roundness, segments, color);
}

void feraw_DrawRectangleRoundedLines(BruterList* stack)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRoundedLines(rec, roundness, segments, color);
}

void feraw_DrawRectangleRoundedLinesEx(BruterList* stack)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRoundedLinesEx(rec, roundness, segments, thick, color);
}

void feraw_DrawTriangle(BruterList* stack)
{
    Vector2 v1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangle(v1, v2, v3, color);
}

void feraw_DrawTriangleLines(BruterList* stack)
{
    Vector2 v1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleLines(v1, v2, v3, color);
}

void feraw_DrawTriangleFan(BruterList* stack)
{
    Vector2 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleFan(points, pointCount, color);
}

void feraw_DrawTriangleStrip(BruterList* stack)
{
    Vector2 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleStrip(points, pointCount, color);
}

void feraw_DrawPoly(BruterList* stack)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPoly(center, sides, radius, rotation, color);
}

void feraw_DrawPolyLines(BruterList* stack)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPolyLines(center, sides, radius, rotation, color);
}

void feraw_DrawPolyLinesEx(BruterList* stack)
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
void feraw_DrawSplineLinear(BruterList* stack)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineLinear(points, pointCount, thick, color);
}

void feraw_DrawSplineBasis(BruterList* stack)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBasis(points, pointCount, thick, color);
}

void feraw_DrawSplineCatmullRom(BruterList* stack)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineCatmullRom(points, pointCount, thick, color);
}

void feraw_DrawSplineBezierQuadratic(BruterList* stack)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBezierQuadratic(points, pointCount, thick, color);
}

void feraw_DrawSplineBezierCubic(BruterList* stack)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBezierCubic(points, pointCount, thick, color);
}

void feraw_DrawSplineSegmentLinear(BruterList* stack)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentLinear(p1, p2, thick, color);
}

void feraw_DrawSplineSegmentBasis(BruterList* stack)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
}

void feraw_DrawSplineSegmentCatmullRom(BruterList* stack)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
}

void feraw_DrawSplineSegmentBezierQuadratic(BruterList* stack)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentBezierQuadratic(p1, p2, p3, thick, color);
}

void feraw_DrawSplineSegmentBezierCubic(BruterList* stack)
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
void feraw_GetSplinePointLinear(BruterList* stack)
{
    Vector2 startPos = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 endPos = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointLinear(startPos, endPos, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetSplinePointBasis(BruterList* stack)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointBasis(p1, p2, p3, p4, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetSplinePointCatmullRom(BruterList* stack)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointCatmullRom(p1, p2, p3, p4, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetSplinePointBezierQuad(BruterList* stack)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointBezierQuad(p1, p2, p3, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetSplinePointBezierCubic(BruterList* stack)
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
void feraw_CheckCollisionRecs(BruterList* stack)
{
    Rectangle rec1 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle rec2 = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionRecs(rec1, rec2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionCircles(BruterList* stack)
{
    Vector2 center1 = vector2_constructor(bruter_pop_pointer(stack));
    float radius1 = bruter_pop_float(stack);
    Vector2 center2 = vector2_constructor(bruter_pop_pointer(stack));
    float radius2 = bruter_pop_float(stack);
    bool collision = CheckCollisionCircles(center1, radius1, center2, radius2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionCircleRec(BruterList* stack)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionCircleRec(center, radius, rec);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionCircleLine(BruterList* stack)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionCircleLine(center, radius, start, end);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionPointRec(BruterList* stack)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionPointRec(point, rec);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionPointCircle(BruterList* stack)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    bool collision = CheckCollisionPointCircle(point, center, radius);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionPointTriangle(BruterList* stack)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionPointTriangle(point, p1, p2, p3);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionPointLine(BruterList* stack)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    bool collision = CheckCollisionPointLine(point, start, end, threshold);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionPointPoly(BruterList* stack)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    bool collision = CheckCollisionPointPoly(point, points, pointCount);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionLines(BruterList* stack)
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

void feraw_GetCollisionRec(BruterList* stack)
{
    Rectangle rec1 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle rec2 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle collisionRec = GetCollisionRec(rec1, rec2);
    bruter_push_pointer(stack, rectangle_to_list(collisionRec), NULL, BRUTER_TYPE_LIST);
}

// image loading functions
void feraw_LoadImage(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Image image = LoadImage(fileName);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadImageRaw(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int format = bruter_pop_int(stack);
    int headerSize = bruter_pop_int(stack);
    Image image = LoadImageRaw(fileName, width, height, format, headerSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadImageAnim(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *framesCount = (int*)bruter_pop_pointer(stack);
    Image images = LoadImageAnim(fileName, framesCount);
    bruter_push_pointer(stack, &images, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_LoadImageAnimFromMemory(BruterList* stack)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    const unsigned char *fileData = (const unsigned char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *framesCount = (int*)bruter_pop_pointer(stack);
    Image images = LoadImageAnimFromMemory(fileType, fileData, dataSize, framesCount);
    bruter_push_pointer(stack, &images, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_LoadImageFromMemory(BruterList* stack)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    const unsigned char *fileData = (const unsigned char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Image image = LoadImageFromMemory(fileType, fileData, dataSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadImageFromTexture(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Image image = LoadImageFromTexture(texture);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadImageFromScreen(BruterList* stack)
{
    Image image = LoadImageFromScreen();
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsImageValid(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    bool isValid = IsImageValid(image);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UnloadImage(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    UnloadImage(image);
}

void feraw_ExportImage(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportImage(image, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

void feraw_ExportImageToMemory(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileType = (char*)bruter_pop_pointer(stack);
    int *dataSize = (int*)bruter_pop_pointer(stack);
    unsigned char *data = ExportImageToMemory(image, fileType, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_ExportImageAsCode(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportImageAsCode(image, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// image generation functions
void feraw_GenImageColor(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    Image image = GenImageColor(width, height, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenImageGradientLinear(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int direction = bruter_pop_int(stack);
    Color start = color_from_int(bruter_pop_int(stack));
    Color end = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientLinear(width, height, direction, start, end);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenImageGradientRadial(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float density = bruter_pop_float(stack);
    Color inner = color_from_int(bruter_pop_int(stack));
    Color outer = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientRadial(width, height, density, inner, outer);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenImageGradientSquare(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float density = bruter_pop_float(stack);
    Color inner = color_from_int(bruter_pop_int(stack));
    Color outer = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientSquare(width, height, density, inner, outer);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenImageChecked(BruterList* stack)
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

void feraw_GenImageWhiteNoise(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float factor = bruter_pop_float(stack);
    Image image = GenImageWhiteNoise(width, height, factor);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenImagePerlinNoise(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int offsetX = bruter_pop_int(stack);
    int offsetY = bruter_pop_int(stack);
    float scale = bruter_pop_float(stack);
    Image image = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenImageCellular(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int tileSize = bruter_pop_int(stack);
    Image image = GenImageCellular(width, height, tileSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenImageText(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    char *text = (char*)bruter_pop_pointer(stack);
    Image image = GenImageText(width, height, text);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

// image manipulation functions

void feraw_ImageCopy(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image copiedImage = ImageCopy(image);
    bruter_push_pointer(stack, image_to_list(copiedImage), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageFromImage(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Image subImage = ImageFromImage(image, rec);
    bruter_push_pointer(stack, image_to_list(subImage), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageFromChannel(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int channel = bruter_pop_int(stack);
    Image channelImage = ImageFromChannel(image, channel);
    bruter_push_pointer(stack, image_to_list(channelImage), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageText(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    Image image = ImageText(text, fontSize, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageTextEx(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    Image image = ImageTextEx(font, text, fontSize, spacing, tint);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageFormat(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newFormat = bruter_pop_int(stack);
    ImageFormat(&image, newFormat);
}

void feraw_ImageToPot(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color fill = color_from_int(bruter_pop_int(stack));
    ImageToPOT(&image, fill);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageCrop(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle crop = rectangle_constructor(bruter_pop_pointer(stack));
    ImageCrop(&image, crop);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageAlphaCrop(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    ImageAlphaCrop(&image, threshold);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageAlphaClear(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    float threshold = bruter_pop_float(stack);
    ImageAlphaClear(&image, color, threshold);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageAlphaMask(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image mask = image_constructor(bruter_pop_pointer(stack));
    ImageAlphaMask(&image, mask);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageAlphaPremultiply(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageAlphaPremultiply(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageBlurGlaussian(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int blurSize = bruter_pop_int(stack);
    ImageBlurGaussian(&image, blurSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageKernelConvolution(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float *kernel = (float*)bruter_pop_pointer(stack);
    int kernelsize = bruter_pop_int(stack);
    ImageKernelConvolution(&image, kernel, kernelsize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageResize(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newWidth = bruter_pop_int(stack);
    int newHeight = bruter_pop_int(stack);
    ImageResize(&image, newWidth, newHeight);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageResizeNn(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newWidth = bruter_pop_int(stack);
    int newHeight = bruter_pop_int(stack);
    ImageResizeNN(&image, newWidth, newHeight);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageResizeCanvas(BruterList* stack)
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

void feraw_ImageMipmaps(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageMipmaps(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDither(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int rBpp = bruter_pop_int(stack);
    int gBpp = bruter_pop_int(stack);
    int bBpp = bruter_pop_int(stack);
    int aBpp = bruter_pop_int(stack);
    ImageDither(&image, rBpp, gBpp, bBpp, aBpp);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageFlipVertical(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageFlipVertical(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageFlipHorizontal(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageFlipHorizontal(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageRotate(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float degrees = bruter_pop_float(stack);
    ImageRotate(&image, degrees);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageRotateCw(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageRotateCW(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageRotateCcw(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageRotateCCW(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageColorTint(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageColorTint(&image, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageColorInvert(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageColorInvert(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageColorGrayscale(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageColorGrayscale(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageColorContrast(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float contrast = bruter_pop_float(stack);
    ImageColorContrast(&image, contrast);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageColorBrightness(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int brightness = bruter_pop_int(stack);
    ImageColorBrightness(&image, brightness);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageColorReplace(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    Color replace = color_from_int(bruter_pop_int(stack));
    ImageColorReplace(&image, color, replace);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadImageColors(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color *colors = LoadImageColors(image);
    int colorCount = image.width * image.height;
    bruter_push_pointer(stack, colors, NULL, BRUTER_TYPE_BUFFER);
    bruter_push_int(stack, colorCount, NULL, BRUTER_TYPE_ANY);
}

void feraw_LoadImagePalette(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int maxPaletteSize = bruter_pop_int(stack);
    int *colorCount = (int*)bruter_pop_pointer(stack);
    Color *palette = LoadImagePalette(image, maxPaletteSize, colorCount);
    bruter_push_pointer(stack, palette, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_UnloadImageColors(BruterList* stack)
{
    UnloadImageColors((Color*)bruter_pop_pointer(stack));
}

void feraw_UnloadImagePalette(BruterList* stack)
{
    Color *palette = (Color*)bruter_pop_pointer(stack);
    UnloadImagePalette(palette);
}

void feraw_GetImageAlphaBorder(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    Rectangle rec = GetImageAlphaBorder(image, threshold);
    bruter_push_pointer(stack, rectangle_to_list(rec), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetImageColor(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    Color color = GetImageColor(image, x, y);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

// image drawing functions
void feraw_ImageClearBackground(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageClearBackground(&image, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawPixel(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawPixel(&image, posX, posY, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawLine(BruterList* stack)
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

void feraw_ImageDrawLineEx(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawLineEx(&image, start, end, thick, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawCircle(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircle(&image, centerX, centerY, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawCircleLines(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircleLines(&image, centerX, centerY, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawRectangle(BruterList* stack)
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

void feraw_ImageDrawRectangleRec(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangleRec(&image, rec, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawRectangleLines(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    int thick = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangleLines(&image, rec, thick, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawTriangle(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangle(&image, p1, p2, p3, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawTriangleEx(BruterList* stack)
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

void feraw_ImageDrawTriangleLines(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleLines(&image, p1, p2, p3, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawTriangleFan(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleFan(&image, points, pointCount, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawTriangleStrip(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleStrip(&image, points, pointCount, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDraw(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image src = image_constructor(bruter_pop_pointer(stack));
    Rectangle srcRec = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle destRec = rectangle_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    ImageDraw(&image, src, srcRec, destRec, tint);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

void feraw_ImageDrawText(BruterList* stack)
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

void feraw_ImageDrawTextEx(BruterList* stack)
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

void feraw_LoadTexture(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Texture2D texture = LoadTexture(fileName);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadTextureFromImage(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Texture2D texture = LoadTextureFromImage(image);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadTextureCubemap(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int layout = bruter_pop_int(stack); // Assuming layout is an int representing the cubemap layout
    TextureCubemap texture = LoadTextureCubemap(image, layout);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}


void feraw_LoadRenderRexture(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    RenderTexture2D renderTexture = LoadRenderTexture(width, height);
    bruter_push_pointer(stack, render_texture_to_list(renderTexture), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsTextureValid(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    bool isValid = IsTextureValid(texture);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UnloadTexture(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    UnloadTexture(texture);
}

void feraw_IsRenderTextureValid(BruterList* stack)
{
    RenderTexture2D renderTexture = render_texture_constructor(bruter_pop_pointer(stack));
    bool isValid = IsRenderTextureValid(renderTexture);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UnloadRenderTexture(BruterList* stack)
{
    RenderTexture2D renderTexture = render_texture_constructor(bruter_pop_pointer(stack));
    UnloadRenderTexture(renderTexture);
}

void feraw_UpdateTexture(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    unsigned char *pixels = (unsigned char*)bruter_pop_pointer(stack);
    UpdateTexture(texture, pixels);
}

void feraw_UpdateTextureRec(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    unsigned char *pixels = (unsigned char*)bruter_pop_pointer(stack);
    UpdateTextureRec(texture, rec, pixels);
}

// texture configuration functions
void feraw_GenTextureMipmaps(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    GenTextureMipmaps(&texture);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetTextureFilter(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int filter = bruter_pop_int(stack);
    SetTextureFilter(texture, filter);
}

void feraw_SetTextureWrap(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int wrap = bruter_pop_int(stack);
    SetTextureWrap(texture, wrap);
}

// texture drawing functions
void feraw_DrawTexture(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTexture(texture, posX, posY, tint);
}

void feraw_DrawTextureEx(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureEx(texture, position, rotation, scale, tint);
}

void feraw_DrawTextureRec(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureRec(texture, sourceRec, position, tint);
}

void feraw_DrawTexturePro(BruterList* stack)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle destRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
}

void feraw_DrawTextureNpatch(BruterList* stack)
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

void feraw_ColorIsEqual(BruterList* stack)
{
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    bool isEqual = ColorIsEqual(color1, color2);
    bruter_push_int(stack, isEqual, NULL, BRUTER_TYPE_ANY);
}

void feraw_FadeColor(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float alpha = bruter_pop_float(stack);
    Color fadedColor = Fade(color, alpha);
    bruter_push_int(stack, color_to_int(fadedColor), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorToInt(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    int colorInt = ColorToInt(color);
    bruter_push_int(stack, colorInt, NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorNormalize(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Vector4 normalizedColor = ColorNormalize(color);
    bruter_push_pointer(stack, vector4_to_list(normalizedColor), NULL, BRUTER_TYPE_LIST);
}

void feraw_ColorFromNormalized(BruterList* stack)
{
    Vector4 normalizedColor = vector4_constructor(bruter_pop_pointer(stack));
    Color color = ColorFromNormalized(normalizedColor);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorToHsv(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Vector3 hsv = ColorToHSV(color);
    bruter_push_pointer(stack, vector3_to_list(hsv), NULL, BRUTER_TYPE_LIST);
}

void feraw_ColorFromHsv(BruterList* stack)
{
    float hue = bruter_pop_float(stack);
    float saturation = bruter_pop_float(stack);
    float value = bruter_pop_float(stack);
    Color color = ColorFromHSV(hue, saturation, value);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorTint(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    Color tintedColor = ColorTint(color, tint);
    bruter_push_int(stack, color_to_int(tintedColor), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorBrightness(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    int brightness = bruter_pop_int(stack);
    Color brightenedColor = ColorBrightness(color, brightness);
    bruter_push_int(stack, color_to_int(brightenedColor), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorContrast(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float contrast = bruter_pop_float(stack);
    Color contrastedColor = ColorContrast(color, contrast);
    bruter_push_int(stack, color_to_int(contrastedColor), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorAlpha(BruterList* stack)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float alpha = bruter_pop_float(stack);
    Color alphaColor = ColorAlpha(color, alpha);
    bruter_push_int(stack, color_to_int(alphaColor), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorAlphaBlend(BruterList* stack)
{
    Color dst = color_from_int(bruter_pop_int(stack));
    Color src = color_from_int(bruter_pop_int(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    Color blendedColor = ColorAlphaBlend(dst, src, tint);
    bruter_push_int(stack, color_to_int(blendedColor), NULL, BRUTER_TYPE_ANY);
}

void feraw_ColorLerp(BruterList* stack)
{
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    float amount = bruter_pop_float(stack);
    Color lerpedColor = ColorLerp(color1, color2, amount);
    bruter_push_int(stack, color_to_int(lerpedColor), NULL, BRUTER_TYPE_ANY);
}

void feraw_GetColor(BruterList* stack)
{
    int hexColor = bruter_pop_int(stack);
    Color color = GetColor(hexColor);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

void feraw_GetPixelColor(BruterList* stack)
{
    void* data = bruter_pop_pointer(stack);
    int format = bruter_pop_int(stack);
    Color color = GetPixelColor(data, format);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

void feraw_SetPixelColor(BruterList* stack)
{
    void *data = bruter_pop_pointer(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    int format = bruter_pop_int(stack);
    SetPixelColor(data, color, format);
}

void feraw_GetPixelDataSize(BruterList* stack)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int format = bruter_pop_int(stack);
    int size = GetPixelDataSize(width, height, format);
    bruter_push_int(stack, size, NULL, BRUTER_TYPE_ANY);
}

// font loading/unloading functions

void feraw_GetFontDefault(BruterList* stack)
{
    Font font = GetFontDefault();
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadFont(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Font font = LoadFont(fileName);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadFontEx(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    int *fontChars = (int*)bruter_pop_pointer(stack);
    int charsCount = bruter_pop_int(stack);
    Font font = LoadFontEx(fileName, fontSize, fontChars, charsCount);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadFontFromImage(BruterList* stack)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color key = color_from_int(bruter_pop_int(stack));
    int firstChar = bruter_pop_int(stack);
    Font font = LoadFontFromImage(image, key, firstChar);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadFontFromMemory(BruterList* stack)
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

void feraw_IsFontValid(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    bool isValid = IsFontValid(font);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_LoadFontData(BruterList* stack)
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

void feraw_GenImageFontAtlas(BruterList* stack)
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

void feraw_UnloadFontData(BruterList* stack)
{
    GlyphInfo *fontData = (GlyphInfo*)bruter_pop_pointer(stack);
    int glyphCount = bruter_pop_int(stack);
    UnloadFontData(fontData, glyphCount);
}

void feraw_UnloadFont(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    UnloadFont(font);
}

void feraw_ExportFontAsCode(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportFontAsCode(font, fileName);
}

// text drawing functions
void feraw_DrawFPS(BruterList* stack)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    DrawFPS(posX, posY);
}

void feraw_DrawText(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawText(text, posX, posY, fontSize, color);
}

void feraw_DrawTextEx(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextEx(font, text, position, fontSize, spacing, tint);
}

void feraw_DrawTextPro(BruterList* stack)
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

void feraw_DrawTextCodepoint(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextCodepoint(font, codepoint, position, fontSize, tint);
}

void feraw_DrawTextCodepoints(BruterList* stack)
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
void feraw_SetTextLineSpacing(BruterList* stack)
{
    float spacing = bruter_pop_float(stack);
    SetTextLineSpacing(spacing);
}

void feraw_MeasureText(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    int size = MeasureText(text, fontSize);
    bruter_push_int(stack, size, NULL, BRUTER_TYPE_ANY);
}

void feraw_MeasureTextEx(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Vector2 size = MeasureTextEx(font, text, fontSize, spacing);
    bruter_push_pointer(stack, vector2_to_list(size), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetGlyphIndex(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    int glyphIndex = GetGlyphIndex(font, codepoint);
    bruter_push_int(stack, glyphIndex, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetGlyphInfo(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    GlyphInfo glyphInfo = GetGlyphInfo(font, codepoint);
    bruter_push_pointer(stack, glyph_info_to_list(glyphInfo), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetGlyphAtlasRec(BruterList* stack)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    Rectangle rec = GetGlyphAtlasRec(font, codepoint);
    bruter_push_pointer(stack, rectangle_to_list(rec), NULL, BRUTER_TYPE_LIST);
}

// text string managment functions
void feraw_TextCopy(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *src = (char*)bruter_pop_pointer(stack);
    TextCopy(text, src);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextIsEqual(BruterList* stack)
{
    char *text1 = (char*)bruter_pop_pointer(stack);
    char *text2 = (char*)bruter_pop_pointer(stack);
    bool isEqual = TextIsEqual(text1, text2);
    bruter_push_int(stack, isEqual, NULL, BRUTER_TYPE_ANY);
}

void feraw_TextLength(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int length = TextLength(text);
    bruter_push_int(stack, length, NULL, BRUTER_TYPE_ANY);
}

void feraw_TextFormat(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *formattedText = strdup(TextFormat(text));
    bruter_push_pointer(stack, formattedText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextSubtext(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    int length = bruter_pop_int(stack);
    char *subText = strdup(TextSubtext(text, position, length));
    bruter_push_pointer(stack, subText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextReplace(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *find = (char*)bruter_pop_pointer(stack);
    char *replace = (char*)bruter_pop_pointer(stack);
    char *replacedText = TextReplace(text, find, replace);
    bruter_push_pointer(stack, replacedText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextInsert(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *insert = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    char *insertedText = TextInsert(text, insert, position);
    bruter_push_pointer(stack, insertedText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextJoin(BruterList* stack)
{
    const char **textList = bruter_pop_pointer(stack);
    int count = bruter_pop_int(stack);
    char *delimiter = (char*)bruter_pop_pointer(stack);
    const char *joinedText = TextJoin(textList, count, delimiter);
    bruter_push_pointer(stack, strdup(joinedText), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextSplit(BruterList* stack)
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

void feraw_TextAppend(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *appendText = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    TextAppend(text, appendText, &position);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextFindIndex(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *find = (char*)bruter_pop_pointer(stack);
    int index = TextFindIndex(text, find);
    bruter_push_int(stack, index, NULL, BRUTER_TYPE_ANY);
}

void feraw_TextToUpper(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    const char *upperText = TextToUpper(text);
    bruter_push_pointer(stack, strdup(upperText), NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextToLower(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *lowerText = strdup(TextToLower(text));
    bruter_push_pointer(stack, lowerText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextToPascal(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *pascalText = strdup(TextToPascal(text));
    bruter_push_pointer(stack, pascalText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextToSnake(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *snakeText = strdup(TextToSnake(text));
    bruter_push_pointer(stack, snakeText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextToCamel(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *camelText = strdup(TextToCamel(text));
    bruter_push_pointer(stack, camelText, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_TextToInteger(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int value = TextToInteger(text);
    bruter_push_int(stack, value, NULL, BRUTER_TYPE_ANY);
}

void feraw_TextToFloat(BruterList* stack)
{
    char *text = (char*)bruter_pop_pointer(stack);
    float value = TextToFloat(text);
    bruter_push_float(stack, value, NULL, BRUTER_TYPE_ANY);
}

// basic geometric 3D shapes drawing functions

void feraw_DrawLine3D(BruterList* stack)
{
    Vector3 start = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 end = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLine3D(start, end, color);
}

void feraw_DrawPoint3D(BruterList* stack)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPoint3D(position, color);
}

void feraw_DrawCircle3D(BruterList* stack)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
}

void feraw_DrawTriangle3D(BruterList* stack)
{
    Vector3 p1 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p2 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p3 = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangle3D(p1, p2, p3, color);
}

void feraw_DrawTriangleStrip3D(BruterList* stack)
{
    const Vector3 *points = bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleStrip3D(points, pointCount, color);
}

void feraw_DrawCube(BruterList* stack)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCube(position, width, height, length, color);
}

void feraw_DrawCubeWires(BruterList* stack)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCubeWires(position, width, height, length, color);
}

void feraw_DrawSphere(BruterList* stack)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphere(center, radius, color);
}

void feraw_DrawSphereEx(BruterList* stack)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphereEx(center, radius, rings, slices, color);
}

void feraw_DrawSphereWires(BruterList* stack)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphereWires(center, radius, rings, slices, color);
}

void feraw_DrawCylinder(BruterList* stack)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
}

void feraw_DrawCylinderEx(BruterList* stack)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderEx(startPos, endPos, radiusTop, radiusBottom, slices, color);
}

void feraw_DrawCylinderWires(BruterList* stack)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
}

void feraw_DrawCylinderWiresEx(BruterList* stack)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderWiresEx(startPos, endPos, radiusTop, radiusBottom, slices, color);
}

void feraw_DrawCapsule(BruterList* stack)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    int rings = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCapsule(startPos, endPos, radius, slices, rings, color);
}

void feraw_DrawPlane(BruterList* stack)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPlane(center, size, color);
}

void feraw_DrawRay(BruterList* stack)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRay(ray, color);
}

void feraw_DrawGrid(BruterList* stack)
{
    int slices = bruter_pop_int(stack);
    float spacing = bruter_pop_float(stack);
    DrawGrid(slices, spacing);
}

// model managment functions

void feraw_LoadModel(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Model model = LoadModel(fileName);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadModelFromMesh(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Model model = LoadModelFromMesh(mesh);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsModelValid(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    bool isValid = IsModelValid(model);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UnloadModel(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    UnloadModel(model);
}

void feraw_GetModelBoundingBox(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    BoundingBox boundingBox = GetModelBoundingBox(model);
    bruter_push_pointer(stack, bounding_box_to_list(boundingBox), NULL, BRUTER_TYPE_LIST);
}

// model drawing functions
void feraw_DrawModel(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModel(model, position, scale, tint);
}

void feraw_DrawModelEx(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

void feraw_DrawModelWires(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelWires(model, position, scale, tint);
}

void feraw_DrawModelWiresEx(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

void feraw_DrawPoints(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelPoints(model, position, scale, tint);
}

void feraw_DrawPointsEx(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelPointsEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

void feraw_DrawBoudingBox(BruterList* stack)
{
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawBoundingBox(box, color);
}

void feraw_DrawBillboard(BruterList* stack)
{
    Camera camera = camera3d_constructor(bruter_pop_pointer(stack));
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float size = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawBillboard(camera, texture, position, size, tint);
}

void feraw_DrawBillboardRec(BruterList* stack)
{
    Camera camera = camera3d_constructor(bruter_pop_pointer(stack));
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawBillboardRec(camera, texture, sourceRec, position, size, tint);
}

void feraw_DrawBillboardPro(BruterList* stack)
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
void feraw_UploadMesh(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    bool dynamic = bruter_pop_int(stack);
    UploadMesh(&mesh, dynamic);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_UpdateMeshBuffer(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    int index = bruter_pop_int(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int offset = bruter_pop_int(stack);
    UpdateMeshBuffer(mesh, index, data, dataSize, offset);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadMesh(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    UnloadMesh(mesh);
}

void feraw_DrawMesh(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Material material = material_constructor(bruter_pop_pointer(stack));
    Matrix transform = matrix_constructor(bruter_pop_pointer(stack));
    DrawMesh(mesh, material, transform);
}

void feraw_DrawMeshInstanced(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Material material = material_constructor(bruter_pop_pointer(stack));
    Matrix *transforms = (Matrix*)bruter_pop_pointer(stack);
    int instanceCount = bruter_pop_int(stack);
    DrawMeshInstanced(mesh, material, transforms, instanceCount);
}

void feraw_GetMeshBoundingBox(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    BoundingBox boundingBox = GetMeshBoundingBox(mesh);
    bruter_push_pointer(stack, bounding_box_to_list(boundingBox), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshTangents(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    GenMeshTangents(&mesh);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_ExportMesh(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportMesh(mesh, fileName);
}

void feraw_ExportMeshAsCode(BruterList* stack)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportMeshAsCode(mesh, fileName);
}

// mesh generation functions
void feraw_GenMeshPoly(BruterList* stack)
{
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    Mesh mesh = GenMeshPoly(sides, radius);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshPlane(BruterList* stack)
{
    float width = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    int resX = bruter_pop_int(stack);
    int resZ = bruter_pop_int(stack);
    Mesh mesh = GenMeshPlane(width, length, resX, resZ);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshCube(BruterList* stack)
{
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Mesh mesh = GenMeshCube(width, height, length);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshSphere(BruterList* stack)
{
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshSphere(radius, rings, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshHemiSphere(BruterList* stack)
{
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshHemiSphere(radius, rings, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshCylinder(BruterList* stack)
{
    float radius = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshCylinder(radius, height, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshCone(BruterList* stack)
{
    float radius = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshCone(radius, height, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshTorus(BruterList* stack)
{
    float radius = bruter_pop_float(stack);
    float tubeRadius = bruter_pop_float(stack);
    int radialSegments = bruter_pop_int(stack);
    int tubularSegments = bruter_pop_int(stack);
    Mesh mesh = GenMeshTorus(radius, tubeRadius, radialSegments, tubularSegments);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshKnot(BruterList* stack)
{
    float radius = bruter_pop_float(stack);
    float tubeRadius = bruter_pop_float(stack);
    int radialSegments = bruter_pop_int(stack);
    int sides = bruter_pop_int(stack);
    Mesh mesh = GenMeshKnot(radius, tubeRadius, radialSegments, sides);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshHeightmap(BruterList* stack)
{
    Image heightmap = image_constructor(bruter_pop_pointer(stack));
    Vector3 size = vector3_constructor(bruter_pop_pointer(stack));
    Mesh mesh = GenMeshHeightmap(heightmap, size);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

void feraw_GenMeshCubicmap(BruterList* stack)
{
    Image cubicmap = image_constructor(bruter_pop_pointer(stack));
    Vector3 cubeSize = vector3_constructor(bruter_pop_pointer(stack));
    Mesh mesh = GenMeshCubicmap(cubicmap, cubeSize);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

// material loading/unloading functions
void feraw_LoadMaterials(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *materialCount = (int*)bruter_pop_pointer(stack);
    bruter_push_pointer(stack, LoadMaterials(fileName, materialCount), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadMaterialDefault(BruterList* stack)
{
    Material material = LoadMaterialDefault();
    bruter_push_pointer(stack, material_to_list(material), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsMaterialValid(BruterList* stack)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    bool isValid = IsMaterialValid(material);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UnloadMaterial(BruterList* stack)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    UnloadMaterial(material);
}

void feraw_SetMaterialTexture(BruterList* stack)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    int mapType = bruter_pop_int(stack); // Assuming mapType is an int representing the texture type
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    SetMaterialTexture(&material, mapType, texture);
    bruter_push_pointer(stack, material_to_list(material), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetModelMeshMaterial(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    int meshId = bruter_pop_int(stack);
    int materialId = bruter_pop_int(stack);
    SetModelMeshMaterial(&model, meshId, materialId);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

// model animations loading/unloading functions
void feraw_LoadModelAnimations(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *animCount = (int*)bruter_pop_pointer(stack);
    ModelAnimation *animations = LoadModelAnimations(fileName, animCount);
    bruter_push_pointer(stack, animations, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_UpdateModelAnimation(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    int frame = bruter_pop_int(stack);
    UpdateModelAnimation(model, animation, frame);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

void feraw_UpdateModelAnimationBones(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    int frame = bruter_pop_int(stack);
    UpdateModelAnimationBones(model, animation, frame);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadModelAnimation(BruterList* stack)
{
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    UnloadModelAnimation(animation);
}

void feraw_UnloadModelAnimations(BruterList* stack)
{
    ModelAnimation *animations = (ModelAnimation*)bruter_pop_pointer(stack);
    int animCount = bruter_pop_int(stack);
    UnloadModelAnimations(animations, animCount);
}

void feraw_IsModelAnimationValid(BruterList* stack)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    bool isValid = IsModelAnimationValid(model, animation);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

// collision detection functions

void feraw_CheckCollisionSpheres(BruterList* stack)
{
    Vector3 center1 = vector3_constructor(bruter_pop_pointer(stack));
    float radius1 = bruter_pop_float(stack);
    Vector3 center2 = vector3_constructor(bruter_pop_pointer(stack));
    float radius2 = bruter_pop_float(stack);
    bool collision = CheckCollisionSpheres(center1, radius1, center2, radius2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionBoxes(BruterList* stack)
{
    BoundingBox box1 = bounding_box_constructor(bruter_pop_pointer(stack));
    BoundingBox box2 = bounding_box_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionBoxes(box1, box2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_CheckCollisionBoxSphere(BruterList* stack)
{
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    bool collision = CheckCollisionBoxSphere(box, center, radius);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetRayCollisionSphere(BruterList* stack)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    RayCollision collision = GetRayCollisionSphere(ray, center, radius);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetRayCollisionBox(BruterList* stack)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionBox(ray, box);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetRayCollisionMesh(BruterList* stack)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Matrix transform = matrix_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionMesh(ray, mesh, transform);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetRayCollisionTriangle(BruterList* stack)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Vector3 p1 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p2 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p3 = vector3_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionTriangle(ray, p1, p2, p3);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetRayCollisionQuad(BruterList* stack)
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
void feraw_InitAudioDevice(BruterList* stack)
{
    InitAudioDevice();
}

void feraw_CloseAudioDevice(BruterList* stack)
{
    CloseAudioDevice();
}

void feraw_IsAudioDeviceReady(BruterList* stack)
{
    bool isReady = IsAudioDeviceReady();
    bruter_push_int(stack, isReady, NULL, BRUTER_TYPE_ANY);
}

void feraw_SetMasterVolume(BruterList* stack)
{
    float volume = bruter_pop_float(stack);
    SetMasterVolume(volume);
}

void feraw_GetMasterVolume(BruterList* stack)
{
    float volume = GetMasterVolume();
    bruter_push_float(stack, volume, NULL, BRUTER_TYPE_ANY);
}

// wave/sound loading/unloading functions

void feraw_LoadWave(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Wave wave = LoadWave(fileName);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadWaveFromMemory(BruterList* stack)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Wave wave = LoadWaveFromMemory(fileType, data, dataSize);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsWaveValid(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    bool isValid = IsWaveValid(wave);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_LoadSound(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Sound sound = LoadSound(fileName);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadSoundFromWave(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    Sound sound = LoadSoundFromWave(wave);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadSoundAlias(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    Sound aliasSound = LoadSoundAlias(sound);
    bruter_push_pointer(stack, sound_to_list(aliasSound), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsSoundValid(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    bool isValid = IsSoundValid(sound);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UpdateSound(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    void *data = bruter_pop_pointer(stack);
    int samplesCount = bruter_pop_int(stack);
    UpdateSound(sound, data, samplesCount);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

void feraw_UnloadWave(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    UnloadWave(wave);
}

void feraw_UnloadSound(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    UnloadSound(sound);
}

void feraw_UnloadSoundAlias(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    UnloadSoundAlias(sound);
}

void feraw_ExportWave(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportWave(wave, fileName);
}

void feraw_ExportWaveAsCode(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportWaveAsCode(wave, fileName);
}

// wave/sound management functions
void feraw_PlaySound(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    PlaySound(sound);
}

void feraw_StopSound(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    StopSound(sound);
}

void feraw_PauseSound(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    PauseSound(sound);
}

void feraw_ResumeSound(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    ResumeSound(sound);
}

void feraw_IsSoundPlaying(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    bool isPlaying = IsSoundPlaying(sound);
    bruter_push_int(stack, isPlaying, NULL, BRUTER_TYPE_ANY);
}

void feraw_SetSoundVolume(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetSoundVolume(sound, volume);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetSoundPitch(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetSoundPitch(sound, pitch);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetSoundPan(BruterList* stack)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetSoundPan(sound, pan);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

void feraw_WaveCopy(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    Wave copiedWave = WaveCopy(wave);
    bruter_push_pointer(stack, wave_to_list(copiedWave), NULL, BRUTER_TYPE_LIST);
}

void feraw_WaveCrop(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    int initSample = bruter_pop_int(stack);
    int finalSample = bruter_pop_int(stack);
    WaveCrop(&wave, initSample, finalSample);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

void feraw_WaveFormat(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    int sampleRate = bruter_pop_int(stack);
    int sampleSize = bruter_pop_int(stack);
    int channels = bruter_pop_int(stack);
    WaveFormat(&wave, sampleRate, sampleSize, channels);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadWaveSamples(BruterList* stack)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    void *samples = LoadWaveSamples(wave);
    bruter_push_pointer(stack, samples, NULL, BRUTER_TYPE_BUFFER);
}

void feraw_UnloadWaveSamples(BruterList* stack)
{
    void *samples = bruter_pop_pointer(stack);
    UnloadWaveSamples(samples);
}

// music management functions
void feraw_LoadMusicStream(BruterList* stack)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Music music = LoadMusicStream(fileName);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

void feraw_LoadMusicStreamFromMemory(BruterList* stack)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Music music = LoadMusicStreamFromMemory(fileType, data, dataSize);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsMusicValid(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    bool isValid = IsMusicValid(music);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UnloadMusicStream(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    UnloadMusicStream(music);
}

void feraw_PlayMusicStream(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    PlayMusicStream(music);
}

void feraw_IsMusicStreamPlaying(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    bool isPlaying = IsMusicStreamPlaying(music);
    bruter_push_int(stack, isPlaying, NULL, BRUTER_TYPE_ANY);
}

void feraw_UpdateMusicStream(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    UpdateMusicStream(music);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

void feraw_StopMusicStream(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    StopMusicStream(music);
}

void feraw_PauseMusicStream(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    PauseMusicStream(music);
}

void feraw_ResumeMusicStream(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    ResumeMusicStream(music);
}

void feraw_SeekMusicStream(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float position = bruter_pop_float(stack);
    SeekMusicStream(music, position);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetMusicVolume(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetMusicVolume(music, volume);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetMusicPitch(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetMusicPitch(music, pitch);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetMusicPan(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetMusicPan(music, pan);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

void feraw_GetMusicTimeLength(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float length = GetMusicTimeLength(music);
    bruter_push_float(stack, length, NULL, BRUTER_TYPE_ANY);
}

void feraw_GetMusicTimePlayed(BruterList* stack)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float playedTime = GetMusicTimePlayed(music);
    bruter_push_float(stack, playedTime, NULL, BRUTER_TYPE_ANY);
}

// audiostream management functions
void feraw_LoadAudioStream(BruterList* stack)
{
    int sampleRate = bruter_pop_int(stack);
    int sampleSize = bruter_pop_int(stack);
    int channels = bruter_pop_int(stack);
    AudioStream stream = LoadAudioStream(sampleRate, sampleSize, channels);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsAudioStreamValid(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    bool isValid = IsAudioStreamValid(stream);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

void feraw_UnloadAudioStream(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    UnloadAudioStream(stream);
}

void feraw_UpdateAudioStream(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    void *data = bruter_pop_pointer(stack);
    int samplesCount = bruter_pop_int(stack);
    UpdateAudioStream(stream, data, samplesCount);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_IsAudioStreamProcessed(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    bool isProcessed = IsAudioStreamProcessed(stream);
    bruter_push_int(stack, isProcessed, NULL, BRUTER_TYPE_ANY);
}

void feraw_PlayAudioStream(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    PlayAudioStream(stream);
}

void feraw_PauseAudioStream(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    StopAudioStream(stream);
}

void feraw_StopAudioStream(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    PauseAudioStream(stream);
}

void feraw_ResumeAudioStream(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    ResumeAudioStream(stream);
}

void feraw_SetAudioStreamVolume(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetAudioStreamVolume(stream, volume);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetAudioStreamPitch(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetAudioStreamPitch(stream, pitch);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetAudioStreamPan(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetAudioStreamPan(stream, pan);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_SetAudioStreamBufferSizeDefault(BruterList* stack)
{
    int size = bruter_pop_int(stack);
    SetAudioStreamBufferSizeDefault(size);
}

void feraw_SetAudioStreamCallback(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback callback = (AudioCallback)bruter_pop_pointer(stack);
    SetAudioStreamCallback(stream, callback);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_AttachAudioStreamProcessor(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    AttachAudioStreamProcessor(stream, processor);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_DetachAudioStreamProcessor(BruterList* stack)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    DetachAudioStreamProcessor(stream, processor);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

void feraw_AttachAudioMixedProcessor(BruterList* stack)
{
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    AttachAudioMixedProcessor(processor);
}

void feraw_DetachAudioMixedProcessor(BruterList* stack)
{
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    DetachAudioMixedProcessor(processor);
}