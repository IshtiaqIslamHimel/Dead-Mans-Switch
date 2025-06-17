#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

const string TIMESTAMP_FILE = "last_run.txt";
const string TARGET_FOLDER = "secret_folder"; // folder to delete if time expired
const int MAX_DAYS_ALLOWED = 3;  // days before trigger
const string PASSWORD = "letmein";  // password to extend timer

// Get current UNIX timestamp
long getCurrentTime() {
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
}

// Write current time to file
void updateTimestamp() {
    ofstream file(TIMESTAMP_FILE);
    file << getCurrentTime();
    file.close();
}

// Read timestamp from file
long readLastRunTime() {
    ifstream file(TIMESTAMP_FILE);
    long t = 0;
    if (file.is_open()) {
        file >> t;
        file.close();
    }
    return t;
}

// Calculate days passed since last run
int daysSinceLastRun(long lastTime) {
    long now = getCurrentTime();
    return static_cast<int>((now - lastTime) / (60 * 60 * 24));
}

// Delete target folder recursively
void deleteTarget() {
    if (fs::exists(TARGET_FOLDER)) {
        try {
            fs::remove_all(TARGET_FOLDER);
            cout << "Deleted folder: " << TARGET_FOLDER << "\n";
        } catch (const fs::filesystem_error& e) {
            cout << "Error deleting folder: " << e.what() << "\n";
        }
    } else {
        cout << "Target folder not found, nothing to delete.\n";
    }
}

// Trigger the action if deadline missed
void triggerAction() {
    cout << "\n⚠️  DEAD MAN'S SWITCH TRIGGERED! ⚠️\n";
    cout << "You haven't run this program within " << MAX_DAYS_ALLOWED << " days.\n";
    deleteTarget();
}

// Password prompt to extend/reset timer
bool extendTimer() {
    cout << "\nEnter password to extend the timer: ";
    string input;
    cin >> input;
    if (input == PASSWORD) {
        updateTimestamp();
        cout << "Timer extended! You're safe for another " << MAX_DAYS_ALLOWED << " days.\n";
        return true;
    } else {
        cout << "Wrong password! Timer not extended.\n";
        return false;
    }
}

int main() {
    cout << "🔐 Dead Man's Switch Program\n";

    // First run: create timestamp file and exit safely
    if (!fs::exists(TIMESTAMP_FILE)) {
        cout << "First time run. Creating timestamp file...\n";
        updateTimestamp();
        cout << "You're safe for now.\n";
        return 0;
    }

    long lastRun = readLastRunTime();
    int days = daysSinceLastRun(lastRun);
    cout << "Days since last run: " << days << "\n";

    if (days > MAX_DAYS_ALLOWED) {
        triggerAction();

        // Ask if user wants to extend timer now (password protected)
        cout << "Do you want to extend the timer? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            extendTimer();
        } else {
            cout << "Timer not extended. Goodbye.\n";
        }
    } else {
        cout << "✅ All good. Updating timestamp.\n";
        updateTimestamp();
    }

    return 0;
}
