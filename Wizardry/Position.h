//
//  Position.h
//  Wizardry
//
//  Created by Mustafa Camurcu on 1/10/17.
//  Copyright © 2017 Mustafa Camurcu. All rights reserved.
//

#ifndef Position_h
#define Position_h

#include <set>
#include "Env.h"

class Position {
public:
    /**
     * Construct a 0 Position
     */
    Position();
    /**
     * Construct a Position
     */
    Position(double xx, double yy);
    /*X Coordinate*/
    double x;
    /*Y Coordinate*/
    double y;
    /**
     * find the distance between this and other positions
     * @param other, the other position
     * @return distance to the other Position
     */
    double dist(Position other);
    /**
     * move this position with the given details
     * @param dirs, directions to move to
     * @param speed, speed
     * @param dt, time passed
     */
    void move(std::set<Dir> dirs, double speed, double dt);
};


#endif /* Position_h */
