#include <iostream>
#include <main.h>
#include <util.h>

using namespace std;

// ================================================= AUTH
bool authFunction(string username, string password, string type,
                  char usernames[][10], char passwords[][10], int size) {
  for (int i = 0; i < size; i++) {
    if (username == usernames[i] && password == passwords[i]) {
      return true;
    }
  }

  return false;
}
// ================================================= AUTH

// ================================================= OWNER

const int MAX_SUPPLIERS = 100;
const int MAX_DISTRIBUTIONS = 100;

int supplierIds[MAX_SUPPLIERS];
string supplierNames[MAX_SUPPLIERS];
int supplierSupplyAmounts[MAX_SUPPLIERS];
int supplierCount = 0;

char distributionGrades[MAX_DISTRIBUTIONS];
int distributionQuantities[MAX_DISTRIBUTIONS];
string distributionDestinations[MAX_DISTRIBUTIONS];
int distributionCount = 0;

void addSupplier() {
  if (supplierCount >= MAX_SUPPLIERS) {
    cout << "Supplier list is full.\n";
    return;
  }
  cout << "Enter Supplier ID: ";
  cin >> supplierIds[supplierCount];
  cout << "Enter Supplier Name: ";
  cin >> supplierNames[supplierCount];
  cout << "Enter Supply Amount: ";
  cin >> supplierSupplyAmounts[supplierCount];
  supplierCount++;
  cout << "Supplier added successfully.\n";
}

void viewSupplierHistory() {
  for (int i = 0; i < supplierCount; i++) {
    cout << "ID: " << supplierIds[i] << ", Name: " << supplierNames[i]
         << ", Supply Amount: " << supplierSupplyAmounts[i] << endl;
  }
}

void addDistribution() {
  if (distributionCount >= MAX_DISTRIBUTIONS) {
    cout << "Distribution list is full.\n";
    return;
  }
  cout << "Enter Grade (A/B/C): ";
  cin >> distributionGrades[distributionCount];
  cout << "Enter Quantity: ";
  cin >> distributionQuantities[distributionCount];
  cout << "Enter Destination: ";
  cin >> distributionDestinations[distributionCount];
  distributionCount++;
  cout << "Distribution recorded successfully.\n";
}

void viewDistributionHistory() {
  for (int i = 0; i < distributionCount; i++) {
    cout << "Grade: " << distributionGrades[i]
         << ", Quantity: " << distributionQuantities[i]
         << ", Destination: " << distributionDestinations[i] << endl;
  }
}

int handleOwner(void) {

  // LOGIN SYSTEM
  // =================================================================================
  string usernameInput;
  string passwordInput;

  char ownerUsername[][10] = {
      "admin",
      "owner",
  };

  char ownerPassword[][10] = {
      "admin",
      "owner",
  };

  bool isLoginValid = false;
  int loginAttempt = 0;
  do {
    cout << "Username: ";
    cin >> usernameInput;
    cout << "Password: ";
    cin >> passwordInput;

    isLoginValid = authFunction(
        usernameInput, passwordInput, "owner", ownerUsername, ownerPassword,
        sizeof(ownerUsername) / sizeof(ownerUsername[0]));

    if (!isLoginValid) {
      cout << "Invalid username or password. Please try again.\n";
    }

    loginAttempt++;
    if (loginAttempt >= 3) {
      cout << "Too many login attempts. Exiting...\n";
      return 0;
    }

  } while (!isLoginValid);

  cout << "Login successful!\n";

  // MENU SYSTEM
  // =================================================================================
  int menuChoice;
  do {
    cout << "\nOwner Menu:\n";
    cout << "1. Quality Control\n";
    cout << "2. Supply Management\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> menuChoice;

    char eggGrade[] = {'A', 'B', 'C'};
    int eggQuantity[] = {0, 0, 0};

    if (menuChoice == 1) {

      int stockChoice;
      do {
        cout << "\nQuality Control Menu:\n";
        cout << "1. Insert Stock\n";
        cout << "2. View Stock\n";
        cout << "3. Back to Owner Menu\n";
        cout << "Enter your choice: ";
        cin >> stockChoice;

        if (stockChoice == 1) {
          char eggGradeChoice;
          int eggQuantityChoice;

          cout << "Masukkan Grade Egg (A/B/C): ";
          cin >> eggGradeChoice;

          cout << "Masukkan Quantity Egg: ";
          cin >> eggQuantityChoice;

          eggGradeChoice = toupper(eggGradeChoice);
          if (eggGradeChoice == 'A') {
            eggQuantity[0] += eggQuantityChoice;
            continue;
          }
          if (eggGradeChoice == 'B') {
            eggQuantity[1] += eggQuantityChoice;
            continue;
          }
          if (eggGradeChoice == 'C') {
            eggQuantity[2] += eggQuantityChoice;
            continue;
          }

          cout << "Invalid egg grade. Please enter A, B, or C.\n";
        } else if (stockChoice == 2) {
          cout << "Stock:\n";
          cout << "A: " << eggQuantity[0] << endl;
          cout << "B: " << eggQuantity[1] << endl;
          cout << "C: " << eggQuantity[2] << endl;
        } else if (stockChoice == 3) {
          break;
        } else {
          cout << "Invalid choice. Please try again.\n";
        }
      } while (true);
    }

    if (menuChoice == 2) {
      int supplyChoice;
      do {
        cout << "\nSupply Management Menu:\n";
        cout << "1. Supplier Control\n";
        cout << "2. Distribution\n";
        cout << "3. Back to Owner Menu\n";
        cout << "Enter your choice: ";
        cin >> supplyChoice;

        if (supplyChoice == 1) {
          int supplierChoice;
          do {
            cout << "\nSupplier Control Menu:\n";
            cout << "1. Add Supplier\n";
            cout << "2. View Supplier History\n";
            cout << "3. Back to Supply Management Menu\n";
            cout << "Enter your choice: ";
            cin >> supplierChoice;

            if (supplierChoice == 1) {
              addSupplier();
            } else if (supplierChoice == 2) {
              viewSupplierHistory();
            } else if (supplierChoice == 3) {
              break;
            } else {
              cout << "Invalid choice. Please try again.\n";
            }
          } while (true);
        } else if (supplyChoice == 2) {
          int distributionChoice;
          do {
            cout << "\nDistribution Menu:\n";
            cout << "1. Add Distribution\n";
            cout << "2. View Distribution History\n";
            cout << "3. Back to Supply Management Menu\n";
            cout << "Enter your choice: ";
            cin >> distributionChoice;

            if (distributionChoice == 1) {
              addDistribution();
            } else if (distributionChoice == 2) {
              viewDistributionHistory();
            } else if (distributionChoice == 3) {
              break;
            } else {
              cout << "Invalid choice. Please try again.\n";
            }
          } while (true);
        } else if (supplyChoice == 3) {
          break;
        } else {
          cout << "Invalid choice. Please try again.\n";
        }
      } while (true);
    }

  } while (menuChoice != 3);

  cout << "Exiting Owner Menu\n";

  return 0;
}

// ================================================= OWNER

// ================================================= STAFF

const int MAX_RECEIVING = 100;
const int MAX_SORTING = 100;

// Add these arrays for receiving management
int receivingSupplierIds[MAX_RECEIVING];
int receivingQuantities[MAX_RECEIVING];
string receivingDates[MAX_RECEIVING];
int receivingCount = 0;

// Add these arrays for sorting management
string sortingBatchIds[MAX_SORTING];
int sortingGradeA[MAX_SORTING];
int sortingGradeB[MAX_SORTING];
int sortingGradeC[MAX_SORTING];
int sortingCount = 0;

// Add total stock variable
int totalStock = 0;

// Add after other constants
const int MAX_STORAGE = 100;
const int MAX_SHIPMENT = 100;
const int MAX_RACKS = 10;

// Add after other global arrays
string storageBatchIds[MAX_STORAGE];
int storageRackNumbers[MAX_STORAGE];
int storageCount = 0;

// Storage content per rack (simplified to store total eggs per grade)
int rackGradeA[MAX_RACKS] = {0};
int rackGradeB[MAX_RACKS] = {0};
int rackGradeC[MAX_RACKS] = {0};

// Shipment records
string shipmentIds[MAX_SHIPMENT];
int shipmentGradeA[MAX_SHIPMENT];
int shipmentGradeB[MAX_SHIPMENT];
int shipmentGradeC[MAX_SHIPMENT];
string shipmentDates[MAX_SHIPMENT];
int shipmentCount = 0;

// Add these functions before handleStaff
void receiveEggs() {
    if (receivingCount >= MAX_RECEIVING) {
        cout << "Receiving record is full.\n";
        return;
    }

    cout << "Enter Supplier ID: ";
    cin >> receivingSupplierIds[receivingCount];
    cout << "Enter Total Quantity: ";
    cin >> receivingQuantities[receivingCount];
    cout << "Enter Receive Date (DD/MM/YYYY): ";
    cin >> receivingDates[receivingCount];

    totalStock += receivingQuantities[receivingCount];
    receivingCount++;
    cout << "Eggs received successfully.\n";
}

void viewTotalStock() {
    cout << "Total available stock: " << totalStock << " eggs\n";
}

void inputSorting() {
    if (sortingCount >= MAX_SORTING) {
        cout << "Sorting record is full.\n";
        return;
    }

    cout << "Enter Batch ID: ";
    cin >> sortingBatchIds[sortingCount];
    cout << "Enter quantity for Grade A: ";
    cin >> sortingGradeA[sortingCount];
    cout << "Enter quantity for Grade B: ";
    cin >> sortingGradeB[sortingCount];
    cout << "Enter quantity for Grade C: ";
    cin >> sortingGradeC[sortingCount];

    sortingCount++;
    cout << "Sorting results recorded successfully.\n";
}

void showGradingGuide() {
    cout << "\nEgg Grading Guide:\n";
    cout << "Grade A: Clean, perfect shape, weight 65-70g\n";
    cout << "Grade B: Slightly imperfect shape, weight 60-65g\n";
    cout << "Grade C: Irregular shape, weight below 60g\n";
}

void recordBatchLocation() {
    if (storageCount >= MAX_STORAGE) {
        cout << "Storage record is full.\n";
        return;
    }

    cout << "Enter Batch ID: ";
    cin >> storageBatchIds[storageCount];

    int rackNum;
    cout << "Enter Rack Number (1-" << MAX_RACKS << "): ";
    cin >> rackNum;

    if (rackNum < 1 || rackNum > MAX_RACKS) {
        cout << "Invalid rack number.\n";
        return;
    }

    storageRackNumbers[storageCount] = rackNum;

    int gradeA, gradeB, gradeC;
    cout << "Enter quantity for Grade A: ";
    cin >> gradeA;
    cout << "Enter quantity for Grade B: ";
    cin >> gradeB;
    cout << "Enter quantity for Grade C: ";
    cin >> gradeC;

    rackGradeA[rackNum-1] += gradeA;
    rackGradeB[rackNum-1] += gradeB;
    rackGradeC[rackNum-1] += gradeC;

    storageCount++;
    cout << "Batch location recorded successfully.\n";
}

void viewRackContents() {
    cout << "\nRack Contents:\n";
    for (int i = 0; i < MAX_RACKS; i++) {
        cout << "Rack " << (i+1) << ":\n";
        cout << "  Grade A: " << rackGradeA[i] << " eggs\n";
        cout << "  Grade B: " << rackGradeB[i] << " eggs\n";
        cout << "  Grade C: " << rackGradeC[i] << " eggs\n";
        cout << "------------------------\n";
    }
}

void printShipmentNote(int index) {
    cout << "\n====== SHIPMENT NOTE ======\n";
    cout << "Shipment ID: " << shipmentIds[index] << endl;
    cout << "Date: " << shipmentDates[index] << endl;
    cout << "\nQuantities:\n";
    cout << "Grade A: " << shipmentGradeA[index] << " eggs\n";
    cout << "Grade B: " << shipmentGradeB[index] << " eggs\n";
    cout << "Grade C: " << shipmentGradeC[index] << " eggs\n";
    cout << "Total: " << (shipmentGradeA[index] + shipmentGradeB[index] + shipmentGradeC[index]) << " eggs\n";
    cout << "========================\n";
}

void prepareShipment() {
    if (shipmentCount >= MAX_SHIPMENT) {
        cout << "Shipment record is full.\n";
        return;
    }

    cout << "Enter Shipment ID: ";
    cin >> shipmentIds[shipmentCount];

    cout << "Enter Grade A quantity: ";
    cin >> shipmentGradeA[shipmentCount];
    cout << "Enter Grade B quantity: ";
    cin >> shipmentGradeB[shipmentCount];
    cout << "Enter Grade C quantity: ";
    cin >> shipmentGradeC[shipmentCount];

    cout << "Enter Shipment Date (DD/MM/YYYY): ";
    cin >> shipmentDates[shipmentCount];

    printShipmentNote(shipmentCount);
    shipmentCount++;
}


int handleStaff(void) {

  // LOGIN SYSTEM
  // =================================================================================
  string usernameInput;
  string passwordInput;

  char staffUsername[][10] = {
      "staff1",
      "staff2",
  };
  char staffPassword[][10] = {
      "staff1",
      "staff2",
  };

  bool isLoginValid = false;
  int loginAttempt = 0;
  do {
    cout << "Username: ";
    cin >> usernameInput;
    cout << "Password: ";
    cin >> passwordInput;

    isLoginValid = authFunction(
        usernameInput, passwordInput, "staff", staffUsername, staffPassword,
        sizeof(staffUsername) / sizeof(staffUsername[0]));

    if (!isLoginValid) {
      cout << "Invalid username or password. Please try again.\n";
    }

    loginAttempt++;
    if (loginAttempt >= 3) {
      cout << "Too many login attempts. Exiting...\n";
      return 0;
    }

  } while (!isLoginValid);

  cout << "Login successful!\n";

  // MENU SYSTEM
  // =================================================================================
  int menuChoice;
  do {
    cout << "\nStaff Menu:\n";
    cout << "1. Receiving Management\n";
    cout << "2. Storage Operation\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> menuChoice;

    if (menuChoice == 1) {
      int receivingChoice;
      do {
        cout << "\nReceiving Management Menu:\n";
        cout << "1. Egg Reception\n";
        cout << "2. Sorting\n";
        cout << "3. Back to Staff Menu\n";
        cout << "Enter your choice: ";
        cin >> receivingChoice;

        if (receivingChoice == 1) {
          int eggReceptionChoice;
          do {
            cout << "\nEgg Reception Menu:\n";
            cout << "1. Input Received Eggs\n";
            cout << "2. View Total Stock\n";
            cout << "3. Back to Receiving Management\n";
            cout << "Enter your choice: ";
            cin >> eggReceptionChoice;

            if (eggReceptionChoice == 1) {
              receiveEggs();
            } else if (eggReceptionChoice == 2) {
              viewTotalStock();
            } else if (eggReceptionChoice == 3) {
              break;
            } else {
              cout << "Invalid choice. Please try again.\n";
            }
          } while (true);
        } else if (receivingChoice == 2) {
          int sortingChoice;
          do {
            cout << "\nSorting Menu:\n";
            cout << "1. Input Sorting Results\n";
            cout << "2. View Grading Guide\n";
            cout << "3. Back to Receiving Management\n";
            cout << "Enter your choice: ";
            cin >> sortingChoice;

            if (sortingChoice == 1) {
              inputSorting();
            } else if (sortingChoice == 2) {
              showGradingGuide();
            } else if (sortingChoice == 3) {
              break;
            } else {
              cout << "Invalid choice. Please try again.\n";
            }
          } while (true);
        } else if (receivingChoice == 3) {
          break;
        } else {
          cout << "Invalid choice. Please try again.\n";
        }
      } while (true);
    }

    if (menuChoice == 2) {
        int storageChoice;
        do {
            cout << "\nStorage Operation Menu:\n";
            cout << "1. Record Batch Location\n";
            cout << "2. View Rack Contents\n";
            cout << "3. Prepare Shipment\n";
            cout << "4. Back to Staff Menu\n";
            cout << "Enter your choice: ";
            cin >> storageChoice;

            if (storageChoice == 1) {
                recordBatchLocation();
            } else if (storageChoice == 2) {
                viewRackContents();
            } else if (storageChoice == 3) {
                prepareShipment();
            } else if (storageChoice == 4) {
                break;
            } else {
                cout << "Invalid choice. Please try again.\n";
            }
        } while (true);
    }

  } while (menuChoice != 3);

  cout << "Exiting Staff Menu\n";

  return 0;
}

// ================================================= STAFF

int main(void) {
  bool continueLogin = true;
  char continueLoginInput;

  while (continueLogin) {
    cout << "Select login type:\n";
    cout << "1. Owner\n";
    cout << "2. Staff\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    if (choice != 1 && choice != 2) {
      cout << "Invalid choice. Please try again.\n";
      continue;
    }

    if (choice == 1) {
      handleOwner();
    } else if (choice == 2) {
      handleStaff();
    }

    cout << "Do you want to continue? (y/n): ";
    cin >> continueLoginInput;

    if (continueLoginInput == 'n' || continueLoginInput == 'N') {
      continueLogin = false;
      cout << endl;
    }
  }

  cout << "Thank you for using the system. System shut down\n";

  return 0;
};