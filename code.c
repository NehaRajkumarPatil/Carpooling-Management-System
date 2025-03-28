#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEHICLES 100
#define MAX_COMMUTERS 100
#define MAX_REQUESTS 100

typedef struct {
    int id;
    char owner_name[50];
    char vehicle_type[30];
    float ride_cost_per_km;
    int seats_available;
    char availability_time[20];
} Vehicle;

typedef struct {
    int id;
    char name[50];
    char start_location[50];
    char end_location[50];
    float trip_cost;
    int payment_status;  // 0 - Not Paid, 1 - Paid
} Commuter;

typedef struct {
    int id;
    int vehicle_id;
    int commuter_id;
    char start_location[50];
    char end_location[50];
    char status[20];  // "Pending", "Approved", "Rejected"
} Request;

Vehicle vehicles[MAX_VEHICLES];
Commuter commuters[MAX_COMMUTERS];
Request requests[MAX_REQUESTS];

int num_vehicles = 0, num_commuters = 0, num_requests = 0;

/* Function Prototypes */
void loadVehicles();
void saveVehicles();
void addVehicle();
void displayVehicles();

void loadCommuters();
void saveCommuters();
void addCommuter();
void displayCommuters();
void updatePaymentStatus(int commuter_id);

void loadRequests();
void saveRequests();
void addRequest();
void displayRequests();
void approveRequest(int request_id);
void rejectRequest(int request_id);

/* ----------------- VEHICLE MANAGEMENT ----------------- */
void loadVehicles() {
    FILE *fp = fopen("vehicles.dat", "rb");
    if (fp == NULL) return;
    fread(&num_vehicles, sizeof(int), 1, fp);
    fread(vehicles, sizeof(Vehicle), num_vehicles, fp);
    fclose(fp);
}

void saveVehicles() {
    FILE *fp = fopen("vehicles.dat", "wb");
    if (fp == NULL) {
        printf("Error saving vehicles!\n");
        return;
    }
    fwrite(&num_vehicles, sizeof(int), 1, fp);
    fwrite(vehicles, sizeof(Vehicle), num_vehicles, fp);
    fclose(fp);
}

void addVehicle() {
    if (num_vehicles >= MAX_VEHICLES) {
        printf("Vehicle limit reached!\n");
        return;
    }
    
    Vehicle v;
    v.id = num_vehicles + 1;
    printf("Enter Owner Name: ");
    scanf(" %[^\n]", v.owner_name);
    printf("Enter Vehicle Type: ");
    scanf(" %[^\n]", v.vehicle_type);
    printf("Enter Ride Cost per KM: ");
    scanf("%f", &v.ride_cost_per_km);
    printf("Enter Seats Available: ");
    scanf("%d", &v.seats_available);
    printf("Enter Availability Time: ");
    scanf(" %[^\n]", v.availability_time);
    
    vehicles[num_vehicles++] = v;
    saveVehicles();
    printf("Vehicle Added Successfully!\n");
}

void displayVehicles() {
    printf("\n----- Available Vehicles -----\n");
    for (int i = 0; i < num_vehicles; i++) {
        printf("ID: %d | Owner: %s | Type: %s | Cost/KM: %.2f | Seats: %d | Time: %s\n",
               vehicles[i].id, vehicles[i].owner_name, vehicles[i].vehicle_type,
               vehicles[i].ride_cost_per_km, vehicles[i].seats_available, vehicles[i].availability_time);
    }
}

/* ----------------- COMMUTER MANAGEMENT ----------------- */
void loadCommuters() {
    FILE *fp = fopen("commuters.dat", "rb");
    if (fp == NULL) return;
    fread(&num_commuters, sizeof(int), 1, fp);
    fread(commuters, sizeof(Commuter), num_commuters, fp);
    fclose(fp);
}

void saveCommuters() {
    FILE *fp = fopen("commuters.dat", "wb");
    if (fp == NULL) return;
    fwrite(&num_commuters, sizeof(int), 1, fp);
    fwrite(commuters, sizeof(Commuter), num_commuters, fp);
    fclose(fp);
}

void addCommuter() {
    if (num_commuters >= MAX_COMMUTERS) {
        printf("Commuter limit reached!\n");
        return;
    }
    
    Commuter c;
    c.id = num_commuters + 1;
    printf("Enter Commuter Name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter Start Location: ");
    scanf(" %[^\n]", c.start_location);
    printf("Enter End Location: ");
    scanf(" %[^\n]", c.end_location);
    printf("Enter Trip Cost: ");
    scanf("%f", &c.trip_cost);
    c.payment_status = 0;
    
    commuters[num_commuters++] = c;
    saveCommuters();
    printf("Commuter Added Successfully!\n");
}

void displayCommuters() {
    printf("\n----- Registered Commuters -----\n");
    for (int i = 0; i < num_commuters; i++) {
        printf("ID: %d | Name: %s | From: %s | To: %s | Cost: %.2f | Paid: %s\n",
               commuters[i].id, commuters[i].name, commuters[i].start_location, commuters[i].end_location,
               commuters[i].trip_cost, (commuters[i].payment_status ? "Yes" : "No"));
    }
}

void updatePaymentStatus(int commuter_id) {
    for (int i = 0; i < num_commuters; i++) {
        if (commuters[i].id == commuter_id) {
            commuters[i].payment_status = 1;
            saveCommuters();
            printf("Payment updated successfully!\n");
            return;
        }
    }
    printf("Commuter ID not found!\n");
}

/* ----------------- REQUEST MANAGEMENT ----------------- */
void loadRequests() {
    FILE *fp = fopen("requests.dat", "rb");
    if (fp == NULL) return;
    fread(&num_requests, sizeof(int), 1, fp);
    fread(requests, sizeof(Request), num_requests, fp);
    fclose(fp);
}

void saveRequests() {
    FILE *fp = fopen("requests.dat", "wb");
    if (fp == NULL) return;
    fwrite(&num_requests, sizeof(int), 1, fp);
    fwrite(requests, sizeof(Request), num_requests, fp);
    fclose(fp);
}

void addRequest() {
    if (num_requests >= MAX_REQUESTS) {
        printf("Request limit reached!\n");
        return;
    }
    
    Request r;
    r.id = num_requests + 1;
    printf("Enter Vehicle ID: ");
    scanf("%d", &r.vehicle_id);
    printf("Enter Commuter ID: ");
    scanf("%d", &r.commuter_id);
    strcpy(r.status, "Pending");

    requests[num_requests++] = r;
    saveRequests();
    printf("Request Added Successfully!\n");
}

void displayRequests() {
    printf("\n----- Ride Requests -----\n");
    for (int i = 0; i < num_requests; i++) {
        printf("ID: %d | Vehicle ID: %d | Commuter ID: %d | Status: %s\n",
               requests[i].id, requests[i].vehicle_id, requests[i].commuter_id, requests[i].status);
    }
}

int main() {
    loadVehicles();
    loadCommuters();
    loadRequests();
    addVehicle(); // Example Usage
    displayVehicles();
    return 0;
}
