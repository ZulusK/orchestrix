//
// Created by zulus on 29.04.17.
//

#include <math.h>
#include <progbase-cpp/console.h>
#include <ConsoleGraphic/GraphUtil.h>

void swap(double * a, double * b) {
    double t = *a;
    *a = *b;
    *b = t;
}

Vec2D Vec2D_multByNumber(Vec2D a, double number) {
    return (Vec2D){
            .x = a.x * number,
            .y = a.y * number
    };
}

Vec2D Vec2D_rotate(Vec2D self, double radians) {
    double ca = cosf(radians);
    double sa = sinf(radians);
    return (Vec2D) {
            .x = ca * self.x - sa * self.y,
            .y = sa * self.x + ca * self.y
    };
}

Vec2D Vec2D_normalize(Vec2D self) {
    double length = Vec2D_length(self);
    if (length == 0) return self;
    return Vec2D_multByNumber(self, 1.0 / length);
}

double Vec2D_length(Vec2D self) {
    return sqrt(self.x * self.x + self.y * self.y);
}

Vec2D Vec2D_add(Vec2D a, Vec2D b) {
    return (Vec2D){
            .x = a.x + b.x,
            .y = a.y + b.y
    };
}

Vec2D Vec2D_substract(Vec2D a, Vec2D b) {
    return (Vec2D){
            .x = a.x - b.x,
            .y = a.y - b.y
    };
}