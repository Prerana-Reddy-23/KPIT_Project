#include "Car.h"
#include <stdexcept>
#include <iostream>

Car::Car(const Location& startLocation, double maxSpd, double maxAccel, double maxBrake)
    : currentGear(GearType::PARK),
      currentSpeed(0.0),
      currentLocation(startLocation),
      destination(startLocation),  // Initially set destination to current location
      maxSpeed(maxSpd),
      maxAcceleration(maxAccel),
      maxBrakeForce(maxBrake) {
}

bool Car::accelerate(double accelerationValue) {
    // Can only accelerate in DRIVE or REVERSE gear
    if (currentGear != GearType::DRIVE && currentGear != GearType::REVERSE) {
        return false;
    }
    
    // Limit acceleration to maximum value
    if (accelerationValue > maxAcceleration) {
        accelerationValue = maxAcceleration;
    }
    
    // Calculate new speed
    double newSpeed = currentSpeed + accelerationValue;
    
    // Limit speed based on gear and max speed
    if (currentGear == GearType::DRIVE) {
        if (newSpeed > maxSpeed) {
            newSpeed = maxSpeed;
        }
    } else if (currentGear == GearType::REVERSE) {
        // Reverse speed is typically limited to a lower value, e.g., 20% of max speed
        if (newSpeed > maxSpeed * 0.2) {
            newSpeed = maxSpeed * 0.2;
        }
    }
    
    // Update speed
    currentSpeed = newSpeed;
    return true;
}

bool Car::brake(double brakeForce) {
    // Limit brake force to maximum value
    if (brakeForce > maxBrakeForce) {
        brakeForce = maxBrakeForce;
    }
    
    // Calculate new speed
    double newSpeed = currentSpeed - brakeForce;
    
    // Ensure speed doesn't go below 0
    if (newSpeed < 0) {
        newSpeed = 0;
    }
    
    // Update speed
    currentSpeed = newSpeed;
    return true;
}

bool Car::shiftGears(GearType newGear) {
    // Can only shift gears when speed is 0
    if (currentSpeed > 0) {
        return false;
    }
    
    currentGear = newGear;
    return true;
}

GearType Car::getGearState() const {
    return currentGear;
}

double Car::getSpeed() const {
    return currentSpeed;
}

Location Car::getLocation() const {
    return currentLocation;
}

Location Car::getDestination() const {
    return destination;
}

void Car::setDestination(const Location& dest) {
    destination = dest;
}

double Car::drive(double timeInSeconds) {
    // Can only drive in DRIVE or REVERSE gear and if speed > 0
    if ((currentGear != GearType::DRIVE && currentGear != GearType::REVERSE) || currentSpeed <= 0) {
        return Location::calculateDistance(currentLocation, destination);
    }
    
    // Convert time from seconds to hours
    double timeInHours = timeInSeconds / 3600.0;
    
    // Calculate distance traveled
    double distanceTraveled = currentSpeed * timeInHours;
    
    // Calculate direction vector
    double totalDistance = Location::calculateDistance(currentLocation, destination);
    
    // If already at destination or very close, no need to move
    if (totalDistance < 0.0001) {
        return 0.0;
    }
    
    // Calculate the ratio of distance traveled to total distance
    double ratio = distanceTraveled / totalDistance;
    
    // If we would travel past the destination, limit to destination
    if (ratio > 1.0) {
        ratio = 1.0;
    }
    
    // Calculate new location
    Location newLocation;
    newLocation.latitude = currentLocation.latitude + 
                           ratio * (destination.latitude - currentLocation.latitude);
    newLocation.longitude = currentLocation.longitude + 
                            ratio * (destination.longitude - currentLocation.longitude);
    
    // Update current location
    currentLocation = newLocation;
    
    // Return remaining distance
    return Location::calculateDistance(currentLocation, destination);
}

double Car::timeToDestination() const {
    // If speed is 0, cannot calculate time to destination
    if (currentSpeed <= 0) {
        return -1.0; // Indicate cannot reach destination at current speed
    }
    
    // Calculate distance to destination
    double distance = Location::calculateDistance(currentLocation, destination);
    
    // Calculate time in hours
    double timeInHours = distance / currentSpeed;
    
    // Convert to seconds
    return timeInHours * 3600.0;
}

bool Car::hasArrived() const {
    return currentLocation.isApproximatelyEqual(destination);
}

std::string Car::getGearAsString() const {
    switch (currentGear) {
        case GearType::PARK:
            return "PARK";
        case GearType::REVERSE:
            return "REVERSE";
        case GearType::NEUTRAL:
            return "NEUTRAL";
        case GearType::DRIVE:
            return "DRIVE";
        default:
            return "UNKNOWN";
    }
}