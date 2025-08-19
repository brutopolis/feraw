#include "bruter.h"
#include "raylib.h"

/*
notes:
- everything vr-related is not tested and is not planned to be any soon
- everything audio-related needs some testing
*/

Vector2 vector2_constructor(BruterList *vec2)
{
    float x = vec2->data[0].f;
    float y = vec2->data[1].f;
    
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

BruterList *color_to_int(Color color)
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

Camera3D camera3d_constructor(BruterList *camera3d)
{
    Vector3 position = vector3_constructor(camera3d->data[0].p);
    Vector3 target = vector3_constructor(camera3d->data[1].p);
    Vector3 up = vector3_constructor(camera3d->data[2].p);
    float fovy = camera3d->data[3].f;
    int projection = camera3d->data[4].i;
    
    Camera3D cam;
    cam.position = position;
    cam.target = target;
    cam.up = up;
    cam.fovy = fovy;
    cam.projection = projection;
    return cam;
}

BruterList *camera3d_to_list(Camera3D cam)
{
    BruterList *list = bruter_new(5, true, true);
    bruter_push_pointer(list, vector3_to_list(cam.position), "position", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(cam.target), "target", BRUTER_TYPE_LIST);
    bruter_push_pointer(list, vector3_to_list(cam.up), "up", BRUTER_TYPE_LIST);
    bruter_push_float(list, cam.fovy, "fovy", BRUTER_TYPE_FLOAT);
    bruter_push_int(list, cam.projection, "projection", BRUTER_TYPE_ANY);
    return list;
}

Camera2D camera2d_constructor(BruterList *camera2d)
{
    Vector2 offset = vector2_constructor(camera2d->data[0].p);
    Vector2 target = vector2_constructor(camera2d->data[1].p);
    float rotation = camera2d->data[2].f;
    float zoom = camera2d->data[3].f;
    
    Camera2D cam;
    cam.offset = offset;
    cam.target = target;
    cam.rotation = rotation;
    cam.zoom = zoom;
    return cam;
}

BruterList *camera2d_to_list(Camera2D cam)
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
    BruterList *list = bruter_new(8, true, true);

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
function(raylib_init_window)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    char *title = (char*)bruter_pop_pointer(stack);
    InitWindow(width, height, title);
}

function(raylib_close_window)
{
    CloseWindow();
}

function(raylib_window_should_close)
{
    bool shouldClose = WindowShouldClose();
    bruter_push_int(stack, shouldClose, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_ready)
{
    bool isReady = IsWindowReady();
    bruter_push_int(stack, isReady, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_fullscreen)
{
    bool isFullscreen = IsWindowFullscreen();
    bruter_push_int(stack, isFullscreen, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_hidden)
{
    bool isHidden = IsWindowHidden();
    bruter_push_int(stack, isHidden, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_minimized)
{
    bool isMinimized = IsWindowMinimized();
    bruter_push_int(stack, isMinimized, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_maximized)
{
    bool isMaximized = IsWindowMaximized();
    bruter_push_int(stack, isMaximized, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_focused)
{
    bool isFocused = IsWindowFocused();
    bruter_push_int(stack, isFocused, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_resized)
{
    bool isResized = IsWindowResized();
    bruter_push_int(stack, isResized, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_window_state)
{
    int flags = bruter_pop_int(stack);
    bool isState = IsWindowState(flags);
    bruter_push_int(stack, isState, NULL, BRUTER_TYPE_ANY);
}

function(raylib_set_window_state)
{
    int flags = bruter_pop_int(stack);
    SetWindowState(flags);
}

function(raylib_clear_window_state)
{
    int flags = bruter_pop_int(stack);
    ClearWindowState(flags);
}

function(raylib_toggle_fullscreen)
{
    ToggleFullscreen();
}

function(raylib_toggle_borderless_windowed)
{
    ToggleBorderlessWindowed();
}

function(raylib_maximize_window)
{
    MaximizeWindow();
}

function(raylib_minimize_window)
{
    MinimizeWindow();
}

function(raylib_restore_window)
{
    RestoreWindow();
}

function(raylib_set_window_icon)
{
    Image icon = image_constructor(bruter_pop_pointer(stack));
    SetWindowIcon(icon);
}

function(raylib_set_window_icons)
{
    BruterList *icons = (BruterList*)bruter_pop_pointer(stack);
    SetWindowIcons(icons->data, icons->size);
}

function(raylib_set_window_title)
{
    char *title = (char*)bruter_pop_pointer(stack);
    SetWindowTitle(title);
}

function(raylib_set_window_position)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    SetWindowPosition(x, y);
}

function(raylib_set_window_monitor)
{
    int monitor = bruter_pop_int(stack);
    SetWindowMonitor(monitor);
}

function(raylib_set_window_min_size)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowMinSize(width, height);
}

function(raylib_set_window_max_size)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowMaxSize(width, height);
}

function(raylib_set_window_size)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    SetWindowSize(width, height);
}

function(raylib_set_window_opacity)
{
    float opacity = bruter_pop_float(stack);
    SetWindowOpacity(opacity);
}

function(raylib_set_window_focused)
{
    SetWindowFocused();
}

function(raylib_get_window_handle)
{
    bruter_push_pointer(stack, GetWindowHandle(), NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_screen_width)
{
    int width = GetScreenWidth();
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_screen_height)
{
    int height = GetScreenHeight();
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_monitor_count)
{
    int count = GetMonitorCount();
    bruter_push_int(stack, count, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_current_monitor)
{
    int monitor = GetCurrentMonitor();
    bruter_push_int(stack, monitor, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_monitor_position)
{
    int monitor = bruter_pop_int(stack);
    Vector2 position = GetMonitorPosition(monitor);
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_monitor_width)
{
    int monitor = bruter_pop_int(stack);
    int width = GetMonitorWidth(monitor);
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_monitor_height)
{
    int monitor = bruter_pop_int(stack);
    int height = GetMonitorHeight(monitor);
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_monitor_physical_width)
{
    int monitor = bruter_pop_int(stack);
    int width = GetMonitorPhysicalWidth(monitor);
    bruter_push_int(stack, width, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_monitor_physical_height)
{
    int monitor = bruter_pop_int(stack);
    int height = GetMonitorPhysicalHeight(monitor);
    bruter_push_int(stack, height, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_monitor_refresh_rate)
{
    int monitor = bruter_pop_int(stack);
    int refreshRate = GetMonitorRefreshRate(monitor);
    bruter_push_int(stack, refreshRate, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_window_position)
{
    Vector2 position = GetWindowPosition();
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_window_scale_dpi)
{
    Vector2 scale = GetWindowScaleDPI();
    bruter_push_pointer(stack, vector2_to_list(scale), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_monitor_name)
{
    int monitor = bruter_pop_int(stack);
    char *name = GetMonitorName(monitor);
    bruter_push_pointer(stack, name, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_set_clipboard_text)
{
    char *text = (char*)bruter_pop_pointer(stack);
    SetClipboardText(text);
}

function(raylib_get_clipboard_text)
{
    char *text = GetClipboardText();
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_get_clipboard_image)
{
    Image image = GetClipboardImage();
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_enable_event_waiting)
{
    EnableEventWaiting();
}

function(raylib_disable_event_waiting)
{
    DisableEventWaiting();
}

// Cursor-related functions
function(raylib_show_cursor)
{
    ShowCursor();
}

function(raylib_hide_cursor)
{
    HideCursor();
}

function(raylib_is_cursor_hidden)
{
    bool isHidden = IsCursorHidden();
    bruter_push_int(stack, isHidden, NULL, BRUTER_TYPE_ANY);
}

function(raylib_enable_cursor)
{
    EnableCursor();
}

function(raylib_disable_cursor)
{
    DisableCursor();
}

function(raylib_is_cursor_on_screen)
{
    bool isOnScreen = IsCursorOnScreen();
    bruter_push_int(stack, isOnScreen, NULL, BRUTER_TYPE_ANY);
}

// Drawing-related functions
function(raylib_clear_background)
{
    Color color = color_from_int(bruter_pop_int(stack));
    ClearBackground(color);
}

function(raylib_begin_drawing)
{
    BeginDrawing();
}

function(raylib_end_drawing)
{
    EndDrawing();
}

function(raylib_begin_mode_2d)
{
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    BeginMode2D(camera);
}

function(raylib_end_mode_2d)
{
    EndMode2D();
}

function(raylib_begin_mode_3d)
{
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    BeginMode3D(camera);
}

function(raylib_end_mode_3d)
{
    EndMode3D();
}

function(raylib_begin_shader_mode)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    BeginShaderMode(shader);
}

function(raylib_end_shader_mode)
{
    EndShaderMode();
}

function(raylib_begin_blend_mode)
{
    int mode = bruter_pop_int(stack);
    BeginBlendMode(mode);
}

function(raylib_end_blend_mode)
{
    EndBlendMode();
}

function(raylib_begin_scissor_mode)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    BeginScissorMode(x, y, width, height);
}

function(raylib_end_scissor_mode)
{
    EndScissorMode();
}

function(raylib_begin_vr_stereo_mode)
{
    VrStereoConfig config = vr_stereo_config_constructor(bruter_pop_pointer(stack));
    BeginVrStereoMode(config);
}

function(raylib_end_vr_stereo_mode)
{
    EndVrStereoMode();
}

function(raylib_load_vr_stereo_config)
{
    VrDeviceInfo info = vr_device_info_constructor(bruter_pop_pointer(stack));
    VrStereoConfig config = LoadVrStereoConfig(info);
    bruter_push_pointer(stack, vr_stereo_config_to_list(config), NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_vr_stereo_config)
{
    VrStereoConfig config = vr_stereo_config_constructor(bruter_pop_pointer(stack));
    UnloadVrStereoConfig(config);
}

function(raylib_load_shader)
{
    char *vsFileName = (char*)bruter_pop_pointer(stack);
    char *fsFileName = (char*)bruter_pop_pointer(stack);
    Shader shader = LoadShader(vsFileName, fsFileName);
    bruter_push_pointer(stack, shader_to_list(shader), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_shader_from_memory)
{
    char *vsCode = (char*)bruter_pop_pointer(stack);
    char *fsCode = (char*)bruter_pop_pointer(stack);
    Shader shader = LoadShaderFromMemory(vsCode, fsCode);
    bruter_push_pointer(stack, shader_to_list(shader), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_shader_valid)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    bool isValid = IsShaderValid(shader);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_shader_location)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    char *uniformName = (char*)bruter_pop_pointer(stack);
    int location = GetShaderLocation(shader, uniformName);
    bruter_push_int(stack, location, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_shader_location_attrib)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    char *attribName = (char*)bruter_pop_pointer(stack);
    int location = GetShaderLocationAttrib(shader, attribName);
    bruter_push_int(stack, location, NULL, BRUTER_TYPE_ANY);
}

function(raylib_set_shader_value)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    const void *value = bruter_pop_pointer(stack);
    int uniformType = bruter_pop_int(stack);

    SetShaderValue(shader, locIndex, value, uniformType);
}

function(raylib_set_shader_value_v)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    const void *value = bruter_pop_pointer(stack);
    int uniformType = bruter_pop_int(stack);
    int count = bruter_pop_int(stack);

    SetShaderValueV(shader, locIndex, value, uniformType, count);
}

function(raylib_set_shader_value_matrix)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    Matrix mat = matrix_constructor(bruter_pop_pointer(stack));

    SetShaderValueMatrix(shader, locIndex, mat);
}

function(raylib_set_shader_value_texture)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    int locIndex = bruter_pop_int(stack);
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));

    SetShaderValueTexture(shader, locIndex, texture);
}

function(raylib_unload_shader)
{
    Shader shader = shader_constructor(bruter_pop_pointer(stack));
    UnloadShader(shader);
}

function(raylib_get_screen_to_world_ray)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Ray ray = GetScreenToWorldRay(position, camera);
    bruter_push_pointer(stack, ray_to_list(ray), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_screen_to_world_ray_ex)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Ray ray = GetScreenToWorldRayEx(position, camera, width, height);
    bruter_push_pointer(stack, ray_to_list(ray), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_world_to_screen)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Vector2 screenPos = GetWorldToScreen(position, camera);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_world_to_screen_ex)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Vector2 screenPos = GetWorldToScreenEx(position, camera, width, height);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_world_to_screen_2d)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Vector2 screenPos = GetWorldToScreen2D(position, camera);
    bruter_push_pointer(stack, vector2_to_list(screenPos), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_screen_to_world_2d)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Vector2 worldPos = GetScreenToWorld2D(position, camera);
    bruter_push_pointer(stack, vector2_to_list(worldPos), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_camera_matrix)
{
    Camera3D camera = camera3d_constructor(bruter_pop_pointer(stack));
    Matrix matrix = GetCameraMatrix(camera);
    bruter_push_pointer(stack, matrix_to_list(matrix), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_camera_matrix_2d)
{
    Camera2D camera = camera2d_constructor(bruter_pop_pointer(stack));
    Matrix matrix = GetCameraMatrix2D(camera);
    bruter_push_pointer(stack, matrix_to_list(matrix), NULL, BRUTER_TYPE_LIST);
}

// Timing-related functions
function(raylib_set_target_fps)
{
    int fps = bruter_pop_int(stack);
    SetTargetFPS(fps);
}

function(raylib_get_frame_time)
{
    float frameTime = GetFrameTime();
    bruter_push_float(stack, frameTime, NULL, BRUTER_TYPE_FLOAT);
}

function(raylib_get_time)
{
    double time = GetTime();
    bruter_push_float(stack, (float)time, NULL, BRUTER_TYPE_FLOAT);
}

function(raylib_get_fps)
{
    int fps = GetFPS();
    bruter_push_int(stack, fps, NULL, BRUTER_TYPE_ANY);
}

// Custom frame control functions
function(raylib_swap_screen_buffer)
{
    SwapScreenBuffer();
}

function(raylib_poll_input_events)
{
    PollInputEvents();
}

function(raylib_wait_time)
{
    float seconds = bruter_pop_float(stack);
    WaitTime(seconds);
}

// Random values generation functions
function(raylib_set_random_seed)
{
    unsigned int seed = bruter_pop_int(stack);
    SetRandomSeed(seed);
}

function(raylib_get_random_value)
{
    int min = bruter_pop_int(stack);
    int max = bruter_pop_int(stack);
    int value = GetRandomValue(min, max);
    bruter_push_int(stack, value, NULL, BRUTER_TYPE_ANY);
}

function(raylib_load_random_sequence)
{
    unsigned int count = bruter_pop_int(stack);
    int min = bruter_pop_int(stack);
    int max = bruter_pop_int(stack);
    int *sequence = LoadRandomSequence(count, min, max);
    bruter_push_pointer(stack, sequence, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_unload_random_sequence)
{
    int *sequence = (int*)bruter_pop_pointer(stack);
    UnloadRandomSequence(sequence);
}

// Misc. functions
function(raylib_take_screenshot)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    TakeScreenshot(fileName);
}

function(raylib_set_config_flags)
{
    unsigned int flags = bruter_pop_int(stack);
    SetConfigFlags(flags);
}

function(raylib_open_url)
{
    char *url = (char*)bruter_pop_pointer(stack);
    OpenURL(url);
}

// utils functions
function(raylib_trace_log)
{
    printf("raylib_trace_log is not implemented in bruter yet\n");
}

function(raylib_set_trace_log_level)
{
    int logLevel = bruter_pop_int(stack);
    SetTraceLogLevel(logLevel);
}

function(raylib_mem_alloc)
{
    unsigned int size = bruter_pop_int(stack);
    void *ptr = MemAlloc(size);
    bruter_push_pointer(stack, ptr, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_mem_realloc)
{
    void *ptr = bruter_pop_pointer(stack);
    unsigned int size = bruter_pop_int(stack);
    void *newPtr = MemRealloc(ptr, size);
    bruter_push_pointer(stack, newPtr, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_mem_free)
{
    void *ptr = bruter_pop_pointer(stack);
    MemFree(ptr);
}

// custom callbacks, probably not working
function(raylib_set_custom_tracelog_callback)
{
    TraceLogCallback callback = (TraceLogCallback)bruter_pop_pointer(stack);
    SetCustomTraceLogCallback(callback);
}

function(raylib_set_load_file_data_callback)
{
    LoadFileDataCallback callback = (LoadFileDataCallback)bruter_pop_pointer(stack);
    SetLoadFileDataCallback(callback);
}

function(raylib_set_save_file_data_callback)
{
    SaveFileDataCallback callback = (SaveFileDataCallback)bruter_pop_pointer(stack);
    SetSaveFileDataCallback(callback);
}

function(raylib_set_load_file_text_callback)
{
    LoadFileTextCallback callback = (LoadFileTextCallback)bruter_pop_pointer(stack);
    SetLoadFileTextCallback(callback);
}

function(raylib_set_save_file_text_callback)
{
    SaveFileTextCallback callback = (SaveFileTextCallback)bruter_pop_pointer(stack);
    SetSaveFileTextCallback(callback);
}

// Files management functions
function(raylib_load_file_data)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    unsigned int bytesRead = 0;
    void *data = LoadFileData(fileName, &bytesRead);
    BruterList *list = bruter_new(2, true, true);
    bruter_push_pointer(list, data, "data", BRUTER_TYPE_BUFFER);
    bruter_push_int(list, bytesRead, "bytesRead", BRUTER_TYPE_ANY);
    bruter_push_pointer(stack, list, NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_file_data)
{
    void *data = bruter_pop_pointer(stack);
    UnloadFileData(data);
}

function(raylib_save_file_data)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    unsigned int bytesToWrite = bruter_pop_int(stack);
    bool success = SaveFileData(fileName, data, bytesToWrite);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(raylib_export_data_as_code)
{
    char *data = (char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportDataAsCode(data, dataSize, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(raylib_load_file_text)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *text = LoadFileText(fileName);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_unload_file_text)
{
    char *text = (char*)bruter_pop_pointer(stack);
    UnloadFileText(text);
}

function(raylib_save_file_text)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *text = (char*)bruter_pop_pointer(stack);
    bool success = SaveFileText(fileName, text);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// File system functions
function(raylib_file_exists)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool exists = FileExists(fileName);
    bruter_push_int(stack, exists, NULL, BRUTER_TYPE_ANY);
}

function(raylib_directory_exists)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool exists = DirectoryExists(dirPath);
    bruter_push_int(stack, exists, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_file_extension)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *ext = (char*)bruter_pop_pointer(stack);
    bool isExt = IsFileExtension(fileName, ext);
    bruter_push_int(stack, isExt, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_file_length)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    unsigned int length = GetFileLength(fileName);
    bruter_push_int(stack, length, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_file_extension)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    char *ext = GetFileExtension(fileName);
    bruter_push_pointer(stack, ext, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_get_file_name)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    char *fileName = GetFileName(filePath);
    bruter_push_pointer(stack, fileName, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_get_file_name_without_ext)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    char *fileNameWithoutExt = GetFileNameWithoutExt(filePath);
    bruter_push_pointer(stack, fileNameWithoutExt, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_get_directory_path)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    char *dirPath = GetDirectoryPath(filePath);
    bruter_push_pointer(stack, dirPath, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_get_prev_directory_path)
{
    char *filePath = (char*)bruter_pop_pointer(stack);
    char *prevDirPath = GetPreviousDirectoryPath(filePath);
    bruter_push_pointer(stack, prevDirPath, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_get_working_directory)
{
    char *workingDir = GetWorkingDirectory();
    bruter_push_pointer(stack, workingDir, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_get_application_directory)
{
    char *appDir = GetApplicationDirectory();
    bruter_push_pointer(stack, appDir, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_make_directory)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool success = MakeDirectory(dirPath);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(raylib_change_directory)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    bool success = ChangeDirectory(dirPath);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_path_file)
{
    char *path = (char*)bruter_pop_pointer(stack);
    bool isFile = IsPathFile(path);
    bruter_push_int(stack, isFile, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_filename_valid)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool isValid = IsFileNameValid(fileName);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_load_directory_files)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    FilePathList filePathList = LoadDirectoryFiles(dirPath);
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_directory_files_ex)
{
    char *dirPath = (char*)bruter_pop_pointer(stack);
    const char* filter = (const char*)bruter_pop_pointer(stack);
    bool scanSubdirs = bruter_pop_int(stack);
    FilePathList filePathList = LoadDirectoryFilesEx(dirPath, filter, scanSubdirs);
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_directory_files)
{
    FilePathList filePathList = file_path_list_constructor(bruter_pop_pointer(stack));
    UnloadDirectoryFiles(filePathList);
}

function(raylib_is_file_dropped)
{
    bool isDropped = IsFileDropped();
    bruter_push_int(stack, isDropped, NULL, BRUTER_TYPE_ANY);
}

function(raylib_load_dropped_files)
{
    FilePathList filePathList = LoadDroppedFiles();
    bruter_push_pointer(stack, file_path_list_to_list(filePathList), NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_dropped_files)
{
    FilePathList filePathList = file_path_list_constructor(bruter_pop_pointer(stack));
    UnloadDroppedFiles(filePathList);
}

function(raylib_get_file_mod_time)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    long modTime = GetFileModTime(fileName);
    bruter_push_int(stack, (int)modTime, NULL, BRUTER_TYPE_ANY);
}

// Compression/Encoding functionality
function(raylib_compress_data)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *compDataSize = (int*)bruter_pop_pointer(stack);
    void *compressedData = CompressData(data, dataSize, compDataSize);
    bruter_push_pointer(stack, compressedData, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_decompress_data)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *decompDataSize = (int*)bruter_pop_pointer(stack);
    void *decompressedData = DecompressData(data, dataSize, decompDataSize);
    bruter_push_pointer(stack, decompressedData, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_encode_data_base64)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *outputSize = (int*)bruter_pop_pointer(stack);
    char *encodedData = EncodeDataBase64(data, dataSize, outputSize);
    bruter_push_pointer(stack, encodedData, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_decode_data_base64)
{
    char *encodedData = (char*)bruter_pop_pointer(stack);
    int *decodedDataSize = (int*)bruter_pop_pointer(stack);
    void *decodedData = DecodeDataBase64(encodedData, decodedDataSize);
    bruter_push_pointer(stack, decodedData, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_compute_crc32)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    unsigned int crc = ComputeCRC32(data, dataSize);
    bruter_push_int(stack, crc, NULL, BRUTER_TYPE_ANY);
}

function(raylib_compute_md5)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    ComputeMD5(data, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_compute_sha1)
{
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    ComputeSHA1(data, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

// Automation events functionality
function(raylib_load_automation_event_list)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    AutomationEventList eventList = automation_event_list_constructor(fileName);
    bruter_push_pointer(stack, automation_event_list_to_list(eventList), NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_automation_event_list)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    UnloadAutomationEventList(eventList);
}

function(raylib_export_automation_event_list)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportAutomationEventList(eventList, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// needs revision!!!!!
function(raylib_set_automation_event_list)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    SetAutomationEventList(&eventList);
}

function(raylib_set_automation_event_base_frame)
{
    int baseFrame = bruter_pop_int(stack);
    SetAutomationEventBaseFrame(baseFrame);
}

function(raylib_start_automation_event_recording)
{
    StartAutomationEventRecording();
}

function(raylib_stop_automation_event_recording)
{
    StopAutomationEventRecording();
}

function(raylib_play_automation_event)
{
    AutomationEventList eventList = automation_event_list_constructor(bruter_pop_pointer(stack));
    PlayAutomationEventList(eventList);
}

// input-related functions: keyboard
function(raylib_is_key_pressed)
{
    int key = bruter_pop_int(stack);
    bool isPressed = IsKeyPressed(key);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_key_pressed_repeat)
{
    int key = bruter_pop_int(stack);
    bool isPressedRepeat = IsKeyPressedRepeat(key);
    bruter_push_int(stack, isPressedRepeat, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_key_down)
{
    int key = bruter_pop_int(stack);
    bool isDown = IsKeyDown(key);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_key_released)
{
    int key = bruter_pop_int(stack);
    bool isReleased = IsKeyReleased(key);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_key_up)
{
    int key = bruter_pop_int(stack);
    bool isUp = IsKeyUp(key);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_key_pressed)
{
    int key = GetKeyPressed();
    bruter_push_int(stack, key, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_key_pressed_repeat)
{
    int key = GetKeyPressedRepeat();
    bruter_push_int(stack, key, NULL, BRUTER_TYPE_ANY);
}

function(raylin_set_exit_key)
{
    int key = bruter_pop_int(stack);
    SetExitKey(key);
}

// input-related functions: gamepads
function(raylib_is_gamepad_available)
{
    int gamepad = bruter_pop_int(stack);
    bool isAvailable = IsGamepadAvailable(gamepad);
    bruter_push_int(stack, isAvailable, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_gamepad_name)
{
    int gamepad = bruter_pop_int(stack);
    char *name = GetGamepadName(gamepad);
    bruter_push_pointer(stack, name, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_is_gamepad_button_pressed)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isPressed = IsGamepadButtonPressed(gamepad, button);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_gamepad_button_down)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isDown = IsGamepadButtonDown(gamepad, button);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_gamepad_button_released)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isReleased = IsGamepadButtonReleased(gamepad, button);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_gamepad_button_up)
{
    int gamepad = bruter_pop_int(stack);
    int button = bruter_pop_int(stack);
    bool isUp = IsGamepadButtonUp(gamepad, button);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_gamepad_button_pressed)
{
    int gamepad = bruter_pop_int(stack);
    int button = GetGamepadButtonPressed();
    bruter_push_int(stack, button, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_gamepad_axis_count)
{
    int gamepad = bruter_pop_int(stack);
    int axisCount = GetGamepadAxisCount(gamepad);
    bruter_push_int(stack, axisCount, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_gamepad_axis_movement)
{
    int gamepad = bruter_pop_int(stack);
    int axis = bruter_pop_int(stack);
    float movement = GetGamepadAxisMovement(gamepad, axis);
    bruter_push_float(stack, movement, NULL, BRUTER_TYPE_FLOAT);
}

function(raylib_set_gamepad_mappings)
{
    char *mapping = (char*)bruter_pop_pointer(stack);
    bool success = SetGamepadMapping(mapping);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(raylib_set_gamepad_vibration)
{
    int gamepad = bruter_pop_int(stack);
    float leftVibration = bruter_pop_float(stack);
    float rightVibration = bruter_pop_float(stack);
    float duration = bruter_pop_float(stack);
    SetGamepadVibration(gamepad, leftVibration, rightVibration, duration);
}

// input-related functions: mouse
function(raylib_is_mouse_button_pressed)
{
    int button = bruter_pop_int(stack);
    bool isPressed = IsMouseButtonPressed(button);
    bruter_push_int(stack, isPressed, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_mouse_button_down)
{
    int button = bruter_pop_int(stack);
    bool isDown = IsMouseButtonDown(button);
    bruter_push_int(stack, isDown, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_mouse_button_released)
{
    int button = bruter_pop_int(stack);
    bool isReleased = IsMouseButtonReleased(button);
    bruter_push_int(stack, isReleased, NULL, BRUTER_TYPE_ANY);
}

function(raylib_is_mouse_button_up)
{
    int button = bruter_pop_int(stack);
    bool isUp = IsMouseButtonUp(button);
    bruter_push_int(stack, isUp, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_mouse_x)
{
    int x = GetMouseX();
    bruter_push_int(stack, x, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_mouse_y)
{
    int y = GetMouseY();
    bruter_push_int(stack, y, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_mouse_position)
{
    Vector2 position = GetMousePosition();
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_mouse_delta)
{
    Vector2 delta = GetMouseDelta();
    bruter_push_pointer(stack, vector2_to_list(delta), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_mouse_position)
{
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    SetMousePosition(x, y);
}

function(raylib_set_mouse_offset)
{
    int offsetX = bruter_pop_int(stack);
    int offsetY = bruter_pop_int(stack);
    SetMouseOffset(offsetX, offsetY);
}

function(raylib_set_mouse_scale)
{
    float scaleX = bruter_pop_float(stack);
    float scaleY = bruter_pop_float(stack);
    SetMouseScale(scaleX, scaleY);
}

function(raylib_get_mouse_wheel_move)
{
    float wheelMove = GetMouseWheelMove();
    bruter_push_float(stack, wheelMove, NULL, BRUTER_TYPE_FLOAT);
}

function(raylib_get_mouse_wheel_move_v)
{
    Vector2 wheelMove = GetMouseWheelMoveV();
    bruter_push_pointer(stack, vector2_to_list(wheelMove), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_mouse_cursor)
{
    int cursor = bruter_pop_int(stack);
    SetMouseCursor(cursor);
}

// input-related functions: touch

function(raylib_get_touch_x)
{
    int touchX = GetTouchX();
    bruter_push_int(stack, touchX, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_touch_y)
{
    int touchY = GetTouchY();
    bruter_push_int(stack, touchY, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_touch_position)
{
    int index = bruter_pop_int(stack);
    Vector2 position = GetTouchPosition(index);
    bruter_push_pointer(stack, vector2_to_list(position), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_touch_point_id)
{
    int index = bruter_pop_int(stack);
    int id = GetTouchPointId(index);
    bruter_push_int(stack, id, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_touch_point_count)
{
    int count = GetTouchPointCount();
    bruter_push_int(stack, count, NULL, BRUTER_TYPE_ANY);
}

// Gestures and Touch Handling functions
function(raylib_set_gestures_enabled)
{
    unsigned int gestureFlags = bruter_pop_int(stack);
    SetGesturesEnabled(gestureFlags);
}

function(raylib_is_gesture_detected)
{
    int gesture = bruter_pop_int(stack);
    bool detected = IsGestureDetected(gesture);
    bruter_push_int(stack, detected, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_gesture_detected)
{
    int gesture = GetGestureDetected();
    bruter_push_int(stack, gesture, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_gesture_hold_duration)
{
    float duration = GetGestureHoldDuration();
    bruter_push_float(stack, duration, NULL, BRUTER_TYPE_FLOAT);
}

function(raylib_get_gesture_drag_vector)
{
    Vector2 dragVector = GetGestureDragVector();
    bruter_push_pointer(stack, vector2_to_list(dragVector), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_gesture_drag_angle)
{
    float angle = GetGestureDragAngle();
    bruter_push_float(stack, angle, NULL, BRUTER_TYPE_FLOAT);
}

function(raylib_get_gesture_pinch_vector)
{
    Vector2 pinchVector = GetGesturePinchVector();
    bruter_push_pointer(stack, vector2_to_list(pinchVector), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_gesture_pinch_angle)
{
    float angle = GetGesturePinchAngle();
    bruter_push_float(stack, angle, NULL, BRUTER_TYPE_FLOAT);
}

// Camera system functions
function(raylib_update_camera)
{
    Camera3D *camera = (Camera3D*)bruter_pop_pointer(stack);
    int mode = bruter_pop_int(stack);
    UpdateCamera(camera, mode);
}

function(raylib_update_camera_pro)
{
    Camera3D *camera = (Camera3D*)bruter_pop_pointer(stack);
    Vector3 move = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotation = vector3_constructor(bruter_pop_pointer(stack));
    float zoom = bruter_pop_float(stack);
    UpdateCameraPro(camera, move, rotation, zoom);
}

// basic shapes drawing functions
function(raylib_set_shapes_texture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle source = rectangle_constructor(bruter_pop_pointer(stack));
    SetShapesTexture(texture, source);
}

function(raylib_get_shapes_texture)
{
    Texture2D texture = GetShapesTexture();
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_shapes_texture_rectangle)
{
    Rectangle source = GetShapesTextureRectangle();
    bruter_push_pointer(stack, rectangle_to_list(source), NULL, BRUTER_TYPE_LIST);
}

// basic shapes drawing functions
function(raylib_draw_pixel)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPixel(posX, posY, color);
}

function(raylib_draw_pixel_v)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPixelV(position, color);
}

function(raylib_draw_line)
{
    int startX = bruter_pop_int(stack);
    int startY = bruter_pop_int(stack);
    int endX = bruter_pop_int(stack);
    int endY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLine(startX, startY, endX, endY, color);
}

function(raylib_draw_line_v)
{
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineV(start, end, color);
}

function(raylib_draw_line_ex)
{
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineEx(start, end, thick, color);
}

function(raylib_draw_line_strip)
{
    BruterList *pointsList = bruter_pop_list(stack);
    Vector2 *points = (Vector2*)bruter_list_to_pointer(pointsList);
    int pointCount = bruter_list_length(pointsList);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineStrip(points, pointCount, color);
}

function(raylib_draw_line_bezier)
{
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLineBezier(start, end, thick, color);
}

function(raylib_draw_circle)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircle(centerX, centerY, radius, color);
}

function(raylib_draw_circle_sector)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    float startAngle = bruter_pop_float(stack);
    float endAngle = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
}

function(raylib_draw_circle_sector_lines)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    float startAngle = bruter_pop_float(stack);
    float endAngle = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
}

function(raylib_draw_circle_gradient)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    Color innerColor = color_from_int(bruter_pop_int(stack));
    Color outerColor = color_from_int(bruter_pop_int(stack));
    DrawCircleGradient(centerX, centerY, radius, innerColor, outerColor);
}

function(raylib_draw_circle_v)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleV(center, radius, color);
}

function(raylib_draw_circle_lines)
{
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleLines(centerX, centerY, radius, color);
}

function(raylib_draw_circle_lines_v)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircleLinesV(center, radius, color);
}

function(raylib_draw_rectangle)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangle(posX, posY, width, height, color);
}

function(raylib_draw_rectangle_v)
{
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleV(position, size, color);
}

function(raylib_draw_rectangle_rec)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRec(rec, color);
}

function(raylib_draw_rectangle_pro)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectanglePro(rec, origin, rotation, color);
}

function(raylib_draw_rectangle_gradient_v)
{
    int posx = bruter_pop_int(stack);
    int posy = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color top = color_from_int(bruter_pop_int(stack));
    Color bottom = color_from_int(bruter_pop_int(stack));
    DrawRectangleGradientV(posx, posy, width, height, top, bottom);
}

function(raylib_draw_rectangle_gradient_h)
{
    int posx = bruter_pop_int(stack);
    int posy = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color left = color_from_int(bruter_pop_int(stack));
    Color right = color_from_int(bruter_pop_int(stack));
    DrawRectangleGradientH(posx, posy, width, height, left, right);
}

function(raylib_draw_rectangle_gradient_ex)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    Color color3 = color_from_int(bruter_pop_int(stack));
    Color color4 = color_from_int(bruter_pop_int(stack));
    DrawRectangleGradientEx(rec, color1, color2, color3, color4);
}

function(raylib_draw_rectangle_lines)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleLines(posX, posY, width, height, color);
}

function(raylib_draw_rectangle_lines_ex)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleLinesEx(rec, thick, color);
}

function(raylib_draw_rectangle_rounded)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRounded(rec, roundness, segments, color);
}

function(raylib_draw_rectangle_rounded_lines)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRoundedLines(rec, roundness, segments, color);
}

function(raylib_draw_rectangle_rounded_lines_ex)
{
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    float roundness = bruter_pop_float(stack);
    int segments = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRectangleRoundedLinesEx(rec, roundness, segments, thick, color);
}

function(raylib_draw_triangle)
{
    Vector2 v1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangle(v1, v2, v3, color);
}

function(raylib_draw_triangle_lines)
{
    Vector2 v1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 v3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleLines(v1, v2, v3, color);
}

function(raylib_draw_triangle_fan)
{
    BruterList *pointsList = bruter_pop_list(stack);
    Vector2 *points = (Vector2*)bruter_list_to_pointer(pointsList);
    int pointCount = bruter_list_length(pointsList);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleFan(points, pointCount, color);
}

function(raylib_draw_triangle_strip)
{
    BruterList *pointsList = bruter_pop_list(stack);
    Vector2 *points = (Vector2*)bruter_list_to_pointer(pointsList);
    int pointCount = bruter_list_length(pointsList);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleStrip(points, pointCount, color);
}

function(raylib_draw_poly)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPoly(center, sides, radius, rotation, color);
}

function(raylib_draw_poly_lines)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    float rotation = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPolyLines(center, sides, radius, rotation, color);
}

function(raylib_draw_poly_lines_ex)
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
function(raylib_draw_spline_linear)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineLinear(points, pointCount, thick, color);
}

function(raylib_draw_spline_basis)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBasis(points, pointCount, thick, color);
}

function(raylib_draw_spline_catmull_rom)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineCatmullRom(points, pointCount, thick, color);
}

function(raylib_draw_spline_bezierQuadratic)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBezierQuadratic(points, pointCount, thick, color);
}

function(raylib_draw_spline_bezierCubic)
{
    Vector2 *points = (Vector2*)bruter_pop_pointer(stack);
    int pointCount = bruter_pop_int(stack);
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineBezierCubic(points, pointCount, thick, color);
}

function(raylib_draw_spline_segment_linear)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentLinear(p1, p2, thick, color);
}

function(raylib_draw_spline_segment_basis)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
}

function(raylib_draw_spline_segment_catmull_rom)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
}

function(raylib_draw_spline_segment_bezierQuadratic)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSplineSegmentBezierQuadratic(p1, p2, p3, thick, color);
}

function(raylib_draw_spline_segment_bezierCubic)
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
function(raylib_get_spline_point_linear)
{
    Vector2 startPos = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 endPos = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointLinear(startPos, endPos, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_spline_point_basis)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointBasis(p1, p2, p3, p4, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_spline_point_catmull_rom)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p4 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointCatmullRom(p1, p2, p3, p4, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_spline_point_bezierQuad)
{
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    float t = bruter_pop_float(stack);
    Vector2 point = GetSplinePointBezierQuad(p1, p2, p3, t);
    bruter_push_pointer(stack, vector2_to_list(point), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_spline_point_bezierCubic)
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
function(raylib_check_collision_recs)
{
    Rectangle rec1 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle rec2 = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionRecs(rec1, rec2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_circles)
{
    Vector2 center1 = vector2_constructor(bruter_pop_pointer(stack));
    float radius1 = bruter_pop_float(stack);
    Vector2 center2 = vector2_constructor(bruter_pop_pointer(stack));
    float radius2 = bruter_pop_float(stack);
    bool collision = CheckCollisionCircles(center1, radius1, center2, radius2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_circle_rec)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionCircleRec(center, radius, rec);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_circle_line)
{
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionCircleLine(center, radius, start, end);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_point_rec)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionPointRec(point, rec);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_point_circle)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    bool collision = CheckCollisionPointCircle(point, center, radius);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_point_triangle)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionPointTriangle(point, p1, p2, p3);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_point_line)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    bool collision = CheckCollisionPointLine(point, start, end, threshold);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_point_poly)
{
    Vector2 point = vector2_constructor(bruter_pop_pointer(stack));
    BruterList *pointsList = bruter_pop_list(stack);
    Vector2 *points = (Vector2*)bruter_list_to_pointer(pointsList);
    int pointCount = bruter_list_length(pointsList);
    bool collision = CheckCollisionPointPoly(point, points, pointCount);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_lines)
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

function(raylib_get_collision_rec)
{
    Rectangle rec1 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle rec2 = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle collisionRec = GetCollisionRec(rec1, rec2);
    bruter_push_pointer(stack, rectangle_to_list(collisionRec), NULL, BRUTER_TYPE_LIST);
}

// image loading functions
function(raylib_load_image)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Image image = LoadImage(fileName);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_image_raw)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int format = bruter_pop_int(stack);
    int headerSize = bruter_pop_int(stack);
    Image image = LoadImageRaw(fileName, width, height, format, headerSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_image_anim)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *framesCount = (int*)bruter_pop_pointer(stack);
    Image *images = LoadImageAnimation(fileName, framesCount);
    bruter_push_pointer(stack, images, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_load_image_anim_from_memory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    char *fileData = (char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int *framesCount = (int*)bruter_pop_pointer(stack);
    Image *images = LoadImageAnimationFromMemory(fileType, fileData, dataSize, framesCount);
    bruter_push_pointer(stack, images, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_load_image_from_memory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    char *fileData = (char*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Image image = LoadImageFromMemory(fileType, fileData, dataSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_image_from_texture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Image image = LoadImageFromTexture(texture);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_image_from_screen)
{
    Image image = LoadImageFromScreen();
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_image_valid)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    bool isValid = IsImageValid(image);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_image)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    UnloadImage(image);
}

function(raylib_export_image)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportImage(image, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

function(raylib_export_image_to_memory)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileType = (char*)bruter_pop_pointer(stack);
    int *dataSize = (int*)bruter_pop_pointer(stack);
    unsigned char *data = ExportImageToMemory(image, fileType, dataSize);
    bruter_push_pointer(stack, data, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_export_image_as_code)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    bool success = ExportImageAsCode(image, fileName);
    bruter_push_int(stack, success, NULL, BRUTER_TYPE_ANY);
}

// image generation functions
function(raylib_gen_image_color)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    Image image = GenImageColor(width, height, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_gradient_linear)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int direction = bruter_pop_int(stack);
    Color start = color_from_int(bruter_pop_int(stack));
    Color end = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientLinear(width, height, direction, start, end);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_gradient_radial)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float density = bruter_pop_float(stack);
    Color inner = color_from_int(bruter_pop_int(stack));
    Color outer = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientRadial(width, height, density, inner, outer);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_gradient_square)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float density = bruter_pop_float(stack);
    Color inner = color_from_int(bruter_pop_int(stack));
    Color outer = color_from_int(bruter_pop_int(stack));
    Image image = GenImageGradientSquare(width, height, density, inner, outer);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_checked)
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

function(raylib_gen_image_white_noise)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    float factor = bruter_pop_float(stack);
    Image image = GenImageWhiteNoise(width, height, factor);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_perlin_noise)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int offsetX = bruter_pop_int(stack);
    int offsetY = bruter_pop_int(stack);
    float scale = bruter_pop_float(stack);
    Image image = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_cellular)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int tileSize = bruter_pop_int(stack);
    Image image = GenImageCellular(width, height, tileSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_text)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    char *text = (char*)bruter_pop_pointer(stack);
    Image image = GenImageText(width, height, text);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

// image manipulation functions

function(raylib_image_copy)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image copiedImage = ImageCopy(image);
    bruter_push_pointer(stack, image_to_list(copiedImage), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_from_image)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Image subImage = ImageFromImage(image, rec);
    bruter_push_pointer(stack, image_to_list(subImage), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_from_channel)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int channel = bruter_pop_int(stack);
    Image channelImage = ImageFromChannel(image, channel);
    bruter_push_pointer(stack, image_to_list(channelImage), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_text)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    Image image = ImageText(text, fontSize, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_text_ex)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    Image image = ImageTextEx(font, text, fontSize, spacing, tint);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_format)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newFormat = bruter_pop_int(stack);
    ImageFormat(&image, newFormat);
}

function(raylib_image_to_pot)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color fill = color_from_int(bruter_pop_int(stack));
    ImageToPOT(&image, fill);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_crop)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle crop = rectangle_constructor(bruter_pop_pointer(stack));
    ImageCrop(&image, crop);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_alpha_crop)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    ImageAlphaCrop(&image, threshold);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_alpha_clear)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    float threshold = bruter_pop_float(stack);
    ImageAlphaClear(&image, color, threshold);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_alpha_mask)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image mask = image_constructor(bruter_pop_pointer(stack));
    ImageAlphaMask(&image, mask);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_alpha_premultiply)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageAlphaPremultiply(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_blur_glaussian)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int blurSize = bruter_pop_int(stack);
    ImageBlurGaussian(&image, blurSize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_kernel_convolution)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float *kernel = (float*)bruter_pop_pointer(stack);
    int kernelsize = bruter_pop_int(stack);
    ImageKernelConvolution(&image, kernel, kernelsize);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_resize)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newWidth = bruter_pop_int(stack);
    int newHeight = bruter_pop_int(stack);
    ImageResize(&image, newWidth, newHeight);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_resize_nn)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int newWidth = bruter_pop_int(stack);
    int newHeight = bruter_pop_int(stack);
    ImageResizeNN(&image, newWidth, newHeight);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_resize_canvas)
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

function(raylib_image_mipmaps)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageMipmaps(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_dither)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int rBpp = bruter_pop_int(stack);
    int gBpp = bruter_pop_int(stack);
    int bBpp = bruter_pop_int(stack);
    int aBpp = bruter_pop_int(stack);
    ImageDither(&image, rBpp, gBpp, bBpp, aBpp);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_flip_vertical)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageFlipVertical(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_flip_horizontal)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageFlipHorizontal(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_rotate)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float degrees = bruter_pop_float(stack);
    ImageRotate(&image, degrees);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_rotate_cw)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageRotateCW(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_rotate_ccw)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageRotateCCW(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_color_tint)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageColorTint(&image, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_color_invert)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageColorInvert(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_color_grayscale)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    ImageColorGrayscale(&image);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_color_contrast)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float contrast = bruter_pop_float(stack);
    ImageColorContrast(&image, contrast);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_color_brightness)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int brightness = bruter_pop_int(stack);
    ImageColorBrightness(&image, brightness);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_color_replace)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    Color replace = color_from_int(bruter_pop_int(stack));
    ImageColorReplace(&image, color, replace);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_image_colors)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color *colors = LoadImageColors(image);
    int colorCount = image.width * image.height;
    bruter_push_pointer(stack, colors, NULL, BRUTER_TYPE_BUFFER);
    bruter_push_int(stack, colorCount, NULL, BRUTER_TYPE_ANY);
}

function(raylib_load_image_palette)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int maxPaletteSize = bruter_pop_int(stack);
    int *colorCount = (int*)bruter_pop_pointer(stack);
    Color *palette = LoadImagePalette(image, maxPaletteSize, colorCount);
    int paletteSize = GetImagePaletteSize(image, maxPaletteSize);
    bruter_push_pointer(stack, palette, NULL, BRUTER_TYPE_BUFFER);
    bruter_push_int(stack, paletteSize, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_image_colors)
{
    Color *colors = (Color*)bruter_pop_pointer(stack);
    bruter_free(colors);
}

function(raylib_unload_image_palette)
{
    Color *palette = (Color*)bruter_pop_pointer(stack);
    bruter_free(palette);
}

function(raylib_get_image_alpha_border)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    float threshold = bruter_pop_float(stack);
    Rectangle rec = GetImageAlphaBorder(image, threshold);
    bruter_push_pointer(stack, rectangle_to_list(rec), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_image_color)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int x = bruter_pop_int(stack);
    int y = bruter_pop_int(stack);
    Color color = GetImageColor(image, x, y);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

// image drawing functions
function(raylib_image_clear_background)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageClearBackground(&image, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_pixel)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawPixel(&image, posX, posY, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_pixel_v)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 pos = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawPixelV(&image, pos, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_line)
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

function(raylib_image_draw_line_v)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawLineV(&image, start, end, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_line_ex)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 start = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 end = vector2_constructor(bruter_pop_pointer(stack));
    float thick = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawLineEx(&image, start, end, thick, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_circle)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircle(&image, centerX, centerY, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_circle_v)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircleV(&image, center, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_circle_lines)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int centerX = bruter_pop_int(stack);
    int centerY = bruter_pop_int(stack);
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircleLines(&image, centerX, centerY, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_circle_lines_v)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 center = vector2_constructor(bruter_pop_pointer(stack));
    int radius = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawCircleLinesV(&image, center, radius, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_rectangle)
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

function(raylib_image_draw_rectangle_v)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangleV(&image, position, size, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_rectangle_rec)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangleRec(&image, rec, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_rectangle_lines)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    int thick = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawRectangleLines(&image, rec, thick, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_triangle)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangle(&image, p1, p2, p3, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_triangle_ex)
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

function(raylib_image_draw_triangle_lines)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Vector2 p1 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p2 = vector2_constructor(bruter_pop_pointer(stack));
    Vector2 p3 = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleLines(&image, p1, p2, p3, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_triangle_fan)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    BruterList *pointsList = bruter_pop_list(stack);
    Vector2 *points = (Vector2*)bruter_list_to_pointer(pointsList);
    int pointCount = bruter_list_length(pointsList);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleFan(&image, points, pointCount, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_triangle_strip)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    BruterList *pointsList = bruter_pop_list(stack);
    Vector2 *points = (Vector2*)bruter_list_to_pointer(pointsList);
    int pointCount = bruter_list_length(pointsList);
    Color color = color_from_int(bruter_pop_int(stack));
    ImageDrawTriangleStrip(&image, points, pointCount, color);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Image src = image_constructor(bruter_pop_pointer(stack));
    Rectangle srcRec = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle destRec = rectangle_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    ImageDraw(&image, src, srcRec, destRec, tint);
    bruter_push_pointer(stack, image_to_list(image), NULL, BRUTER_TYPE_LIST);
}

function(raylib_image_draw_text)
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

function(raylib_image_draw_text_ex)
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

function(raylib_load_texture)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Texture2D texture = LoadTexture(fileName);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_texture_from_image)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Texture2D texture = LoadTextureFromImage(image);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_texture_cubemap)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    int layout = bruter_pop_int(stack); // Assuming layout is an int representing the cubemap layout
    TextureCubemap texture = LoadTextureCubemap(image, layout);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}


function(raylib_load_render_rexture)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    RenderTexture2D renderTexture = LoadRenderTexture(width, height);
    bruter_push_pointer(stack, render_texture_to_list(renderTexture), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_texture_valid)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    bool isValid = IsTextureValid(texture);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_texture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    UnloadTexture(texture);
}

function(raylib_is_render_texture_valid)
{
    RenderTexture2D renderTexture = render_texture_constructor(bruter_pop_pointer(stack));
    bool isValid = IsRenderTextureValid(renderTexture);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_render_texture)
{
    RenderTexture2D renderTexture = render_texture_constructor(bruter_pop_pointer(stack));
    UnloadRenderTexture(renderTexture);
}

function(raylib_update_texture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    unsigned char *pixels = (unsigned char*)bruter_pop_pointer(stack);
    UpdateTexture(texture, pixels);
}

function(raylib_update_texture_rec)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle rec = rectangle_constructor(bruter_pop_pointer(stack));
    unsigned char *pixels = (unsigned char*)bruter_pop_pointer(stack);
    UpdateTextureRec(texture, rec, pixels);
}

// texture configuration functions
function(raylib_gen_texture_mipmaps)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    GenTextureMipmaps(&texture);
    bruter_push_pointer(stack, texture_to_list(texture), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_texture_filter)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int filter = bruter_pop_int(stack);
    SetTextureFilter(texture, filter);
}

function(raylib_set_texture_wrap)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int wrap = bruter_pop_int(stack);
    SetTextureWrap(texture, wrap);
}

// texture drawing functions
function(raylib_draw_texture)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTexture(texture, posX, posY, tint);
}

function(raylib_draw_texture_v)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureV(texture, position, tint);
}

function(raylib_draw_texture_ex)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureEx(texture, position, rotation, scale, tint);
}

function(raylib_draw_texture_rec)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextureRec(texture, sourceRec, position, tint);
}

function(raylib_draw_texture_pro)
{
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Rectangle destRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector2 origin = vector2_constructor(bruter_pop_pointer(stack));
    float rotation = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
}

function(raylib_draw_texture_npatch)
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

function(raylib_color_is_equal)
{
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    bool isEqual = ColorIsEqual(color1, color2);
    bruter_push_int(stack, isEqual, NULL, BRUTER_TYPE_ANY);
}

function(raylib_fade_color)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float alpha = bruter_pop_float(stack);
    Color fadedColor = Fade(color, alpha);
    bruter_push_int(stack, color_to_int(fadedColor), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_to_int)
{
    Color color = color_from_int(bruter_pop_int(stack));
    int colorInt = ColorToInt(color);
    bruter_push_int(stack, colorInt, NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_normalize)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Vector4 normalizedColor = ColorNormalize(color);
    bruter_push_pointer(stack, vector4_to_list(normalizedColor), NULL, BRUTER_TYPE_LIST);
}

function(raylib_color_from_normalized)
{
    Vector4 normalizedColor = vector4_constructor(bruter_pop_pointer(stack));
    Color color = ColorFromNormalized(normalizedColor);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_to_hsv)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Vector3 hsv = ColorToHSV(color);
    bruter_push_pointer(stack, vector3_to_list(hsv), NULL, BRUTER_TYPE_LIST);
}

function(raylib_color_from_hsv)
{
    float hue = bruter_pop_float(stack);
    float saturation = bruter_pop_float(stack);
    float value = bruter_pop_float(stack);
    Color color = ColorFromHSV(hue, saturation, value);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_tint)
{
    Color color = color_from_int(bruter_pop_int(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    Color tintedColor = ColorTint(color, tint);
    bruter_push_int(stack, color_to_int(tintedColor), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_brightness)
{
    Color color = color_from_int(bruter_pop_int(stack));
    int brightness = bruter_pop_int(stack);
    Color brightenedColor = ColorBrightness(color, brightness);
    bruter_push_int(stack, color_to_int(brightenedColor), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_contrast)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float contrast = bruter_pop_float(stack);
    Color contrastedColor = ColorContrast(color, contrast);
    bruter_push_int(stack, color_to_int(contrastedColor), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_alpha)
{
    Color color = color_from_int(bruter_pop_int(stack));
    float alpha = bruter_pop_float(stack);
    Color alphaColor = ColorAlpha(color, alpha);
    bruter_push_int(stack, color_to_int(alphaColor), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_alpha_blend)
{
    Color dst = color_from_int(bruter_pop_int(stack));
    Color src = color_from_int(bruter_pop_int(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    Color blendedColor = ColorAlphaBlend(dst, src, tint);
    bruter_push_int(stack, color_to_int(blendedColor), NULL, BRUTER_TYPE_ANY);
}

function(raylib_color_lerp)
{
    Color color1 = color_from_int(bruter_pop_int(stack));
    Color color2 = color_from_int(bruter_pop_int(stack));
    float amount = bruter_pop_float(stack);
    Color lerpedColor = ColorLerp(color1, color2, amount);
    bruter_push_int(stack, color_to_int(lerpedColor), NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_color)
{
    int hexColor = bruter_pop_int(stack);
    Color color = GetColor(hexColor);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_pixel_color)
{
    void* data = bruter_pop_pointer(stack);
    int format = bruter_pop_int(stack);
    Color color = GetPixelColor(data, format);
    bruter_push_int(stack, color_to_int(color), NULL, BRUTER_TYPE_ANY);
}

function(raylib_set_pixel_color)
{
    void *data = bruter_pop_pointer(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    int format = bruter_pop_int(stack);
    SetPixelColor(data, color, format);
}

function(raylib_get_pixel_data_size)
{
    int width = bruter_pop_int(stack);
    int height = bruter_pop_int(stack);
    int format = bruter_pop_int(stack);
    int size = GetPixelDataSize(width, height, format);
    bruter_push_int(stack, size, NULL, BRUTER_TYPE_ANY);
}

// font loading/unloading functions

function(raylib_get_font_default)
{
    Font font = GetFontDefault();
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_font)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Font font = LoadFont(fileName);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_font_ex)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    int *fontChars = (int*)bruter_pop_pointer(stack);
    int charsCount = bruter_pop_int(stack);
    Font font = LoadFontEx(fileName, fontSize, fontChars, charsCount);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_font_from_image)
{
    Image image = image_constructor(bruter_pop_pointer(stack));
    Color key = color_from_int(bruter_pop_int(stack));
    int firstChar = bruter_pop_int(stack);
    Font font = LoadFontFromImage(image, key, firstChar);
    bruter_push_pointer(stack, font_to_list(font), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_font_from_memory)
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

function(raylib_is_font_valid)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    bool isValid = IsFontValid(font);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_load_font_data)
{
    void *fileData = (void*)bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    int *codepoints = (int*)bruter_pop_pointer(stack);
    int codepointCount = bruter_pop_int(stack);
    int type = bruter_pop_int(stack); // Assuming type is an int representing the font type
    GlyphInfo *fontData = LoadFontData(fileData, dataSize, fontSize, codepoints, codepointCount, type);
    bruter_push_pointer(stack, font_data_to_list(fontData), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_image_font_atlas)
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

function(raylib_unload_font_data)
{
    GlyphInfo *fontData = (GlyphInfo*)bruter_pop_pointer(stack);
    int glyphCount = bruter_pop_int(stack);
    UnloadFontData(fontData, glyphCount);
}

function(raylib_unload_font)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    UnloadFont(font);
}

function(raylib_export_font_as_code)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportFontAsCode(font, fileName);
}

// text drawing functions
function(raylib_draw_FPS)
{
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    DrawFPS(posX, posY);
}

function(raylib_draw_text)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int posX = bruter_pop_int(stack);
    int posY = bruter_pop_int(stack);
    int fontSize = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawText(text, posX, posY, fontSize, color);
}

function(raylib_draw_text_ex)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextEx(font, text, position, fontSize, spacing, tint);
}

function(raylib_draw_text_pro)
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

function(raylib_draw_text_codepoint)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawTextCodepoint(font, codepoint, position, fontSize, tint);
}

function(raylib_draw_text_codepoints)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    BruterList *codepointsList = bruter_pop_list(stack);
    Vector2 position = vector2_constructor(bruter_pop_pointer(stack));
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    int *codepoints = (int*)bruter_list_to_pointer(codepointsList);
    int codepointCount = bruter_list_length(codepointsList);
    DrawTextCodepoints(font, codepoints, codepointCount, position, fontSize, spacing, tint);
}

// text font info functions
function(raylib_set_text_line_spacing)
{
    float spacing = bruter_pop_float(stack);
    SetTextLineSpacing(spacing);
}

function(raylib_measure_text)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int fontSize = bruter_pop_int(stack);
    int size = MeasureText(text, fontSize);
    bruter_push_int(stack, size, NULL, BRUTER_TYPE_ANY);
}

function(raylib_measure_text_ex)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    char *text = (char*)bruter_pop_pointer(stack);
    float fontSize = bruter_pop_float(stack);
    float spacing = bruter_pop_float(stack);
    Vector2 size = MeasureTextEx(font, text, fontSize, spacing);
    bruter_push_pointer(stack, vector2_to_list(size), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_glyph_index)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    int glyphIndex = GetGlyphIndex(font, codepoint);
    bruter_push_int(stack, glyphIndex, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_glyph_info)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    GlyphInfo glyphInfo = GetGlyphInfo(font, codepoint);
    bruter_push_pointer(stack, glyph_info_to_list(glyphInfo), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_glyph_atlas_rec)
{
    Font font = font_constructor(bruter_pop_pointer(stack));
    int codepoint = bruter_pop_int(stack);
    Rectangle rec = GetGlyphAtlasRec(font, codepoint);
    bruter_push_pointer(stack, rectangle_to_list(rec), NULL, BRUTER_TYPE_LIST);
}

// text string managment functions
function(raylib_text_copy)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *src = (char*)bruter_pop_pointer(stack);
    char *copiedText = TextCopy(text, src);
    bruter_push_pointer(stack, copiedText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_is_equal)
{
    char *text1 = (char*)bruter_pop_pointer(stack);
    char *text2 = (char*)bruter_pop_pointer(stack);
    bool isEqual = TextIsEqual(text1, text2);
    bruter_push_int(stack, isEqual, NULL, BRUTER_TYPE_ANY);
}

function(raylib_text_length)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int length = TextLength(text);
    bruter_push_int(stack, length, NULL, BRUTER_TYPE_ANY);
}

function(raylib_text_format)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *formattedText = TextFormat(text);
    bruter_push_pointer(stack, formattedText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_subtext)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    int length = bruter_pop_int(stack);
    char *subText = TextSubtext(text, position, length);
    bruter_push_pointer(stack, subText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_replace)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *find = (char*)bruter_pop_pointer(stack);
    char *replace = (char*)bruter_pop_pointer(stack);
    char *replacedText = TextReplace(text, find, replace);
    bruter_push_pointer(stack, replacedText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_insert)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *insert = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    char *insertedText = TextInsert(text, insert, position);
    bruter_push_pointer(stack, insertedText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_join)
{
    const char **textList = bruter_pop_list(stack);
    int count = bruter_pop_int(stack);
    char *delimiter = (char*)bruter_pop_pointer(stack);
    char *joinedText = TextJoin(textList, count, delimiter);
    bruter_push_pointer(stack, joinedText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_split)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char delimiter = bruter_pop_int(stack);
    int *count = (int*)bruter_pop_pointer(stack);
    BruterList *splitList = TextSplit(text, delimiter, count);
    bruter_push_pointer(stack, splitList, NULL, BRUTER_TYPE_LIST);
}

function(raylib_text_append)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *appendText = (char*)bruter_pop_pointer(stack);
    int position = bruter_pop_int(stack);
    TextAppend(text, appendText, position);
    bruter_push_pointer(stack, text, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_find_index)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *find = (char*)bruter_pop_pointer(stack);
    int index = TextFindIndex(text, find);
    bruter_push_int(stack, index, NULL, BRUTER_TYPE_ANY);
}

function(raylib_text_to_upper)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *upperText = TextToUpper(text);
    bruter_push_pointer(stack, upperText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_to_lower)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *lowerText = TextToLower(text);
    bruter_push_pointer(stack, lowerText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_to_pascal)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *pascalText = TextToPascal(text);
    bruter_push_pointer(stack, pascalText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_to_snake)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *snakeText = TextToSnake(text);
    bruter_push_pointer(stack, snakeText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_to_camel)
{
    char *text = (char*)bruter_pop_pointer(stack);
    char *camelText = TextToCamel(text);
    bruter_push_pointer(stack, camelText, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_text_to_integer)
{
    char *text = (char*)bruter_pop_pointer(stack);
    int value = TextToInteger(text);
    bruter_push_int(stack, value, NULL, BRUTER_TYPE_ANY);
}

function(raylib_text_to_float)
{
    char *text = (char*)bruter_pop_pointer(stack);
    float value = TextToFloat(text);
    bruter_push_float(stack, value, NULL, BRUTER_TYPE_ANY);
}

// basic geometric 3d shapes drawing functions

function(raylib_draw_line_3d)
{
    Vector3 start = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 end = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawLine3D(start, end, color);
}

function(raylib_draw_point_3d)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPoint3D(position, color);
}

function(raylib_draw_circle_3d)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
}

function(raylib_draw_triangle_3d)
{
    Vector3 p1 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p2 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p3 = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangle3D(p1, p2, p3, color);
}

function(raylib_draw_triangle_strip_3d)
{
    BruterList *pointsList = bruter_pop_list(stack);
    Vector3 *points = (Vector3*)bruter_list_to_pointer(pointsList);
    int pointCount = bruter_list_length(pointsList);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawTriangleStrip3D(points, pointCount, color);
}

function(raylib_draw_cube)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCube(position, width, height, length, color);
}

function(raylib_draw_cube_v)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 size = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCubeV(position, size, color);
}

function(raylib_draw_cube_wires)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCubeWires(position, width, height, length, color);
}

function(raylib_draw_cube_wires_v)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 size = vector3_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCubeWiresV(position, size, color);
}

function(raylib_draw_sphere)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphere(center, radius, color);
}

function(raylib_draw_sphere_ex)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphereEx(center, radius, rings, slices, color);
}

function(raylib_draw_sphere_wires)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawSphereWires(center, radius, rings, slices, color);
}

function(raylib_draw_cylinder)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
}

function(raylib_draw_cylinder_ex)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderEx(startPos, endPos, radiusTop, radiusBottom, slices, color);
}

function(raylib_draw_cylinder_wires)
{
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
}

function(raylib_draw_cylinder_wires_ex)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radiusTop = bruter_pop_float(stack);
    float radiusBottom = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCylinderWiresEx(startPos, endPos, radiusTop, radiusBottom, slices, color);
}

function(raylib_draw_capsule)
{
    Vector3 startPos = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 endPos = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    int rings = bruter_pop_int(stack);
    Color color = color_from_int(bruter_pop_int(stack));
    DrawCapsule(startPos, endPos, radius, slices, rings, color);
}

function(raylib_draw_plane)
{
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawPlane(center, size, color);
}

function(raylib_draw_ray)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawRay(ray, color);
}

function(raylib_draw_grid)
{
    int slices = bruter_pop_int(stack);
    float spacing = bruter_pop_float(stack);
    DrawGrid(slices, spacing);
}

// model managment functions

function(raylib_load_model)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Model model = LoadModel(fileName);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_model_from_mesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Model model = LoadModelFromMesh(mesh);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_model_valid)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    bool isValid = IsModelValid(model);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_model)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    UnloadModel(model);
}

function(raylib_get_model_bounding_box)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    BoundingBox boundingBox = GetModelBoundingBox(model);
    bruter_push_pointer(stack, bounding_box_to_list(boundingBox), NULL, BRUTER_TYPE_LIST);
}

// model drawing functions
function(raylib_draw_model)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModel(model, position, scale, tint);
}

function(raylib_draw_model_ex)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

function(raylib_draw_model_wires)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelWires(model, position, scale, tint);
}

function(raylib_draw_model_wires_ex)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

function(raylib_draw_points)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float scale = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelPoints(model, position, scale, tint);
}

function(raylib_draw_points_ex)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 rotationAxis = vector3_constructor(bruter_pop_pointer(stack));
    float rotationAngle = bruter_pop_float(stack);
    Vector3 scale = vector3_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawModelPointsEx(model, position, rotationAxis, rotationAngle, scale, tint);
}

function(raylib_draw_bouding_box)
{
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    Color color = color_from_int(bruter_pop_int(stack));
    DrawBoundingBox(box, color);
}

function(raylib_draw_billboard)
{
    Camera camera = camera3d_constructor(bruter_pop_pointer(stack));
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    float size = bruter_pop_float(stack);
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawBillboard(camera, texture, position, size, tint);
}

function(raylib_draw_billboard_rec)
{
    Camera camera = camera3d_constructor(bruter_pop_pointer(stack));
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    Rectangle sourceRec = rectangle_constructor(bruter_pop_pointer(stack));
    Vector3 position = vector3_constructor(bruter_pop_pointer(stack));
    Vector2 size = vector2_constructor(bruter_pop_pointer(stack));
    Color tint = color_from_int(bruter_pop_int(stack));
    DrawBillboardRec(camera, texture, sourceRec, position, size, tint);
}

function(raylib_draw_billboard_pro)
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
function(raylib_upload_mesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    bool dynamic = bruter_pop_int(stack);
    UploadMesh(&mesh, dynamic);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_update_mesh_buffer)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    int index = bruter_pop_int(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    int offset = bruter_pop_int(stack);
    UpdateMeshBuffer(mesh, index, data, dataSize, offset);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_mesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    UnloadMesh(mesh);
}

function(raylib_draw_mesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Material material = material_constructor(bruter_pop_pointer(stack));
    Matrix transform = matrix_constructor(bruter_pop_pointer(stack));
    DrawMesh(mesh, material, transform);
}

function(raylib_draw_mesh_instanced)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Material material = material_constructor(bruter_pop_pointer(stack));
    Matrix *transforms = (Matrix*)bruter_pop_pointer(stack);
    int instanceCount = bruter_pop_int(stack);
    DrawMeshInstanced(mesh, material, transforms, instanceCount);
}

function(raylib_get_mesh_bounding_box)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    BoundingBox boundingBox = GetMeshBoundingBox(mesh);
    bruter_push_pointer(stack, bounding_box_to_list(boundingBox), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_tangents)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    GenMeshTangents(&mesh);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_export_mesh)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportMesh(mesh, fileName);
}

function(raylib_export_mesh_as_code)
{
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportMeshAsCode(mesh, fileName);
}

// mesh generation functions
function(raylib_gen_mesh_poly)
{
    int sides = bruter_pop_int(stack);
    float radius = bruter_pop_float(stack);
    Mesh mesh = GenMeshPoly(sides, radius);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_plane)
{
    float width = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    int resX = bruter_pop_int(stack);
    int resZ = bruter_pop_int(stack);
    Mesh mesh = GenMeshPlane(width, length, resX, resZ);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_cube)
{
    float width = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    float length = bruter_pop_float(stack);
    Mesh mesh = GenMeshCube(width, height, length);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_sphere)
{
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshSphere(radius, rings, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_hemi_sphere)
{
    float radius = bruter_pop_float(stack);
    int rings = bruter_pop_int(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshHemiSphere(radius, rings, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_cylinder)
{
    float radius = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshCylinder(radius, height, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_cone)
{
    float radius = bruter_pop_float(stack);
    float height = bruter_pop_float(stack);
    int slices = bruter_pop_int(stack);
    Mesh mesh = GenMeshCone(radius, height, slices);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_torus)
{
    float radius = bruter_pop_float(stack);
    float tubeRadius = bruter_pop_float(stack);
    int radialSegments = bruter_pop_int(stack);
    int tubularSegments = bruter_pop_int(stack);
    Mesh mesh = GenMeshTorus(radius, tubeRadius, radialSegments, tubularSegments);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_knot)
{
    float radius = bruter_pop_float(stack);
    float tubeRadius = bruter_pop_float(stack);
    int radialSegments = bruter_pop_int(stack);
    int sides = bruter_pop_int(stack);
    Mesh mesh = GenMeshKnot(radius, tubeRadius, radialSegments, sides);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_heightmap)
{
    Image heightmap = image_constructor(bruter_pop_pointer(stack));
    Vector3 size = vector3_constructor(bruter_pop_pointer(stack));
    Mesh mesh = GenMeshHeightmap(heightmap, size);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

function(raylib_gen_mesh_cubicmap)
{
    Image cubicmap = image_constructor(bruter_pop_pointer(stack));
    Vector3 cubeSize = vector3_constructor(bruter_pop_pointer(stack));
    Mesh mesh = GenMeshCubicmap(cubicmap, cubeSize);
    bruter_push_pointer(stack, mesh_to_list(mesh), NULL, BRUTER_TYPE_LIST);
}

// material loading/unloading functions
function(raylib_load_materials)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *materialCount = (int*)bruter_pop_pointer(stack);
    bruter_push_pointer(stack, material_list_to_pointer(LoadMaterials(fileName, materialCount)), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_material_default)
{
    Material material = LoadMaterialDefault();
    bruter_push_pointer(stack, material_to_list(material), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_material_valid)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    bool isValid = IsMaterialValid(material);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_material)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    UnloadMaterial(material);
}

function(raylib_set_material_texture)
{
    Material material = material_constructor(bruter_pop_pointer(stack));
    int mapType = bruter_pop_int(stack); // Assuming mapType is an int representing the texture type
    Texture2D texture = texture_constructor(bruter_pop_pointer(stack));
    SetMaterialTexture(&material, mapType, texture);
    bruter_push_pointer(stack, material_to_list(material), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_model_mesh_material)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    int meshId = bruter_pop_int(stack);
    int materialId = bruter_pop_int(stack);
    SetModelMeshMaterial(&model, meshId, materialId);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

// model animations loading/unloading functions
function(raylib_load_model_animations)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    int *animCount = (int*)bruter_pop_pointer(stack);
    ModelAnimation *animations = LoadModelAnimations(fileName, animCount);
    bruter_push_pointer(stack, model_animation_list_to_pointer(animations, *animCount), NULL, BRUTER_TYPE_LIST);
}

function(raylib_update_model_animation)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    int frame = bruter_pop_int(stack);
    UpdateModelAnimation(model, animation, frame);
    bruter_push_pointer(stack, model_to_list(model), NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_model_animation_bones)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    UnloadModelAnimationBones(&model, animation);
}

function(raylib_unload_model_animation)
{
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    UnloadModelAnimation(animation);
}

function(raylib_unload_model_animations)
{
    ModelAnimation *animations = (ModelAnimation*)bruter_pop_pointer(stack);
    int animCount = bruter_pop_int(stack);
    UnloadModelAnimations(animations, animCount);
}

function(raylib_is_model_animation_valid)
{
    Model model = model_constructor(bruter_pop_pointer(stack));
    ModelAnimation animation = model_animation_constructor(bruter_pop_pointer(stack));
    bool isValid = IsModelAnimationValid(model, animation);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

// collision detection functions

function(raylib_check_collision_spheres)
{
    Vector3 center1 = vector3_constructor(bruter_pop_pointer(stack));
    float radius1 = bruter_pop_float(stack);
    Vector3 center2 = vector3_constructor(bruter_pop_pointer(stack));
    float radius2 = bruter_pop_float(stack);
    bool collision = CheckCollisionSpheres(center1, radius1, center2, radius2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_boxes)
{
    BoundingBox box1 = bounding_box_constructor(bruter_pop_pointer(stack));
    BoundingBox box2 = bounding_box_constructor(bruter_pop_pointer(stack));
    bool collision = CheckCollisionBoxes(box1, box2);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_check_collision_box_sphere)
{
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    bool collision = CheckCollisionBoxSphere(box, center, radius);
    bruter_push_int(stack, collision, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_ray_collision_sphere)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Vector3 center = vector3_constructor(bruter_pop_pointer(stack));
    float radius = bruter_pop_float(stack);
    RayCollision collision = GetRayCollisionSphere(ray, center, radius);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_ray_collision_box)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    BoundingBox box = bounding_box_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionBox(ray, box);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_ray_collision_mesh)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Mesh mesh = mesh_constructor(bruter_pop_pointer(stack));
    Matrix transform = matrix_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionMesh(ray, mesh, transform);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_ray_collision_triangle)
{
    Ray ray = ray_constructor(bruter_pop_pointer(stack));
    Vector3 p1 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p2 = vector3_constructor(bruter_pop_pointer(stack));
    Vector3 p3 = vector3_constructor(bruter_pop_pointer(stack));
    RayCollision collision = GetRayCollisionTriangle(ray, p1, p2, p3);
    bruter_push_pointer(stack, ray_collision_to_list(collision), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_ray_collision_quad)
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
function(raylib_init_audio_device)
{
    InitAudioDevice();
}

function(raylib_close_audio_device)
{
    CloseAudioDevice();
}

function(raylib_is_audio_device_ready)
{
    bool isReady = IsAudioDeviceReady();
    bruter_push_int(stack, isReady, NULL, BRUTER_TYPE_ANY);
}

function(raylib_set_master_volume)
{
    float volume = bruter_pop_float(stack);
    SetMasterVolume(volume);
}

function(raylib_get_master_volume)
{
    float volume = GetMasterVolume();
    bruter_push_float(stack, volume, NULL, BRUTER_TYPE_ANY);
}

// wave/sound loading/unloading functions

function(raylib_load_wave)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Wave wave = LoadWave(fileName);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_wave_from_memory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Wave wave = LoadWaveFromMemory(fileType, data, dataSize);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_wave_valid)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    bool isValid = IsWaveValid(wave);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_load_sound)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Sound sound = LoadSound(fileName);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_sound_from_wave)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    Sound sound = LoadSoundFromWave(wave);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_sound_alias)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    Sound aliasSound = LoadSoundAlias(sound);
    bruter_push_pointer(stack, sound_to_list(aliasSound), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_sound_valid)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    bool isValid = IsSoundValid(sound);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_update_sound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    void *data = bruter_pop_pointer(stack);
    int samplesCount = bruter_pop_int(stack);
    UpdateSound(sound, data, samplesCount);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(raylib_unload_wave)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    UnloadWave(wave);
}

function(raylib_unload_sound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    UnloadSound(sound);
}

function(raylib_unload_sound_alias)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    UnloadSoundAlias(sound);
}

function(raylib_export_wave)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportWave(wave, fileName);
}

function(raylib_export_wave_as_code)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    char *fileName = (char*)bruter_pop_pointer(stack);
    ExportWaveAsCode(wave, fileName);
}

// wave/sound management functions
function(raylib_play_sound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    PlaySound(sound);
}

function(raylib_stop_sound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    StopSound(sound);
}

function(raylib_pause_sound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    PauseSound(sound);
}

function(raylib_resume_sound)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    ResumeSound(sound);
}

function(raylib_is_sound_playing)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    bool isPlaying = IsSoundPlaying(sound);
    bruter_push_int(stack, isPlaying, NULL, BRUTER_TYPE_ANY);
}

function(raylib_set_sound_volume)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetSoundVolume(sound, volume);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_sound_pitch)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetSoundPitch(sound, pitch);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_sound_pan)
{
    Sound sound = sound_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetSoundPan(sound, pan);
    bruter_push_pointer(stack, sound_to_list(sound), NULL, BRUTER_TYPE_LIST);
}

function(raylib_wave_copy)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    Wave copiedWave = WaveCopy(wave);
    bruter_push_pointer(stack, wave_to_list(copiedWave), NULL, BRUTER_TYPE_LIST);
}

function(raylib_wave_crop)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    int initSample = bruter_pop_int(stack);
    int finalSample = bruter_pop_int(stack);
    WaveCrop(&wave, initSample, finalSample);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(raylib_wave_format)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    int sampleRate = bruter_pop_int(stack);
    int sampleSize = bruter_pop_int(stack);
    int channels = bruter_pop_int(stack);
    WaveFormat(&wave, sampleRate, sampleSize, channels);
    bruter_push_pointer(stack, wave_to_list(wave), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_wave_samples)
{
    Wave wave = wave_constructor(bruter_pop_pointer(stack));
    void *samples = LoadWaveSamples(wave);
    bruter_push_pointer(stack, samples, NULL, BRUTER_TYPE_BUFFER);
}

function(raylib_unload_wave_samples)
{
    void *samples = bruter_pop_pointer(stack);
    UnloadWaveSamples(samples);
}

// music management functions
function(raylib_load_music_stream)
{
    char *fileName = (char*)bruter_pop_pointer(stack);
    Music music = LoadMusicStream(fileName);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(raylib_load_music_stream_from_memory)
{
    char *fileType = (char*)bruter_pop_pointer(stack);
    void *data = bruter_pop_pointer(stack);
    int dataSize = bruter_pop_int(stack);
    Music music = LoadMusicStreamFromMemory(fileType, data, dataSize);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_music_valid)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    bool isValid = IsMusicValid(music);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_music_stream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    UnloadMusicStream(music);
}

function(raylib_play_music_stream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    PlayMusicStream(music);
}

function(raylib_is_music_stream_playing)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    bool isPlaying = IsMusicPlaying(music);
    bruter_push_int(stack, isPlaying, NULL, BRUTER_TYPE_ANY);
}

function(raylib_update_music_stream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    UpdateMusicStream(music);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(raylib_stop_music_stream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    StopMusicStream(music);
}

function(raylib_pause_music_stream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    PauseMusicStream(music);
}

function(raylib_resume_music_stream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    ResumeMusicStream(music);
}

function(raylib_seek_music_stream)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float position = bruter_pop_float(stack);
    SeekMusicStream(music, position);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_music_volume)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetMusicVolume(music, volume);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_music_pitch)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetMusicPitch(music, pitch);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_music_pan)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetMusicPan(music, pan);
    bruter_push_pointer(stack, music_to_list(music), NULL, BRUTER_TYPE_LIST);
}

function(raylib_get_music_time_length)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float length = GetMusicTimeLength(music);
    bruter_push_float(stack, length, NULL, BRUTER_TYPE_ANY);
}

function(raylib_get_music_time_played)
{
    Music music = music_constructor(bruter_pop_pointer(stack));
    float playedTime = GetMusicTimePlayed(music);
    bruter_push_float(stack, playedTime, NULL, BRUTER_TYPE_ANY);
}

// audiostream management functions
function(raylib_load_audio_stream)
{
    int sampleRate = bruter_pop_int(stack);
    int sampleSize = bruter_pop_int(stack);
    int channels = bruter_pop_int(stack);
    AudioStream stream = LoadAudioStream(sampleRate, sampleSize, channels);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_audio_stream_valid)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    bool isValid = IsAudioStreamValid(stream);
    bruter_push_int(stack, isValid, NULL, BRUTER_TYPE_ANY);
}

function(raylib_unload_audio_stream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    UnloadAudioStream(stream);
}

function(raylib_update_audio_stream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    void *data = bruter_pop_pointer(stack);
    int samplesCount = bruter_pop_int(stack);
    UpdateAudioStream(stream, data, samplesCount);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_is_audio_stream_processed)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    bool isProcessed = IsAudioStreamProcessed(stream);
    bruter_push_int(stack, isProcessed, NULL, BRUTER_TYPE_ANY);
}

function(raylib_play_audio_stream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    PlayAudioStream(stream);
}

function(raylib_pause_audio_stream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    StopAudioStream(stream);
}

function(raylib_stop_audio_stream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    PauseAudioStream(stream);
}

function(raylib_resume_audio_stream)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    ResumeAudioStream(stream);
}

function(raylib_set_audio_stream_volume)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float volume = bruter_pop_float(stack);
    SetAudioStreamVolume(stream, volume);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_audio_stream_pitch)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float pitch = bruter_pop_float(stack);
    SetAudioStreamPitch(stream, pitch);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_audio_stream_pan)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    float pan = bruter_pop_float(stack);
    SetAudioStreamPan(stream, pan);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_set_audio_stream_buffer_size_default)
{
    int size = bruter_pop_int(stack);
    SetAudioStreamBufferSizeDefault(size);
}

function(raylib_set_audio_stream_callback)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback callback = (AudioCallback)bruter_pop_pointer(stack);
    SetAudioStreamCallback(stream, callback);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_attach_audio_stream_processor)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    AttachAudioStreamProcessor(stream, processor);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_detach_audio_stream_processor)
{
    AudioStream stream = audio_stream_constructor(bruter_pop_pointer(stack));
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    DetachAudioStreamProcessor(stream, processor);
    bruter_push_pointer(stack, audio_stream_to_list(stream), NULL, BRUTER_TYPE_LIST);
}

function(raylib_attach_audio_mixed_processor)
{
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    AttachAudioMixedProcessor(processor);
}

function(raylib_detach_audio_mixed_processor)
{
    AudioCallback processor = (AudioCallback)bruter_pop_pointer(stack);
    DetachAudioMixedProcessor(processor);
}