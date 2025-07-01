#include "Car.h"
#include <iostream>
#include <iomanip>
#include <string>

// Function to print the car's status
void printCarStatus(const Car& car) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Current Speed: " << car.getSpeed() << " km/h" << std::endl;
    std::cout << "Current Gear: " << car.getGearAsString() << std::endl;
    
    Location currentLoc = car.getLocation();
    std::cout << "Current Location: (" << currentLoc.latitude << ", " 
              << currentLoc.longitude << ")" << std::endl;
    
    Location dest = car.getDestination();
    std::cout << "Destination: (" << dest.latitude << ", " 
              << dest.longitude << ")" << std::endl;
    
    double distance = Location::calculateDistance(currentLoc, dest);
    std::cout << "Distance to destination: " << distance << " km" << std::endl;
    
    double eta = car.timeToDestination();
    if (eta >= 0) {
        std::cout << "Estimated arrival time: " << eta / 60.0 << " minutes" << std::endl;
    } else {
        std::cout << "Cannot calculate arrival time at current speed" << std::endl;
    }
    
    std::cout << "Arrived at destination: " << (car.hasArrived() ? "Yes" : "No") << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

// Function to test all car functionality
void testCarFunctionality() {
    // Create a car at starting location
    Location startLocation = {40.7128, -74.0060}; // New York City coordinates
    Car myCar(startLocation);
    
    std::cout << "*** Initial Car Status ***" << std::endl;
    printCarStatus(myCar);
    
    // Set destination to Los Angeles
    Location destination = {34.0522, -118.2437}; // Los Angeles coordinates
    myCar.setDestination(destination);
    
    std::cout << "*** After Setting Destination ***" << std::endl;
    printCarStatus(myCar);
    
    // Try to accelerate in PARK
    std::cout << "Attempting to accelerate in PARK..." << std::endl;
    bool success = myCar.accelerate(10.0);
    std::cout << "Acceleration " << (success ? "successful" : "failed") << std::endl;
    printCarStatus(myCar);
    
    // Shift to DRIVE
    std::cout << "Shifting to DRIVE..." << std::endl;
    success = myCar.shiftGears(GearType::DRIVE);
    std::cout << "Gear shift " << (success ? "successful" : "failed") << std::endl;
    printCarStatus(myCar);
    
    // Accelerate to 100 km/h
    std::cout << "Accelerating to 100 km/h..." << std::endl;
    for (int i = 0; i < 10 && myCar.getSpeed() < 100.0; i++) {
        myCar.accelerate(10.0);
    }
    printCarStatus(myCar);
    
    // Drive for 1 hour
    std::cout << "Driving for 1 hour..." << std::endl;
    double remainingDistance = myCar.drive(3600.0);
    std::cout << "Remaining distance: " << remainingDistance << " km" << std::endl;
    printCarStatus(myCar);
    
    // Brake to reduce speed
    std::cout << "Applying brakes..." << std::endl;
    myCar.brake(50.0);
    printCarStatus(myCar);
    
    // Drive some more
    std::cout << "Driving for another 30 minutes..." << std::endl;
    remainingDistance = myCar.drive(1800.0);
    std::cout << "Remaining distance: " << remainingDistance << " km" << std::endl;
    printCarStatus(myCar);
    
    // Test full stop and gear change
    std::cout << "Coming to a complete stop..." << std::endl;
    while (myCar.getSpeed() > 0) {
        myCar.brake(20.0);
    }
    printCarStatus(myCar);
    
    // Try to shift to PARK
    std::cout << "Shifting to PARK..." << std::endl;
    success = myCar.shiftGears(GearType::PARK);
    std::cout << "Gear shift " << (success ? "successful" : "failed") << std::endl;
    printCarStatus(myCar);
    
    // Create a small test case to demonstrate arrival
    std::cout << "\n*** Testing arrival functionality ***" << std::endl;
    Location closeLocation = {34.0523, -118.2438}; // Very close to destination
    Car testCar(closeLocation);
    testCar.setDestination(destination);
    
    std::cout << "Initial status (close to destination):" << std::endl;
    printCarStatus(testCar);
    
    std::cout << "Shifting to DRIVE..." << std::endl;
    testCar.shiftGears(GearType::DRIVE);
    
    std::cout << "Accelerating..." << std::endl;
    testCar.accelerate(5.0);
    
    std::cout << "Driving for a short time..." << std::endl;
    testCar.drive(10.0);
    
    std::cout << "Final status:" << std::endl;
    printCarStatus(testCar);
}

int main() {
    std::cout << "=== C++ Car Functionality System Test ===" << std::endl;
    testCarFunctionality();
    return 0;
}