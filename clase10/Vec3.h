#ifndef VEC3_H_
#define VEC3_H_

typedef struct strVec3* Vec3;
typedef enum { False, True } Bool;

Vec3 vec3_create(float x, float y, float z);
void vec3_destroy(Vec3);
void vec3_setX(Vec3, float);
void vec3_setY(Vec3, float);
void vec3_setZ(Vec3, float);
float vec3_getX(Vec3);
float vec3_getY(Vec3);
float vec3_getZ(Vec3);
float vec3_magnitude(Vec3);
Vec3 vec3_normalize(Vec3);

void vec3_print(Vec3);
void vec3_println(Vec3);
Bool vec3_equals(Vec3);
Vec3 vec3_clone(Vec3);


#endif