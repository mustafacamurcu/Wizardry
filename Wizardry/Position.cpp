//
//  Position.cpp
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#include "Position.h"
#include <iostream>
#include <cmath>

Position::Position() {
    x = 0.0;
    y = 0.0;
}

Position::Position(double xx, double yy) {
    x = xx;
    y = yy;
}

double Position::dist(Position other) {
    return sqrt((x - other.x)*(x - other.x)+(y - other.y)*(y - other.y));
}

void Position::move(std::set<Dir> dirs, double speed, double dt) {
    if( dirs.count(North) && y - dt * speed > 0) {
        y -= dt * speed;
    }
    if( dirs.count(South) && y + dt * speed < Env::SCREEN_HEIGHT ) {
        y += speed * dt;
    }
    if( dirs.count(East) && x + dt * speed < Env::SCREEN_WIDTH ) {
        x += speed * dt;
    }
    if( dirs.count(West) && x - dt * speed > 0 ) {
        x -= speed * dt;
    }
}