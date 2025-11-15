// Tagged Union
#include <stdio.h>
#include <stdlib.h>

// Base types
typedef struct {
    double side;
} Square;

typedef struct {
    double length, width;
} Rectangle;

typedef struct {
    double radius;
} Circle;

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

    Shape rectangle;
    rectangle.type = SHAPE_RECTANGLE;
    rectangle.data.rectangle.length = 5.0;
    rectangle.data.rectangle.width = 10.0;

    Shape circle;
    circle.type = SHAPE_CIRCLE;
    circle.data.circle.radius = 5.0;

    append(&array, square);
    append(&array, rectangle);
    append(&array, circle);

    return 0;
}