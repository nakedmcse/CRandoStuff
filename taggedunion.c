// Tagged Union
#include <stdio.h>
#include <stdlib.h>

// Base types
typedef struct {
    double side;
} Square;

double squareArea(void *object) {
    const Square *square = (const Square *)object;
    return square->side * square->side;
}

typedef struct {
    double length, width;
} Rectangle;

double rectangleArea(void *object) {
    const Rectangle *rectangle = (const Rectangle *)object;
    return rectangle->length * rectangle->width;
}

typedef struct {
    double radius;
} Circle;

double circleArea(void *object) {
    const Circle *circle = (const Circle *)object;
    return (circle->radius * circle->radius) * 3.14;
}

// Tag
typedef enum {
    SHAPE_SQUARE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE
} ShapeType;

// Tagged Union Type
typedef struct {
    ShapeType type;
    union {
        Square square;
        Rectangle rectangle;
        Circle circle;
    } data;
    double (*area)(void *);
} Shape;

// Dynamic Array of Shapes
typedef struct {
    Shape *values;
    size_t count;
    size_t capacity;
} dynArray;

void append(dynArray *array, Shape value) {
    if (array->count >= array->capacity) {
        if (array->capacity == 0) {
            array->capacity = 256;
            array->values = (Shape*)malloc(array->capacity * sizeof(Shape));
        }
        else {
            array->capacity *= 2;
            array->values = (Shape*)realloc(array->values, array->capacity * sizeof(Shape));
        }
    }
    array->values[array->count++] = value;
}

int main(void) {
    dynArray array = { NULL, 0, 0 };

    Shape square;
    square.type = SHAPE_SQUARE;
    square.data.square.side = 5.0;
    square.area = (void *)&squareArea;

    Shape rectangle;
    rectangle.type = SHAPE_RECTANGLE;
    rectangle.data.rectangle.length = 5.0;
    rectangle.data.rectangle.width = 10.0;
    rectangle.area = (void *)&rectangleArea;

    Shape circle;
    circle.type = SHAPE_CIRCLE;
    circle.data.circle.radius = 5.0;
    circle.area = (void *)&circleArea;

    append(&array, square);
    append(&array, rectangle);
    append(&array, circle);

    for (size_t i = 0; i < array.count; i++) {
        switch (array.values[i].type) {
            case SHAPE_SQUARE:
                printf("Square, area %f\n", array.values[i].area((void *)&array.values[i].data.square));
                break;
            case SHAPE_RECTANGLE:
                printf("Rectangle, area %f\n", array.values[i].area((void *)&array.values[i].data.rectangle));
                break;
            case SHAPE_CIRCLE:
                printf("Circle, area %f\n", array.values[i].area((void *)&array.values[i].data.circle));
                break;
        }
    }

    return 0;
}