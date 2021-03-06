#ifdef LPG3DMATH_H

#include <stdio.h>
#include <math.h>
#include <string.h>


#define PI (3.14159265358979323846)
#define TOW_PI (2.0*PI)
#define PI_DIV_180 (0.017453292519943296)
#define PI_DIV_180_INV (57.2957795130823229)

#define degreeToRad(x) ((x)*PI_DIV_180)
#define radToDegree(x) ((x)*PI_DIV_180_INV)

/*--------------- Data Type ----------------*/

/*-- Matrixs --*/
typedef float lpg3dm_matrix22f[4];
typedef int lpg3dm_matrix22i[4];
typedef double lpg3dm_matrix22d[4];

typedef float lpg3dm_matrix33f[9];
typedef int lpg3dm_matrix33i[9];
typedef double lpg3dm_matrix33d[9];

typedef float lpg3dm_matrix44f[16];
typedef int lpg3dm_matrix44i[16];
typedef double lpg3dm_matrix44d[16];

/*-- Vectors --*/
typedef float lpg3dm_vec4f[4];
typedef float lpg3dm_vec3f[3];
typedef float lpg3dm_vec2f[2];

typedef int lpg3dm_vec4i[4];
typedef int lpg3dm_vec3i[3];
typedef int lpg3dm_vec2i[2];

typedef double lpg3dm_vec4d[4];
typedef double lpg3dm_vec3d[3];
typedef double lpg3dm_vec2d[2];


/*--------- Operations functions -----------*/

/*! @brief Load the identity matrix into your matrix
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the identity matrix
 *  @return void
 */
void lpg3dm_loadIdentity(lpg3dm_matrix44f m){

    static lpg3dm_matrix44f matrixIdentity = { 1.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 1.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 1.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 1.0f };

    memcpy(m, matrixIdentity, sizeof(matrixIdentity));
}


/*! @brief Calculate the rotation matrix give a angle in degree and a vector with each coordinate
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the rotation matrix
 *  @param [float] angulo - The angle in degree for rotation
 *  @param [float] x - The x coordinate of the vector
 *  @param [float] y - The y coordinate of the vector
 *  @param [float] z - The z coordinate of the vector
 *  @return void
 */
void lpg3dm_rotationd4f(lpg3dm_matrix44f m, float angulo, float x, float y, float z){
    float seno, cosseno, moduloVetor;
    float xx,yy,zz,xy,xz,yz,xseno,zseno,yseno,umMenosCosseno;

    seno = (float)sin(angulo);
    cosseno = (float) cos(angulo);

    moduloVetor = (float) sqrt(x*x + y*y + z*z);

    if(moduloVetor == 0.0f){
        return ;
    }

    x = x/moduloVetor;
    y = y/moduloVetor;
    z = z/moduloVetor;

    xx = x*x;
    yy = y*y;
    zz = z*z;
    xy = x*y;
    xz = x*z;
    yz = y*z;
    xseno = x*seno;
    yseno = y*seno;
    zseno = z*seno;
    umMenosCosseno = 1.0f - cosseno;
    #define M(linha,coluna) m[coluna*4 + linha]

    M(0,0) = (xx*umMenosCosseno) + cosseno;
    M(0,1) = (xy*umMenosCosseno) + zseno;
    M(0,2) = (xz*umMenosCosseno) - yseno;
    M(0,3) = 0.0f;
    M(1,0) = (xy*umMenosCosseno) - zseno;
    M(1,1) = (yy*umMenosCosseno) + cosseno;
    M(1,2) = (yz*umMenosCosseno) + xseno;
    M(1,3) = 0.0f;
    M(2,0) = (xz*umMenosCosseno) + yseno;
    M(2,1) = (yz*umMenosCosseno)- xseno;
    M(2,2) = (zz*umMenosCosseno) + cosseno;
    M(2,3) = 0.0f;
    M(3,0) = 0.0;
    M(3,1) = 0.0f;
    M(3,2) = 0.0f;
    M(3,3) = 1.0f;

    #undef M
/*
    |[x*x(1-cos @) +   cos @] [x*y(1-cos @) - z*sin @] [x*z(1-cos @) + y*sin @]   [0]   |
    |[x*y(1-cos @) + z*sen @] [y*y(1-cos @) +   cos @] [y*z(1-cos @) - x*sin @]   [0]   |
    |[x*z(1-cos @) - y*sen @] [y*z(1-cos @) + x*sin @] [z*z(1-cos @) +   cos @]   [0]   |
    |[             0        ] [             0        ] [             0        ]   [1]   |
*/
}
// lpg3dm_matrix44f *lpg3dm_rotationd4fr(lpg3dm_matrix44f m, float angulo, float x, float y, float z);


/*! @brief Calculate the rotation matrix give a angle in radian and a vector with each coordinate
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the rotation matrix
 *  @param [float] angulo - The angle in radian for rotation
 *  @param [float] x - The x coordinate of the vector
 *  @param [float] y - The y coordinate of the vector
 *  @param [float] z - The z coordinate of the vector
 *  @return void
 */
void lpg3dm_rotationr4f(lpg3dm_matrix44f m, float angulo, float x, float y, float z){
    angulo = angulo*0.017453292519943296;
    lpg3dm_rotationd4f(m, angulo, x, y, z);
}


/*! @brief Calculate the rotation matrix give a angle in degree and a vector
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the rotation matrix
 *  @param [float] angulo - The angle in degree for rotation
 *  @param [lpg3dm_vec3f] vec - The vector
 *  @return void
 */
void lpg3dm_rotationd4fv(lpg3dm_matrix44f m, float angulo, lpg3dm_vec3f vec){
    lpg3dm_rotationd4f(m, angulo, vec[0], vec[1], vec[2]);
}

/*! @brief Calculate the rotation matrix give a angle in radian and a vector
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the rotation matrix
 *  @param [float] angulo - The angle in radian for rotation
 *  @param [lpg3dm_vec3f] vec - The vector
 *  @return void
 */
void lpg3dm_rotationr4fv(lpg3dm_matrix44f m, float angulo, lpg3dm_vec3f vec){
    lpg3dm_rotationr4f(m, angulo, vec[0], vec[1], vec[2]);
}

/*! @brief Calculate the scaling matrix give the how much scaling in the axis.
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the scaling matrix
 *  @param [float] x - How much scaling in the X axis
 *  @param [float] y - How much scaling in the Y axis
 *  @param [float] z - How much scaling in the Z axis
 *  @return void
 */
void lpg3dm_scale4f(lpg3dm_matrix44f m, float x, float y, float z){

    #define M(l,c) m[(c*4)+l]

    M(0,0) = M(0,0)*x;
    M(1,1) = M(1,1)*y;
    M(2,2) = M(2,2)*z;
    M(3,3) = 1;

    #undef M

}

/*! @brief Calculate the scaling matrix give the how much scaling in the axis with one vector.
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the scaling matrix
 *  @param [lpg3dm_vec3f] vec - How much scaling in the axis
 *  @return void
 */
void lpg3dm_scale4fv(lpg3dm_matrix44f m, lpg3dm_vec3f vec){

    lpg3dm_scale4f(m, vec[0], vec[1], vec[2]);

}
void lpg3dm_vecSize4f(float x, float y, float z, float *tam){
    *tam = sqrt((x*x) + (y*y) + (z*z));
}

void lpg3dm_vecSize4fv(lpg3dm_vec3f vetor, float *tam){
    lpg3dm_vecSize4f(vetor[0], vetor[1], vetor[2], tam);
}

void lpg3dm_translate4f(lpg3dm_matrix44f m,  float x, float y, float z){
    #define M(l,c) m[(c*4)+l]

    M(0,3) = M(0,3) + x;
    M(1,3) = M(1,3) + y;
    M(2,3) = M(2,3) + z;
    M(3,3) = 1;

    #undef M
}


void lpg3dm_translate4fv(lpg3dm_matrix44f m, lpg3dm_vec3f vec){
    lpg3dm_translate4f(m, vec[0], vec[1], vec[2]);
}

void lpg3dm_multi4f(lpg3dm_matrix44f m, lpg3dm_matrix44f a, lpg3dm_matrix44f b){
    #define A(l,c) a[(c*4)+l]
    #define B(l,c) b[(c*4)+l]
    #define C(l,c) m[(c*4)+l]

    int i;
    float ai0, ai1, ai2, ai3;
    for(i = 0; i < 4;i++){
        ai0 = A(i,0);
        ai1 = A(i,1);
        ai2 = A(i,2);
        ai3 = A(i,3);
        C(i,0) = (ai0 * B(0,0)) + (ai1 * B(1,0)) + (ai2 * B(2,0)) + (ai3 * B(3,0));
        C(i,1) = (ai0 * B(0,1)) + (ai1 * B(1,1)) + (ai2 * B(2,1)) + (ai3 * B(3,1));
        C(i,2) = (ai0 * B(0,2)) + (ai1 * B(1,2)) + (ai2 * B(2,2)) + (ai3 * B(3,2));
        C(i,3) = (ai0 * B(0,3)) + (ai1 * B(1,3)) + (ai2 * B(2,3)) + (ai3 * B(3,3));
    }

    #undef A
    #undef B
    #undef C
}

void lpg3dm_vecCrossProduct3f(lpg3dm_vec3f res, float aX, float aY, float aZ, float bX, float bY, float bZ){
    res[0] = aY*bZ - bY*aZ;
    res[1] =-aX*bZ + bX*aZ;
    res[2] = aX*bY - bX*aY;
}

void lpg3dm_vecCrossProduct3fv(lpg3dm_vec3f m, lpg3dm_vec3f a, lpg3dm_vec3f b){
    lpg3dm_vecCrossProduct3f(m, a[0], a[1], a[2], b[0], b[1], b[2]);
}

void lpg3dm_vecScale(lpg3dm_vec3f m, float x){
    m[0] = m[0] * x;
    m[1] = m[1] * x;
    m[2] = m[2] * x;
}
void lpg3dm_vecScalev(lpg3dm_vec3f r, lpg3dm_vec3f m,float x){
    r[0] = m[0] * x;
    r[1] = m[1] * x;
    r[2] = m[2] * x;
}

void lpg3dm_vecNormalize3f(lpg3dm_vec3f vetor){
    float tam;
    lpg3dm_vecSize4fv(vetor, &tam);
    if(tam == 0){
        tam = 1;
    }
    vetor[0] = vetor[0] / tam;
    vetor[1] = vetor[1] / tam;
    vetor[2] = vetor[2] / tam;
}

/*! @brief Create the ortho matrix.
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the ortho matrix
 *  @param [float] left - Specifies the left finla coordenate.
 *  @param [float] right - Specifies the right finla coordenate
 *  @param [float] bottom - Specifies the bottom finla coordenate
 *  @param [float] top - Specifies the top finla coordenate
 *  @param [float] near - Specifies the near finla coordenate
 *  @param [float] far - Specifies the far finla coordenate
 *  @return void
 */
void lpg3dm_orth(lpg3dm_matrix44f m, float left, float right, float bottom, float top, float near, float far){

    lpg3dm_loadIdentity(m);

    float rl, tb, fn, plusrl, plustb, plusfn;

    rl = right-left;
    tb = top-bottom;
    fn = far-near;
    plusrl = right+left;
    plustb = top+bottom;
    plusfn = far+near;

    m[0] = (2.0f/rl);
    m[3] = (-plusrl/rl);
    m[5] = (2.0f/tb);
    m[7] = (-plustb/tb);
    m[10] = (-2.0f/fn);
    m[11] = (-plusfn/fn);
    m[15] = 1.0f;

/*
    |[2/(right-left)] [       0      ] [       0      ] [ -(right+left)/(right-left) ]|
    |[       0      ] [2/(top-bottom)] [       0      ] [-((top+bottom)/(top-bottom))]|
    |[       0      ] [       0      ] [ -2/(far-near)] [  -((far+near)/(far-near))  ]|
    |[       0      ] [       0      ] [       0      ] [              1             ]|
*/
}

/*! @brief Create the perspective matrix.
 *  @param [lpg3dm_matrix44f] m - The matrix who recive the perspective matrix
 *  @param [float] fov - Specifies the fov in degree.
 *  @param [float] aspect - Specifies the aspect ration of the screen
 *  @param [float] near - Specifies the near finla coordenate
 *  @param [float] far - Specifies the far finla coordenate
 *  @return void
 */
void lpg3dm_perspective(lpg3dm_matrix44f m, float fov, float aspect, float near, float far){

    lpg3dm_loadIdentity(m);

    fov = fov*0.017453292519943296;

    float top = near * tanf(fov*0.5);
    float bottom = -top;
    float left = bottom * aspect;
    float right = -left;

    m[0]  = (2.0f * near)/(left - right);
    m[5]  = (2.0f * near)/(top - bottom);
    m[8]  = (right + left)/((right - left));
    m[9]  = (top + bottom)/(top-bottom);
    m[10] = -((far + near)/(far-near));
    m[11] = -1.0f;
    m[14] = -((2.0f * (far*near))/(far-near));
    m[15] = 0.0f;

}

void lpg3dm_addVector3f(lpg3dm_vec3f res, float aX, float aY, float aZ, float bX, float bY, float bZ){
    res[0] = aX + bX;
    res[1] = aY + bY;
    res[2] = aZ + bZ;
}
void lpg3dm_addVector3fv(lpg3dm_vec3f res, lpg3dm_vec3f a, lpg3dm_vec3f b){
    lpg3dm_addVector3f(res, a[0], a[1], a[2], b[0], b[1], b[2]);
}
void lpg3dm_subtractVector3f(lpg3dm_vec3f res, float aX, float aY, float aZ, float bX, float bY, float bZ){
    lpg3dm_addVector3f(res, aX, aY, aZ, -bX, -bY, -bZ);
}
void lpg3dm_subtractVector3fv(lpg3dm_vec3f res, lpg3dm_vec3f a, lpg3dm_vec3f b){
    lpg3dm_subtractVector3f(res, a[0], a[1], a[2], b[0], b[1], b[2]);
}


/*------------ Print functions -------------*/
void lpg3dm_printMatrix44f(lpg3dm_matrix44f m){
    int i;
    printf("\n");
    for(i = 0;i < 16;i++){
        if(i%4 == 0 && i != 0)
            printf("\n");
        printf(" %.2f ", m[i]);
    }
    printf("\n");
}
void lpg3dm_printMatrix33f(lpg3dm_matrix33f m){
    int i;
    printf("\n");
    for(i = 0;i < 9;i++){
        if(i%3 == 0 && i != 0)
            printf("\n");
        printf(" %.2f ", m[i]);
    }
    printf("\n");
}
void lpg3dm_printMatrix22f(lpg3dm_matrix22f m){
    int i;
    printf("\n");
    for(i = 0;i < 4;i++){
        if(i%2 == 0 && i != 0)
            printf("\n");
        printf(" %.2f ", m[i]);
    }
    printf("\n");

}
void lpg3dm_printVec3f(lpg3dm_vec3f v){
    printf("\n(%f, %f, %f)\n", v[0], v[1], v[2]);
}

void lpg3dm_lookAtf(lpg3dm_matrix44f lookAtm, float posX, float posY, float posZ, float targerX, float targerY, float targerZ, float upX, float upY, float upZ){
    lpg3dm_vec3f direction;
    lpg3dm_vec3f right;
    lpg3dm_vec3f up;


    lpg3dm_subtractVector3f(direction, posX, posY, posZ, targerX, targerY, targerZ);
    lpg3dm_vecNormalize3f(direction);

    lpg3dm_vecCrossProduct3f(right, upX, upY, upZ, direction[0], direction[1], direction[2]);
    lpg3dm_vecNormalize3f(right);

    lpg3dm_vecCrossProduct3f(up, direction[0], direction[1], direction[2], right[0], right[1], right[2]);
    lpg3dm_vecNormalize3f(up);

    #define A(l,c) lookAtm[(c*4)+l]

    A(0, 0) = right[0];
    A(0, 1) = right[1];
    A(0, 2) = right[2];
    A(0, 3) = (right[0]*(-posX)) + (right[1]*(-posY)) + (right[2]*(-posZ));


    A(1, 0) = up[0];
    A(1, 1) = up[1];
    A(1, 2) = up[2];
    A(1, 3) = (up[0]*(-posX)) + (up[1]*(-posY)) + (up[2]*(-posZ));

    A(2, 0) = direction[0];
    A(2, 1) = direction[1];
    A(2, 2) = direction[2];
    A(2, 3) = (direction[0]*(-posX)) + (direction[1]*(-posY)) + (direction[2]*(-posZ));

    A(3, 0) = 0;
    A(3, 1) = 0;
    A(3, 2) = 0;
    A(3, 3) = 1;

    #undef A
/*
    |[ Rx ] [ Ry ] [ Rz ] [ 0 ]|     |[ 1 ] [ 0 ] [ 0 ] [ -Px ]|
    |[ Ux ] [ Uy ] [ Uz ] [ 0 ]|     |[ 0 ] [ 1 ] [ 0 ] [ -Py ]|
    |[ Dx ] [ Dy ] [ Dz ] [ 0 ]|  *  |[ 0 ] [ 0 ] [ 1 ] [ -Pz ]|
    |[  0 ] [  0 ] [  0 ] [ 1 ]|     |[ 0 ] [ 0 ] [ 0 ] [   1 ]|
*/
}
void lpg3dm_lookAtfv(lpg3dm_matrix44f lookAtm, lpg3dm_vec3f position, lpg3dm_vec3f target, lpg3dm_vec3f up){
    lpg3dm_lookAtf(lookAtm, position[0],  position[1], position[2], target[0], target[1], target[2], up[0], up[1], up[2]);
}


#endif // MY_3DLIB
