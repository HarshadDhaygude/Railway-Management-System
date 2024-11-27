#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <ctime>

using namespace std;

// Structure to store train information
struct Train {
    string trainName;
    int trainNumber;
    string trainType; // "VIP" or "Normal"
    time_t arrivalTime;
};

// Class to simulate the platform management system
class RailwayPlatformManagement {
private:
    queue<Train> normalQueue;      // Queue for normal trains
    stack<Train> vipStack;         // Stack for VIP trains
    int availablePlatforms;        // Number of available platforms
    int platformCounter = 0;       // Platform allocation counter

public:
    RailwayPlatformManagement(int platforms) {
        availablePlatforms = platforms;
    }

    // Method to simulate a new train arrival
    void arriveTrain(string trainName, int trainNumber, string trainType) {
        Train newTrain;
        newTrain.trainName = trainName;
        newTrain.trainNumber = trainNumber;
        newTrain.trainType = trainType;
        newTrain.arrivalTime = time(0);  // Get the current time

        // If the train is VIP, push it to the VIP stack
        if (trainType == "VIP") {
            vipStack.push(newTrain);
            cout << "VIP Train " << trainName << " has arrived!" << endl;
        } else {
            normalQueue.push(newTrain);
            cout << "Normal Train " << trainName << " has arrived!" << endl;
        }
    }

    // Method to allocate a platform to a train
    void allocatePlatform() {
        if (!vipStack.empty()) {
            Train vipTrain = vipStack.top();
            vipStack.pop();
            platformCounter++;
            cout << "Allocated platform " << platformCounter << " to VIP Train " << vipTrain.trainName << endl;
        } else if (!normalQueue.empty()) {
            Train normalTrain = normalQueue.front();
            normalQueue.pop();
            platformCounter++;
            cout << "Allocated platform " << platformCounter << " to Normal Train " << normalTrain.trainName << endl;
        } else {
            cout << "No trains available for platform allocation!" << endl;
        }

        // Decrement available platforms
        availablePlatforms--;
    }

    // Method to release a platform
    void releasePlatform() {
        if (platformCounter > 0) {
            cout << "Platform " << platformCounter << " has been released." << endl;
            platformCounter--;
            availablePlatforms++;
        } else {
            cout << "No platforms to release!" << endl;
        }
    }

    // Display available platforms
    void displayAvailablePlatforms() {
        cout << "Available platforms: " << availablePlatforms << endl;
    }

    // Method to track real-time train information
    void trackTrains() {
        cout << "\nTrain Tracking Information:" << endl;
        cout << "============================" << endl;
        cout << "VIP Train Stack: " << vipStack.size() << " train(s)" << endl;
        cout << "Normal Train Queue: " << normalQueue.size() << " train(s)" << endl;
    }
};

int main() {
    // Initialize the platform manager with 5 available platforms
    RailwayPlatformManagement rpm(5);

    // Simulate train arrivals
    rpm.arriveTrain("Express 101", 101, "VIP");
    rpm.arriveTrain("Local 202", 202, "Normal");
    rpm.arriveTrain("Express 102", 102, "VIP");
    rpm.arriveTrain("Local 203", 203, "Normal");

    // Allocate platforms to trains
    rpm.allocatePlatform(); // Allocate platform to the first arriving train
    rpm.allocatePlatform(); // Allocate platform to the second arriving train
    rpm.allocatePlatform(); // Allocate platform to the third arriving train

    // Display available platforms
    rpm.displayAvailablePlatforms();

    // Track trains
    rpm.trackTrains();

    // Release a platform and reallocate
    rpm.releasePlatform();
    rpm.allocatePlatform();

    return 0;
}
