//
// Created by zulus on 29.04.17.
//

#ifndef THREADS_GARPHICS_H
#define THREADS_GARPHICS_H
#pragma once

typedef struct Graphics Graphics;

typedef struct Vec2D Vec2D;
struct Vec2D {
    double x;
    double y;
};

void swap(double *a, double *b);

Vec2D Vec2D_normalize(Vec2D self);

Vec2D Vec2D_rotate(Vec2D self, double radians);

Vec2D Vec2D_multByNumber(Vec2D a, double number);

double Vec2D_length(Vec2D self);

Vec2D Vec2D_substract(Vec2D a, Vec2D b);

Vec2D Vec2D_add(Vec2D a, Vec2D b);

#endif //THREADS_GARPHICS_H
