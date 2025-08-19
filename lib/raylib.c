#include "bruter.h"
#include "raylib.h"

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
    bruter_push_pointer(list, image_to_list(info.image), "image", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, texture_to_list(font.texture), "texture", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, vector3_to_list(cam.position), "position", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector3_to_list(cam.target), "target", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector3_to_list(cam.up), "up", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, vector2_to_list(cam.offset), "offset", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector2_to_list(cam.target), "target", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, texture_to_list(map.texture), "texture", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, shader_to_list(mat.shader), "shader", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, mat.maps, "maps", BRUTER_TYPE_BUFFER);
    
    BruterList *paramsList = bruter_new(4, true, true);
    for (int i = 0; i < 4; i++) 
    {
        bruter_push_float(paramsList, mat.params[i], "param", BRUTER_TYPE_FLOAT);
    }
    
    bruter_push_pointer(list, paramsList, "params", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, vector3_to_list(t.translation), "translation", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector4_to_list(t.rotation), "rotation", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector3_to_list(t.scale), "scale", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, matrix_to_list(m.transform), "transform", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, vector3_to_list(r.position), "position", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector3_to_list(r.direction), "direction", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, vector3_to_list(rc.point), "point", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector3_to_list(rc.normal), "normal", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, vector3_to_list(box.min), "min", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, vector3_to_list(box.max), "max", BRUTER_TYPE_BUFFER);
    return list;
}

Wave wave_contructor(BruterList *wave)
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
    bruter_push_pointer(list, audio_stream_to_list(snd.stream), "stream", BRUTER_TYPE_BUFFER);
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
    bruter_push_pointer(list, audio_stream_to_list(mus.stream), "stream", BRUTER_TYPE_BUFFER);
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

    bruter_push_pointer(list, lensDistortionValues, "lensDistortionValues", BRUTER_TYPE_BUFFER);
    bruter_push_pointer(list, chromaAbCorrection, "chromaAbCorrection", BRUTER_TYPE_BUFFER);

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
        bruter_push_pointer(projection_list, matrix_to_list(config.projection[i]), "projection", BRUTER_TYPE_BUFFER);
    }
    bruter_push_pointer(list, projection_list, "projection", BRUTER_TYPE_BUFFER);

    BruterList *viewOffset_list = bruter_new(2, true, true);
    for (int i = 0; i < 2; i++)
    {
        bruter_push_pointer(viewOffset_list, matrix_to_list(config.viewOffset[i]), "viewOffset", BRUTER_TYPE_BUFFER);
    }
    bruter_push_pointer(list, viewOffset_list, "viewOffset", BRUTER_TYPE_BUFFER);

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
    
    bruter_push_pointer(list, params_list, "params", BRUTER_TYPE_BUFFER);
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
    BruterList *vec2 = bruter_list_create(2);
    bruter_list_push_float(vec2, position.x);
    bruter_list_push_float(vec2, position.y);
    bruter_push_pointer(stack, vec2, NULL, BRUTER_TYPE_ANY);
}