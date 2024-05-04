#pragma once
#include "VectorN.h"

static const char kWindowTitle[] = "TR1_FFT";
static const int kWindowSizeX = 1280;
static const int kWindowSizeY = 720;
static Vec2 windowCenter = { float(kWindowSizeX) * 0.5f, float(kWindowSizeY) * 0.5f };
static Vec2 canvasSize = {
float(kWindowSizeY) * 0.8f,
float(kWindowSizeY) * 0.8f
};
static Vec2 windowLT = windowCenter - (canvasSize * 0.5f);
static Vec2 windowRB = windowCenter + (canvasSize * 0.5f);