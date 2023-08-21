//
// Created by Isabela Spinelli on 15/08/2023.
//
#pragma once

//I used constexpr because all constants have pre-established
//values while still in compilation-time,
//therefore they don't rely on changes during run-time.
constexpr unsigned char PixelBySquare = 16;

constexpr unsigned char line = 8;

constexpr unsigned char col = 8;

constexpr unsigned char resizeCam = 8;

constexpr unsigned char frameDuration = 16667;

constexpr unsigned char effectDuration = 16;

constexpr unsigned char fontHeight = 16;

constexpr unsigned char fontWidth = 8;

constexpr unsigned short MINES = 8;
