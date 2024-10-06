#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum VehicleType { CAR, BIKE, TRUCK };

class Vehicle {
public:
    string registrationNumber;
    string color;
    VehicleType type;

    Vehicle(string regNo, string col, VehicleType t) 
        : registrationNumber(regNo), color(col), type(t) {}
};

class ParkingSlot {
public:
    int slotNumber;
    bool isOccupied;
    VehicleType slotType;
    Vehicle* parkedVehicle;

    ParkingSlot(int number, VehicleType type)
        : slotNumber(number), isOccupied(false), slotType(type), parkedVehicle(nullptr) {}

    void parkVehicle(Vehicle* vehicle) {
        isOccupied = true;
        parkedVehicle = vehicle;
    }

    void unparkVehicle() {
        isOccupied = false;
        parkedVehicle = nullptr;
    }
};

class Floor {
public:
    int floorNumber;
    vector<ParkingSlot> slots;

    Floor(int floorNo, int totalSlots) : floorNumber(floorNo) {
        // First slot for truck, next 2 for bikes, remaining for cars
        for (int i = 1; i <= totalSlots; i++) {
            if (i == 1) {
                slots.push_back(ParkingSlot(i, TRUCK));
            } else if (i == 2 || i == 3) {
                slots.push_back(ParkingSlot(i, BIKE));
            } else {
                slots.push_back(ParkingSlot(i, CAR));
            }
        }
    }

    ParkingSlot* findFirstFreeSlot(VehicleType vehicleType) {
        for (auto& slot : slots) {
            if (!slot.isOccupied && slot.slotType == vehicleType) {
                return &slot;
            }
        }
        return nullptr;
    }
};

class ParkingLot {
public:
    string parkingLotId;
    vector<Floor> floors;

    ParkingLot(string id, int numberOfFloors, int slotsPerFloor)
        : parkingLotId(id) {
        for (int i = 1; i <= numberOfFloors; i++) {
            floors.push_back(Floor(i, slotsPerFloor));
        }
    }

    ParkingSlot* findAvailableSlot(VehicleType vehicleType) {
        for (auto& floor : floors) {
            ParkingSlot* freeSlot = floor.findFirstFreeSlot(vehicleType);
            if (freeSlot != nullptr) {
                return freeSlot;
            }
        }
        return nullptr;
    }

    void parkVehicle(Vehicle* vehicle) {
        ParkingSlot* slot = findAvailableSlot(vehicle->type);
        if (slot != nullptr) {
            slot->parkVehicle(vehicle);
            cout << "Parked vehicle. Ticket ID: " << parkingLotId << "_" << slot->slotNumber << endl;
        } else {
            cout << "Parking Lot Full" << endl;
        }
    }

    void unparkVehicle(int floorNo, int slotNo) {
        if (floorNo > 0 && floorNo <= floors.size()) {
            ParkingSlot& slot = floors[floorNo - 1].slots[slotNo - 1];
            if (slot.isOccupied) {
                Vehicle* vehicle = slot.parkedVehicle;
                cout << "Unparked vehicle with Registration Number: " << vehicle->registrationNumber << " and Color: " << vehicle->color << endl;
                slot.unparkVehicle();
            } else {
                cout << "Invalid Ticket" << endl;
            }
        } else {
            cout << "Invalid Floor or Slot" << endl;
        }
    }

    void displayFreeCount(VehicleType type) {
        for (auto& floor : floors) {
            int count = 0;
            for (auto& slot : floor.slots) {
                if (!slot.isOccupied && slot.slotType == type) {
                    count++;
                }
            }
            cout << "No. of free slots for " << (type == CAR ? "CAR" : (type == BIKE ? "BIKE" : "TRUCK")) 
                 << " on Floor " << floor.floorNumber << ": " << count << endl;
        }
    }

    void displayTotalFreeCount(){
        int cntCar = 0, cntBike = 0, cntTruck = 0;

        for(auto& floor : floors){
            
        }
    }
};



int main() {
    ParkingLot* parkingLot = nullptr;
    string command;
    cout << "\nWelcome to parking lot system\n";
    while (true) {
        cin >> command;

        if (command == "create_parking_lot") {
            cout << "Enter parking-lot id ,no. of floor ,no. of slot per floor\n";
            string id;
            int floors, slotsPerFloor;
            cin >> id >> floors >> slotsPerFloor;
            parkingLot = new ParkingLot(id, floors, slotsPerFloor);
            cout << "Created parking lot with " << floors << " floors and " << slotsPerFloor << " slots per floor" << endl;
        } else if (command == "park_vehicle") {
            cout << "Enter type (CAR , BIKE , TRUCK) register numer and color\n";
            string type, regNo, color;
            cin >> type >> regNo >> color;
            VehicleType vType = (type == "CAR") ? CAR : (type == "BIKE") ? BIKE : TRUCK;
            Vehicle* vehicle = new Vehicle(regNo, color, vType);
            parkingLot->parkVehicle(vehicle);
        } else if (command == "unpark_vehicle") {
            cout << "Give your ticket \n";
            string ticketID;
            cin >> ticketID;
            // Assuming ticket format: parkingLotId_floor_slot
            string lotId;
            int floorNo, slotNo;
            sscanf(ticketID.c_str(), "%*[^_]_%d_%d", &floorNo, &slotNo);
            parkingLot->unparkVehicle(floorNo, slotNo);
        } else if (command == "display") {
            cout << "display type (free_count) , and type of vehicle (CAR,BIKE,TRUCK)\n";
            string displayType, vehicleType;
            cin >> displayType >> vehicleType;
            VehicleType vType = (vehicleType == "CAR") ? CAR : (vehicleType == "BIKE") ? BIKE : TRUCK;

            if (displayType == "free_count") {
                parkingLot->displayFreeCount(vType);
            }
            // You can add similar handling for other display types like free_slots, occupied_slots
        } else if (command == "exit") {
            break;
        }
    }

    cout << "Programme Ended\n";

    return 0;
}
