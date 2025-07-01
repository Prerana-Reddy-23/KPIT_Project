#ifndef CAR_H
#define CAR_H

#include <string>
#include <cmath>

enum class GearType {
    PARK,
    REVERSE,
    NEUTRAL,
    DRIVE
};

struct Location {
    double latitude;
    double longitude;

    // Calculate distance between two locations using Haversine formula
    static double calculateDistance(const Location& loc1, const Location& loc2) {
        const double earthRadius = 6371.0; // Earth radius in kilometers
        double lat1Rad = loc1.latitude * M_PI / 180.0;
        double lat2Rad = loc2.latitude * M_PI / 180.0;
        double deltaLat = (loc2.latitude - loc1.latitude) * M_PI / 180.0;
        double deltaLon = (loc2.longitude - loc1.longitude) * M_PI / 180.0;

        double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
                   cos(lat1Rad) * cos(lat2Rad) *
                   sin(deltaLon / 2) * sin(deltaLon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(sqrt(1 - a)));
        return earthRadius * c;
    }

    // Check if two locations are approximately equal (within a small distance)
    bool isApproximatelyEqual(const Location& other, double threshold = 0.01) const {
        return calculateDistance(*this, other) < threshold;
    }
};

class Car {
private:
    GearType currentGear;
    double currentSpeed; // in kilometers per hour
    Location currentLocation;
    Location destination;
    double maxSpeed; // maximum speed in km/h
    double maxAcceleration; // maximum acceleration rate in km/h/s
    double maxBrakeForce; // maximum braking force in km/h/s

public:
    // Constructor
    Car(const Location& startLocation, double maxSpd = 200.0, 
        double maxAccel = 10.0, double maxBrake = 20.0);
    
    // Accelerate function
    bool accelerate(double accelerationValue);
    
    // Brake function
    bool brake(double brakeForce);
    
    // Shift Gears function
    bool shiftGears(GearType newGear);
    
    // Get Gear State function
    GearType getGearState() const;
    
    // Get Speed function
    double getSpeed() const;
    
    // Get Location function
    Location getLocation() const;
    
    // Get Destination function
    Location getDestination() const;
    
    // Set Destination function
    void setDestination(const Location& dest);
    
    // Drive function
    double drive(double timeInSeconds);
    
    // Time to Destination function
    double timeToDestination() const;
    
    // Has Arrived function
    bool hasArrived() const;
    
    // Get gear as string for display
    std::string getGearAsString() const;
};

#endif // CAR_H