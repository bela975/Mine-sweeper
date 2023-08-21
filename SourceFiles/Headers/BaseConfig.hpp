//
// Created by Isabela Spinelli on 15/08/2023.
//
#pragma once

//I used constexpr because all constants have pre-established
//values while still in compilation-time,
//therefore they don't rely on changes during run-time.
constexpr unsigned char pixelBySquare = 16;

constexpr unsigned char lines = 8;

constexpr unsigned char col = 8;

constexpr unsigned char resizeScreen = 8;

constexpr unsigned char frameDuration = 166;

constexpr unsigned char effectDuration = 16;

constexpr unsigned char fontHeight = 16;

constexpr unsigned char fontWidth = 8;

constexpr unsigned short MINES = 8;
