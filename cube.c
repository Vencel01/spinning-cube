#include <stdio.h>
#include <math.h>

#define WIDTH 120
#define HEIGHT 120

typedef struct {
    float x, y, z;
} Vector3D;

Vector3D vertices[] = {
    {-1,-1,-1},
    {-1,-1,1},
    {-1,1,-1},
    {-1,1,1},
    {1,-1,-1},
    {1,-1,1},
    {1,1,-1},
    {1,1,1}
};

int edges[][2] = {
    {0,1},
    {0,2},
    {0,4},
    {1,3},
    {1,5},
    {2,3},
    {2,6},
    {3,7},
    {4,5},
    {4,6},
    {5,7},
    {6,7}
};

void drawPoint(int x, int y, char c) {
    printf("\033[%d;%dH%c", y, x, c);
    fflush(stdout);
}

void drawLine(int x1, int y1, int x2, int y2, char c) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
    
    while (1) {
        drawPoint(x1, y1, c);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

void rotate(Vector3D *point, float angleX, float angleY, float angleZ) {
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float cosZ = cos(angleZ);
    float sinZ = sin(angleZ);
    
    float x = point->x;
    float y = point->y;
    float z = point->z;
    
    // rotate around X-axis
    float xRotate = x;
    float yRotate = y * cosX - z * sinX;
    float zRotate = y * sinX + z * cosX;
    
    // rotate around Y-axis
    x = xRotate * cosY + zRotate * sinY;
    y = yRotate;
    z = -xRotate * sinY + zRotate * cosY;
    
    // rotate around Z-axis
    xRotate = x * cosZ - y * sinZ;
    yRotate = x * sinZ + y * cosZ;
    zRotate = z;
    
    point->x = xRotate;
    point->y = yRotate;
    point->z = zRotate;
}

void drawCube(float angleX, float angleY, float angleZ) {
    for (int i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {
        Vector3D p1 = vertices[edges[i][0]];
        Vector3D p2 = vertices[edges[i][1]];
        
        rotate(&p1, angleX, angleY, angleZ);
        rotate(&p2, angleX, angleY, angleZ);
        
        int x1 = (int)(p1.x * 5) + WIDTH / 2;
        int y1 = (int)(p1.y * 5) + HEIGHT / 2;
        int x2 = (int)(p2.x * 5) + WIDTH / 2;
        int y2 = (int)(p2.y * 5) + HEIGHT / 2;
        
        drawLine(x1, y1, x2, y2, '#');
    }
}

int main() {
    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;
    
    while (1) {
        // clear the screen
        printf("\033[2J");
        
        // draw the cube
        drawCube(angleX, angleY, angleZ);
        
        // update the angles
        angleX += 0.01f;
        angleY += 0.02f;
        angleZ += 0.03f;
        
        // wait for a while
        for (int i = 0; i < 10000000; i++) {}
    }
    
    return 0;
}
