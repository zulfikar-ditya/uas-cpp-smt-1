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
      // Receiving Management
    }

    if (menuChoice == 2) {
      // Storage Operation
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
