#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "vehicles.dat" // File to store vehicle data
typedef struct {
char name[50]; // Vehicle name
char type[20]; // Type of vehicle
float rental_price; // Rental price per day
int available; // Availability status (1 = available, 0 = rented)
} Vehicle;
Vehicle *vehicles = NULL; // Dynamic array for vehicles
int vehicle_count = 0; // Number of vehicles in the system
float total_revenue = 0; // Total revenue from rentals
// Function to save vehicle data to a file
void saveData() {
FILE *file = fopen(FILE_NAME, "wb");
if (!file) {
printf("Error saving data!\n");
return;
}
fwrite(&vehicle_count, sizeof(int), 1, file);
fwrite(vehicles, sizeof(Vehicle), vehicle_count, file);
fwrite(&total_revenue, sizeof(float), 1, file);
fclose(file);
}
// Function to load vehicle data from a file
void loadData() {
FILE *file = fopen(FILE_NAME, "rb");
if (!file) return;
fread(&vehicle_count, sizeof(int), 1, file);
vehicles = (Vehicle *)malloc(vehicle_count * sizeof(Vehicle));
fread(vehicles, sizeof(Vehicle), vehicle_count, file);
fread(&total_revenue, sizeof(float), 1, file);
fclose(file);
}
// Function to add a new vehicle
void addVehicle() {
vehicles = (Vehicle *)realloc(vehicles, (vehicle_count + 1) * sizeof(Vehicle));
printf("Enter vehicle name: ");
scanf("%s", vehicles[vehicle_count].name);
printf("Enter vehicle type: ");
scanf("%s", vehicles[vehicle_count].type);
printf("Enter rental price: ");
scanf("%f", &vehicles[vehicle_count].rental_price);
vehicles[vehicle_count].available = 1; // Set as available
vehicle_count++;
saveData(); // Save changes to file
printf("Vehicle added successfully!\n");
}
// Function to list all vehicles
void listVehicles() {
printf("\nAvailable Vehicles:\n");
for (int i = 0; i < vehicle_count; i++) {
printf("%d. %s (%s) - $%.2f per day - %s\n", i + 1, vehicles[i].name,
vehicles[i].type, vehicles[i].rental_price, vehicles[i].available ? "Available" : "Rented");
}
}
// Function to rent a vehicle
void rentVehicle() {
listVehicles();
printf("Enter vehicle number to rent: ");
int choice;
scanf("%d", &choice);
if (choice < 1 || choice > vehicle_count || !vehicles[choice - 1].available) {
printf("Invalid selection!\n");
return;
}
vehicles[choice - 1].available = 0; // Mark as rented
total_revenue += vehicles[choice - 1].rental_price; // Add to revenue
saveData(); // Save changes
printf("Vehicle rented successfully!\n");
}
// Function to return a rented vehicle
void returnVehicle() {
listVehicles();
printf("Enter vehicle number to return: ");
int choice;
scanf("%d", &choice);
if (choice < 1 || choice > vehicle_count || vehicles[choice - 1].available) {
printf("Invalid selection!\n");
return;
}
vehicles[choice - 1].available = 1; // Mark as available again
saveData(); // Save changes
printf("Vehicle returned successfully!\n");
}
// Function to display total rental revenue
void displayRevenue() {
printf("Total Rental Revenue: $%.2f\n", total_revenue);
}
int main() {
loadData(); // Load existing data from file
int choice;
while (1) {
// Display menu options
printf("\nVehicle Rental System\n");
printf("1. Add Vehicle\n2. List Vehicles\n3. Rent Vehicle\n4. Return Vehicle\n5.Show Revenue\n6. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1: addVehicle(); break;
case 2: listVehicles(); break;
case 3: rentVehicle(); break;
case 4: returnVehicle(); break;
case 5: displayRevenue(); break;
case 6: free(vehicles); exit(0); // Free memory and exit
default: printf("Invalid choice!\n");
}
}
return 0;
}