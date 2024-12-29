#include <ctime>
#include <iostream>
#include <main.h>
#include <util.h>

using namespace std;

const int MAX_SUPPLIERS = 100;
const int MAX_DISTRIBUTIONS = 100;
const int MAX_OWNERS = 10;
const int MAX_STAFF = 10;

string ownerLastLoginTimes[MAX_OWNERS];
string staffLastLoginTimes[MAX_OWNERS];

int supplierIds[MAX_SUPPLIERS];
string supplierNames[MAX_SUPPLIERS];
int supplierSupplyAmounts[MAX_SUPPLIERS];
int supplierCount = 0;

char distributionGrades[MAX_DISTRIBUTIONS];
int distributionQuantities[MAX_DISTRIBUTIONS];
string distributionDestinations[MAX_DISTRIBUTIONS];
int distributionCount = 0;

string getCurrentTime() {
  time_t now = time(0);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&now));
  return string(buffer);
}

// ================================================= AUTH
bool authFunction(string username, string password, string type,
                  char usernames[][10], char passwords[][10], int size) {
  for (int i = 0; i < size; i++) {
    if (username == usernames[i] && password == passwords[i]) {
      if (type == "owner") {
        ownerLastLoginTimes[i] = getCurrentTime(); // Add this line
      } else if (type == "staff") {
        staffLastLoginTimes[i] = getCurrentTime(); // Add this line
      }
      return true;
    }
  }

  return false;
}

void printError(string message) { cout << "Error: " << message << endl; }


// new added function for viewSupplierWithMinAmount() and viewSupplierWithMaxAmount()
// =================================================================================
bool validateSupplierId(int id) {
  return id > 0;
}

int findMaxOrMinSupplier(bool isMax) {
    if (supplierCount == 0) {
        return -1;
    }
    int targetIndex = 0;
    for (int i = 1; i < supplierCount; i++) {
        if (isMax) {
            if (supplierSupplyAmounts[i] > supplierSupplyAmounts[targetIndex]) {
                targetIndex = i;
            }
        } else {
            if (supplierSupplyAmounts[i] < supplierSupplyAmounts[targetIndex]) {
                targetIndex = i;
            }
        }
    }
    return targetIndex;
}
// =================================================================================




// ================================================= AUTH

// ================================================= OWNER




void addSupplier() {
  // Cek apakah daftar supplier sudah penuh
  if (supplierCount >= MAX_SUPPLIERS) {
    cout << "Supplier list is full.\n";
    return;
  }

  // input pengguna memasukkan Supplier ID
  cout << "Enter Supplier ID: ";
  cin >> supplierIds[supplierCount];
  

  // Validasi Supplier ID jika lebih kecil dari 0
  if (!validateSupplierId(supplierIds[supplierCount])) {
    cout << "Invalid Supplier ID. ID must be positive.\n";
    return;
  }
  // input pengguna memasukkan nama dan jumlah pasokan
  cout << "Enter Supplier Name: ";
  cin >> supplierNames[supplierCount];
  cout << "Enter Supply Amount: ";
  cin >> supplierSupplyAmounts[supplierCount];

  // Tambahkan supplierCount jika semua data valid
  supplierCount++;
  cout << "Supplier added successfully.\n";
}

void viewSupplierHistory() {
  for (int i = 0; i < supplierCount; i++) {
    cout << "ID: " << supplierIds[i] << ", Name: " << supplierNames[i]
         << ", Supply Amount: " << supplierSupplyAmounts[i] << endl;
  }
}


// New added function for add supply
 // =================================================================================
void viewSupplierWithMaxAmount() {
    int maxIndex = findMaxOrMinSupplier(true);
    if (maxIndex == -1) {
        cout << "No suppliers available.\n";
        return;
    }
    cout << "Supplier with the largest supply amount:\n";
    cout << "ID: " << supplierIds[maxIndex] << ", Name: " << supplierNames[maxIndex]
         << ", Supply Amount: " << supplierSupplyAmounts[maxIndex] << endl;
}



void viewSupplierWithMinAmount() {
    int minIndex = findMaxOrMinSupplier(false);
    if (minIndex == -1) {
        cout << "No suppliers available.\n";
        return;
    }
    cout << "Supplier with the smallest supply amount:\n";
    cout << "ID: " << supplierIds[minIndex] << ", Name: " << supplierNames[minIndex]
         << ", Supply Amount: " << supplierSupplyAmounts[minIndex] << endl;
}
 // =================================================================================




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
      printError("Invalid username or password.");
    }

    loginAttempt++;
    if (loginAttempt >= 3) {
      printError("Too many login attempts. Exiting...");
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
    cout << "4. Last Login Times\n";
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



// New Modified Logic for AddSupply
 // =================================================================================
       if (supplyChoice == 1) {
    int supplierChoice;
    do {
        cout << "\nSupplier Control Menu:\n";
        cout << "1. Add Supplier\n";
        cout << "2. View Supplier History\n";
        cout << "3. View Supplier with Max Amount\n";
        cout << "4. View Supplier with Min Amount\n";
        cout << "5. Back to Supply Management Menu\n";
        cout << "Enter your choice: ";
        cin >> supplierChoice;

        if (supplierChoice == 1) {
            addSupplier();
        } else if (supplierChoice == 2) {
            viewSupplierHistory();
        } else if (supplierChoice == 3) {
            viewSupplierWithMaxAmount();
        } else if (supplierChoice == 4) {
            viewSupplierWithMinAmount();
        } else if (supplierChoice == 5) {
            break; // Exit the loop and go back to the previous menu
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
 // =================================================================================
            
          } while (true);
        } else if (supplyChoice == 3) {
          break;
        } else {
          cout << "Invalid choice. Please try again.\n";
        }
      } while (true);
    }

    if (menuChoice == 4) {
      cout << "\nLast Login Times:\n";
      for (int i = 0; i < sizeof(ownerUsername) / sizeof(ownerUsername[0]);
           i++) {
        cout << "Username: " << ownerUsername[i]
             << ", Last Login: " << ownerLastLoginTimes[i] << endl;
      }
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

  rackGradeA[rackNum - 1] += gradeA;
  rackGradeB[rackNum - 1] += gradeB;
  rackGradeC[rackNum - 1] += gradeC;

  storageCount++;
  cout << "Batch location recorded successfully.\n";
}

void viewRackContents() {
  cout << "\nRack Contents:\n";
  for (int i = 0; i < MAX_RACKS; i++) {
    cout << "Rack " << (i + 1) << ":\n";
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
  cout << "Total: "
       << (shipmentGradeA[index] + shipmentGradeB[index] +
           shipmentGradeC[index])
       << " eggs\n";
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
      printError("Invalid username or password.");
    }

    loginAttempt++;
    if (loginAttempt >= 3) {
      printError("Too many login attempts. Exiting...");
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
    cout << "4. Last Login Times\n";
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

    if (menuChoice == 4) {
      cout << "\nLast Login Times:\n";
      for (int i = 0; i < sizeof(staffUsername) / sizeof(staffUsername[0]);
           i++) {
        cout << "Username: " << staffUsername[i]
             << ", Last Login: " << staffLastLoginTimes[i] << endl;
      }
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
