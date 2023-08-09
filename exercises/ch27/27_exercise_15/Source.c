#include <stdio.h>
#include <stdlib.h>

typedef void (*fp)(struct Shape *);
typedef void (*fp2)(struct Shape *, int);

struct VFTable
{
    fp draw;
    fp2 rotate;
};

struct Shape
{
    struct VFTable *vft;
    int x;
    int y;
};

struct Circle
{
    struct Shape shape;
    int r;
};

void draw(struct Shape *p)
{
    (p->vft->draw)(p);
}

void rotate(struct Shape *p, int d)
{
    (p->vft->rotate)(p, d);
}

void draw_shape(struct Shape *p)
{
    printf("Shape with coordinates x: %d and y: %d\n", p->x, p->y);
}

void rotate_shape(struct Shape *p, int d)
{
    printf("Rotating shape with coordinates x: %d and y: %d by %d degrees\n", p->x, p->y, d);
}

void draw_circle(struct Shape *p)
{
    struct Circle *c = (struct Circle *)p;
    printf("Circle with coordinates x: %d and y: %d and radius r: %d\n", p->x, p->y, c->r);
}

void rotate_circle(struct Shape *p, int d)
{
    struct Circle *c = (struct Circle *)p;
    printf("Rotating circle with coordinates x: %d and y: %d and radius r: %d by %d degrees\n", p->x, p->y, c->r, d);
}

struct Shape *init_shape(int x, int y)
{
    struct Shape *shape = (struct Shape *)malloc(sizeof(struct Shape));
    if (!shape)
    {
        fprintf(stderr, "cannot allocate memory for shape of size: %d\n", sizeof(struct Shape));
        exit(1);
    }
    shape->vft = (struct VFTable *)malloc(sizeof(struct VFTable));
    if (!shape->vft)
    {
        fprintf(stderr, "cannot allocate memory for function pointers array of size: %d\n", sizeof(struct VFTable));
        exit(2);
    }
    shape->vft->draw = &draw_shape;
    shape->vft->rotate = &rotate_shape;
    shape->x = x;
    shape->y = y;
    return shape;
}

struct Circle *init_circle(int x, int y, int r)
{
    struct Circle *circle = (struct Circle *)malloc(sizeof(struct Circle));
    if (!circle)
    {
        fprintf(stderr, "cannot allocate memory for circle of size: %d\n", sizeof(struct Circle));
        exit(3);
    }
    circle->shape = *init_shape(x, y);
    circle->shape.vft->draw = &draw_circle;
    circle->shape.vft->rotate = &rotate_circle;
    circle->r = r;
    return circle;
}

int main(void)
{
    struct Shape *shape = init_shape(50, 50);
    struct Circle *circle = init_circle(100, 100, 50);

    draw(shape);
    draw(circle);
    rotate(shape, 10);
    rotate(circle, 180);
}