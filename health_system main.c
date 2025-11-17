#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
    #define SLEEP(x) Sleep(x)
#else
    #include <unistd.h>
    #define CLEAR "clear"
    #define SLEEP(x) usleep(x * 1000)
#endif

// Structure denotations
typedef struct {
    int id;
    char name[50];
    char username[30];
    char password[60];
    char specialization[60];
    char phone[15];
    int active;
} Doctor;

typedef struct {
    int id;
    char name[50];
    char username[30];
    char password[60];
    int age;
    char gender[11];
    char phone[15];
    char address[150];
    char bloodGroup[5];
    int active;
} Patient;

typedef struct {
    int patient_Id;
    int doctor_Id;
    char date[20];
    float heart_Rate;
    int bpSystolic;
    int bpDiastolic;
    float temperature;
    float bloodSugar;
    float spo2;
    float respirationRate;
    char symptoms[500];
    char diagnosis[500];
    char risk_Level[20];
    int risk_Score;
} HealthRecord;

typedef struct {
    char username[40];
    char password[60];
} Admin;

// Global Variables and Constants
Admin admin = {"tcm9798", "tcm@4626"};
int loggedInDoctorId = -1;
int loggedInPatientId = -1;

// Function Declarations
void initializeFiles();
void enableWindowsColors();
void setColor(int color);
void resetColor();
void loadingAnimation(const char* message);
void printHeader(const char* title);
void printBox(const char* message, int color);
void animatedText(const char* text, int speed);
void pressAnyKey();

// Admin Functions Declarations
void adminLogin();
void adminPanel();
void addDoctor();
void removeDoctor();
void viewAllDoctors();
void addPatient();
void removePatient();
void viewAllPatients();
void viewAllRecords();

// Doctor Functions Declarations
void doctorLogin();
void doctorPanel();
void enterVitals();
void viewPatientHistory();
void viewMyPatients();
void generateHealthReport(int patientId);

// Patient Functions Declarations
void patientLogin();
void patientPanel();
void viewMyProfile();
void viewMyHealthReports();
void viewMyAnalytics();

// Utility Functions Declarations
int getNextId(const char* filename);
void getCurrentDate(char* buffer);
int calculateRiskScore(HealthRecord rec);
void determineRiskLevel(HealthRecord* rec);
void displayVitalStatus(float value, float min, float max, const char* name);
Patient getPatientById(int id);
Doctor getDoctorById(int id);
void trim(char* str);

// Color codes (for Windows)
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_BLUE 9
#define COLOR_MAGENTA 13
#define COLOR_CYAN 11
#define COLOR_WHITE 15
#define COLOR_GRAY 8

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;

    #ifdef _WIN32
    enableWindowsColors();
    #endif

    initializeFiles();

    while(1) {
        system(CLEAR);
        printHeader("Health Monitoring & Early Disease Prediction System");
        printf("\n");
        setColor(COLOR_CYAN);
        printf("================================================================\n");
        printf("||           MAIN MENU - SELECT YOUR ROLE                    ||\n");
        printf("================================================================\n");
        resetColor();
        printf("||                                                            ||\n");
        setColor(COLOR_YELLOW);
        printf("||  1. ");
        resetColor();
        printf("Doctor Login                                          ||\n");
        setColor(COLOR_YELLOW);
        printf("||  2. ");
        resetColor();
        printf("Patient Login                                         ||\n");
        setColor(COLOR_YELLOW);
        printf("||  3. ");
        resetColor();
        printf("Admin Login                                           ||\n");
        setColor(COLOR_YELLOW);
        printf("||  4. ");
        resetColor();
        printf("About System                                          ||\n");
        setColor(COLOR_YELLOW);
        printf("||  5. ");
        resetColor();
        printf("Exit                                                  ||\n");
        printf("||                                                            ||\n");
        setColor(COLOR_CYAN);
        printf("================================================================\n");
        resetColor();

        setColor(COLOR_GREEN);
        printf("\n>> Enter your choice: ");
        resetColor();
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                doctorLogin();
                break;
            case 2:
                patientLogin();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                system(CLEAR);
                printHeader("Health Monitoring & Early Disease Prediction System");
                setColor(COLOR_CYAN);
                printf("||  Version: 1.0                                             ||\n");
                printf("||  Developed in: C Language                                 ||\n");
                printf("||  Developed by: techytcm                                   ||\n");
                printf("||  Features:                                                ||\n");
                printf("||    * Multi-user role-based system                         ||\n");
                printf("||    * Real-time vital monitoring                           ||\n");
                printf("||    * AI-powered risk prediction                           ||\n");
                printf("||    * Comprehensive health analytics                       ||\n");
                printf("||    * Automated report generation                          ||\n");
                printf("================================================================\n");
                resetColor();
                pressAnyKey();
                break;
            case 5:
                loadingAnimation("Shutting down system");
                setColor(COLOR_GREEN);
                printf("\n[SUCCESS] Thank you for using Health Monitoring & Early Disease Prediction System!\n");
                resetColor();
                return 0;
            default:
                printBox("Invalid choice! Please try again.", COLOR_RED);
                SLEEP(1500);
        }
    }

    return 0;
}

// ==================== INITIALIZATION ====================
void initializeFiles() {
    FILE *fp;

    fp = fopen("doctors.dat", "ab+");
    if(fp) fclose(fp);

    fp = fopen("patients.dat", "ab+");
    if(fp) fclose(fp);

    fp = fopen("health_records.dat", "ab+");
    if(fp) fclose(fp);
}

void enableWindowsColors() {
    #ifdef _WIN32
    // Set console to UTF-8 for better character support
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
}

void setColor(int color) {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    #endif
}

void resetColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // Default white color
    #endif
}

// ==================== ANIMATION FUNCTIONS ====================
void loadingAnimation(const char* message) {
    setColor(COLOR_YELLOW);
    printf("\n%s", message);
    for(int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        SLEEP(400);
    }
    printf("\n");
    resetColor();
}

void printHeader(const char* title) {
    int len = strlen(title);
    int padding = (60 - len) / 2;

    setColor(COLOR_BLUE);
    printf("\n");
    printf("================================================================\n");
    printf("||%*s%s%*s||\n", padding, "", title, 60-padding-len, "");
    printf("================================================================\n");
    resetColor();
}

void printBox(const char* message, int color) {
    setColor(color);
    printf("\n");
    printf("+--------------------------------------------------------------+\n");
    printf("| %-60s |\n", message);
    printf("+--------------------------------------------------------------+\n");
    resetColor();
}

void animatedText(const char* text, int speed) {
    for(int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        SLEEP(speed);
    }
}

void pressAnyKey() {
    setColor(COLOR_YELLOW);
    printf("\nClick Enter to continue...");
    resetColor();
    getchar();
}

// ==================== ADMIN FUNCTIONS ====================
void adminLogin() {
    char username[50], password[50];

    system(CLEAR);
    printHeader("ADMIN LOGIN");

    setColor(COLOR_CYAN);
    printf("\n+-- Enter Credentials -----------------------------------------+\n");
    resetColor();
    printf("| Username: ");
    scanf("%s", username);
    printf("| Password: ");
    scanf("%s", password);
    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();
    getchar();

    loadingAnimation("Authenticating");

    if(strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0) {
        printBox("[SUCCESS] Login Successful! Welcome TCM.", COLOR_GREEN);
        SLEEP(1000);
        adminPanel();
    } else {
        printBox("[ERROR] Invalid credentials!", COLOR_RED);
        SLEEP(1500);
    }
}

void adminPanel() {
    int choice;

    while(1) {
        system(CLEAR);
        printHeader("ADMIN CONTROL PANEL");

        setColor(COLOR_MAGENTA);
        printf("\n================================================================\n");
        printf("||                    ADMIN OPERATIONS                        ||\n");
        printf("================================================================\n");
        resetColor();
        printf("||  1. Add Doctor                                             ||\n");
        printf("||  2. Remove Doctor                                          ||\n");
        printf("||  3. View All Doctors                                       ||\n");
        printf("||  4. Add Patient                                            ||\n");
        printf("||  5. Remove Patient                                         ||\n");
        printf("||  6. View All Patients                                      ||\n");
        printf("||  7. View All Medical Records                               ||\n");
        printf("||  8. Logout                                                 ||\n");
        setColor(COLOR_MAGENTA);
        printf("================================================================\n");
        resetColor();

        setColor(COLOR_GREEN);
        printf("\n>> Enter choice: ");
        resetColor();
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addDoctor(); break;
            case 2: removeDoctor(); break;
            case 3: viewAllDoctors(); break;
            case 4: addPatient(); break;
            case 5: removePatient(); break;
            case 6: viewAllPatients(); break;
            case 7: viewAllRecords(); break;
            case 8: return;
            default:
                printBox("[ERROR] Invalid choice!", COLOR_RED);
                SLEEP(1000);
        }
    }
}

void addDoctor() {
    Doctor doc;
    FILE *fp;

    system(CLEAR);
    printHeader("ADD NEW DOCTOR");

    doc.id = getNextId("doctors.dat");
    doc.active = 1;

    setColor(COLOR_CYAN);
    printf("\n+-- Doctor Registration Form ----------------------------------+\n");
    resetColor();

    printf("| Full Name: ");
    fgets(doc.name, sizeof(doc.name), stdin);
    trim(doc.name);

    printf("| Username: ");
    scanf("%s", doc.username);
    getchar();

    printf("| Password: ");
    scanf("%s", doc.password);
    getchar();

    printf("| Specialization: ");
    fgets(doc.specialization, sizeof(doc.specialization), stdin);
    trim(doc.specialization);

    printf("| Phone: ");
    scanf("%s", doc.phone);
    getchar();

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    fp = fopen("doctors.dat", "ab");
    if(fp) {
        fwrite(&doc, sizeof(Doctor), 1, fp);
        fclose(fp);
        loadingAnimation("Saving doctor information");
        printBox("[SUCCESS] Doctor added successfully!", COLOR_GREEN);
    } else {
        printBox("[ERROR] Error saving doctor!", COLOR_RED);
    }

    pressAnyKey();
}

void removeDoctor() {
    int id, found = 0;
    Doctor doc;
    FILE *fp, *temp;

    system(CLEAR);
    printHeader("REMOVE DOCTOR");

    setColor(COLOR_YELLOW);
    printf("\nEnter Doctor ID to remove: ");
    resetColor();
    scanf("%d", &id);
    getchar();

    fp = fopen("doctors.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if(fp && temp) {
        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(doc.id == id && doc.active == 1) {
                found = 1;
                doc.active = 0;
            }
            fwrite(&doc, sizeof(Doctor), 1, temp);
        }
        fclose(fp);
        fclose(temp);

        remove("doctors.dat");
        rename("temp.dat", "doctors.dat");

        if(found) {
            printBox("[SUCCESS] Doctor removed successfully!", COLOR_GREEN);
        } else {
            printBox("[ERROR] Doctor not found!", COLOR_RED);
        }
    } else {
        printBox("[ERROR] Error accessing file!", COLOR_RED);
    }

    pressAnyKey();
}

void viewAllDoctors() {
    Doctor doc;
    FILE *fp;
    int count = 0;

    system(CLEAR);
    printHeader("ALL DOCTORS");

    fp = fopen("doctors.dat", "rb");
    if(fp) {
        setColor(COLOR_CYAN);
        printf("\n================================================================\n");
        printf("| ID | Name              | Specialization   | Phone           |\n");
        printf("================================================================\n");
        resetColor();

        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(doc.active == 1) {
                printf("|%-4d| %-17s | %-16s | %-15s |\n",
                       doc.id, doc.name, doc.specialization, doc.phone);
                count++;
            }
        }

        setColor(COLOR_CYAN);
        printf("================================================================\n");
        resetColor();
        setColor(COLOR_GREEN);
        printf("\nTotal Doctors: %d\n", count);
        resetColor();
        fclose(fp);
    } else {
        printBox("[ERROR] Error reading file!", COLOR_RED);
    }

    pressAnyKey();
}

void addPatient() {
    Patient pat;
    FILE *fp;

    system(CLEAR);
    printHeader("ADD NEW PATIENT");

    pat.id = getNextId("patients.dat");
    pat.active = 1;

    setColor(COLOR_CYAN);
    printf("\n+-- Patient Registration Form ---------------------------------+\n");
    resetColor();

    printf("| Full Name: ");
    fgets(pat.name, sizeof(pat.name), stdin);
    trim(pat.name);

    printf("| Username: ");
    scanf("%s", pat.username);
    getchar();

    printf("| Password: ");
    scanf("%s", pat.password);
    getchar();

    printf("| Age: ");
    scanf("%d", &pat.age);
    getchar();

    printf("| Gender (M/F): ");
    scanf("%s", pat.gender);
    getchar();

    printf("| Blood Group: ");
    scanf("%s", pat.bloodGroup);
    getchar();

    printf("| Phone: ");
    scanf("%s", pat.phone);
    getchar();

    printf("| Address: ");
    fgets(pat.address, sizeof(pat.address), stdin);
    trim(pat.address);

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    fp = fopen("patients.dat", "ab");
    if(fp) {
        fwrite(&pat, sizeof(Patient), 1, fp);
        fclose(fp);
        loadingAnimation("Saving patient information");
        printBox("[SUCCESS] Patient registered successfully!", COLOR_GREEN);
    } else {
        printBox("[ERROR] Error saving patient!", COLOR_RED);
    }

    pressAnyKey();
}

void removePatient() {
    int id, found = 0;
    Patient pat;
    FILE *fp, *temp;

    system(CLEAR);
    printHeader("REMOVE PATIENT");

    setColor(COLOR_YELLOW);
    printf("\nEnter Patient ID to remove: ");
    resetColor();
    scanf("%d", &id);
    getchar();

    fp = fopen("patients.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if(fp && temp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(pat.id == id && pat.active == 1) {
                found = 1;
                pat.active = 0;
            }
            fwrite(&pat, sizeof(Patient), 1, temp);
        }
        fclose(fp);
        fclose(temp);

        remove("patients.dat");
        rename("temp.dat", "patients.dat");

        if(found) {
            printBox("[SUCCESS] Patient removed successfully!", COLOR_GREEN);
        } else {
            printBox("[ERROR] Patient not found!", COLOR_RED);
        }
    } else {
        printBox("[ERROR] Error accessing file!", COLOR_RED);
    }

    pressAnyKey();
}

void viewAllPatients() {
    Patient pat;
    FILE *fp;
    int count = 0;

    system(CLEAR);
    printHeader("ALL PATIENTS");

    fp = fopen("patients.dat", "rb");
    if(fp) {
        setColor(COLOR_CYAN);
        printf("\n========================================================================\n");
        printf("| ID | Name              | Age | Gender | Blood | Phone          |\n");
        printf("========================================================================\n");
        resetColor();

        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(pat.active == 1) {
                printf("|%-4d| %-17s | %-3d | %-6s | %-5s | %-14s |\n",
                       pat.id, pat.name, pat.age, pat.gender, pat.bloodGroup, pat.phone);
                count++;
            }
        }

        setColor(COLOR_CYAN);
        printf("========================================================================\n");
        resetColor();
        setColor(COLOR_GREEN);
        printf("\nTotal Patients: %d\n", count);
        resetColor();
        fclose(fp);
    } else {
        printBox("[ERROR] Error reading file!", COLOR_RED);
    }

    pressAnyKey();
}

void viewAllRecords() {
    HealthRecord rec;
    Patient pat;
    FILE *fp;
    int count = 0;

    system(CLEAR);
    printHeader("ALL MEDICAL RECORDS");

    fp = fopen("health_records.dat", "rb");
    if(fp) {
        setColor(COLOR_CYAN);
        printf("\n=============================================================\n");
        printf("| Patient    | Date       | Risk Level  | Risk Score    |\n");
        printf("=============================================================\n");
        resetColor();

        while(fread(&rec, sizeof(HealthRecord), 1, fp)) {
            pat = getPatientById(rec.patient_Id);

            printf("| %-10s | %-10s | ", pat.name, rec.date);

            if(strcmp(rec.risk_Level, "HIGH") == 0) setColor(COLOR_RED);
            else if(strcmp(rec.risk_Level, "MEDIUM") == 0) setColor(COLOR_YELLOW);
            else setColor(COLOR_GREEN);

            printf("%-11s", rec.risk_Level);
            resetColor();
            printf(" | %-13d |\n", rec.risk_Score);
            count++;
        }

        setColor(COLOR_CYAN);
        printf("=============================================================\n");
        resetColor();
        setColor(COLOR_GREEN);
        printf("\nTotal Records: %d\n", count);
        resetColor();
        fclose(fp);
    } else {
        printBox("[ERROR] No records found!", COLOR_RED);
    }

    pressAnyKey();
}

// ==================== DOCTOR FUNCTIONS ====================
void doctorLogin() {
    char username[50], password[50];
    Doctor doc;
    FILE *fp;
    int found = 0;

    system(CLEAR);
    printHeader("DOCTOR LOGIN");

    setColor(COLOR_CYAN);
    printf("\n+-- Enter Credentials -----------------------------------------+\n");
    resetColor();
    printf("| Username: ");
    scanf("%s", username);
    printf("| Password: ");
    scanf("%s", password);
    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();
    getchar();

    loadingAnimation("Authenticating");

    fp = fopen("doctors.dat", "rb");
    if(fp) {
        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(strcmp(doc.username, username) == 0 &&
               strcmp(doc.password, password) == 0 &&
               doc.active == 1) {
                found = 1;
                loggedInDoctorId = doc.id;
                break;
            }
        }
        fclose(fp);
    }

    if(found) {
        char msg[100];
        sprintf(msg, "[SUCCESS] Welcome Dr. %s!", doc.name);
        printBox(msg, COLOR_GREEN);
        SLEEP(1000);
        doctorPanel();
    } else {
        printBox("[ERROR] Invalid credentials!", COLOR_RED);
        SLEEP(1500);
    }
}

void doctorPanel() {
    int choice;
    Doctor doc = getDoctorById(loggedInDoctorId);

    while(1) {
        system(CLEAR);
        printHeader("DOCTOR DASHBOARD");

        setColor(COLOR_GREEN);
        printf("\nWelcome, Dr. %s\n", doc.name);
        setColor(COLOR_CYAN);
        printf("Specialization: %s\n", doc.specialization);
        resetColor();

        setColor(COLOR_BLUE);
        printf("\n================================================================\n");
        printf("||                   DOCTOR OPERATIONS                        ||\n");
        printf("================================================================\n");
        resetColor();
        printf("||  1. Enter Patient Vitals                                   ||\n");
        printf("||  2. View Patient History                                   ||\n");
        printf("||  3. View My Patients                                       ||\n");
        printf("||  4. Generate Health Report                                 ||\n");
        printf("||  5. Logout                                                 ||\n");
        setColor(COLOR_BLUE);
        printf("================================================================\n");
        resetColor();

        setColor(COLOR_GREEN);
        printf("\n>> Enter choice: ");
        resetColor();
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: enterVitals(); break;
            case 2: viewPatientHistory(); break;
            case 3: viewMyPatients(); break;
            case 4: {
                int pid;
                setColor(COLOR_YELLOW);
                printf("\nEnter Patient ID: ");
                resetColor();
                scanf("%d", &pid);
                getchar();
                generateHealthReport(pid);
                break;
            }
            case 5:
                loggedInDoctorId = -1;
                return;
            default:
                printBox("[ERROR] Invalid choice!", COLOR_RED);
                SLEEP(1000);
        }
    }
}

void enterVitals() {
    HealthRecord rec;
    int patientId;
    Patient pat;
    FILE *fp;

    system(CLEAR);
    printHeader("ENTER PATIENT VITALS");

    setColor(COLOR_CYAN);
    printf("\nAvailable Patients:\n");
    resetColor();
    fp = fopen("patients.dat", "rb");
    if(fp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(pat.active == 1) {
                printf("  ID: %d - %s\n", pat.id, pat.name);
            }
        }
        fclose(fp);
    }

    setColor(COLOR_YELLOW);
    printf("\nEnter Patient ID: ");
    resetColor();
    scanf("%d", &patientId);
    getchar();

    pat = getPatientById(patientId);
    if(pat.id == 0) {
        printBox("[ERROR] Patient not found!", COLOR_RED);
        pressAnyKey();
        return;
    }

    rec.patient_Id = patientId;
    rec.doctor_Id = loggedInDoctorId;
    getCurrentDate(rec.date);

    setColor(COLOR_CYAN);
    printf("\n+-- Vital Signs Input -----------------------------------------+\n");
    resetColor();

    printf("| Heart Rate (bpm): ");
    scanf("%f", &rec.heart_Rate);

    printf("| Blood Pressure Systolic: ");
    scanf("%d", &rec.bpSystolic);

    printf("| Blood Pressure Diastolic: ");
    scanf("%d", &rec.bpDiastolic);

    printf("| Body Temperature (F): ");
    scanf("%f", &rec.temperature);

    printf("| Blood Sugar (mg/dL): ");
    scanf("%f", &rec.bloodSugar);

    printf("| SpO2 (%%): ");
    scanf("%f", &rec.spo2);

    printf("| Respiration Rate (per min): ");
    scanf("%f", &rec.respirationRate);
    getchar();

    printf("| Symptoms: ");
    fgets(rec.symptoms, sizeof(rec.symptoms), stdin);
    trim(rec.symptoms);

    printf("| Diagnosis: ");
    fgets(rec.diagnosis, sizeof(rec.diagnosis), stdin);
    trim(rec.diagnosis);

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    // AI Risk Calculation
    loadingAnimation("Analyzing vitals with AI");
    rec.risk_Score = calculateRiskScore(rec);
    determineRiskLevel(&rec);

    // Display immediate analysis
    setColor(COLOR_MAGENTA);
    printf("\n===============================================================\n");
    printf("||              AI RISK ANALYSIS RESULT                      ||\n");
    printf("===============================================================\n");
    resetColor();

    displayVitalStatus(rec.heart_Rate, 60, 100, "Heart Rate");
    displayVitalStatus(rec.bpSystolic, 90, 120, "BP Systolic");
    displayVitalStatus(rec.bpDiastolic, 60, 80, "BP Diastolic");
    displayVitalStatus(rec.temperature, 97, 99, "Temperature");
    displayVitalStatus(rec.bloodSugar, 70, 140, "Blood Sugar");
    displayVitalStatus(rec.spo2, 95, 100, "SpO2");
    displayVitalStatus(rec.respirationRate, 12, 20, "Respiration");

    printf("||                                                           ||\n");

    printf("|| Overall Risk Level: ");
    if(strcmp(rec.risk_Level, "HIGH") == 0) setColor(COLOR_RED);
    else if(strcmp(rec.risk_Level, "MEDIUM") == 0) setColor(COLOR_YELLOW);
    else setColor(COLOR_GREEN);
    printf("%-11s", rec.risk_Level);
    resetColor();
    printf("                              ||\n");

    printf("|| Risk Score: %-3d/100                                      ||\n", rec.risk_Score);

    setColor(COLOR_MAGENTA);
    printf("===============================================================\n");
    resetColor();

    // Save record
    fp = fopen("health_records.dat", "ab");
    if(fp) {
        fwrite(&rec, sizeof(HealthRecord), 1, fp);
        fclose(fp);
        printBox("[SUCCESS] Vitals recorded successfully!", COLOR_GREEN);
    } else {
        printBox("[ERROR] Error saving record!", COLOR_RED);
    }

    pressAnyKey();
}

void viewPatientHistory() {
    int patientId;
    HealthRecord rec;
    Patient pat;
    FILE *fp;
    int count = 0;

    system(CLEAR);
    printHeader("PATIENT HEALTH HISTORY");

    setColor(COLOR_YELLOW);
    printf("\nEnter Patient ID: ");
    resetColor();
    scanf("%d", &patientId);
    getchar();

    pat = getPatientById(patientId);
    if(pat.id == 0) {
        printBox("[ERROR] Patient not found!", COLOR_RED);
        pressAnyKey();
        return;
    }

    setColor(COLOR_GREEN);
    printf("\nPatient: %s (Age: %d, Blood Group: %s)\n", pat.name, pat.age, pat.bloodGroup);
    resetColor();

    fp = fopen("health_records.dat", "rb");
    if(fp) {
        setColor(COLOR_CYAN);
        printf("\n=============================================================================\n");
        printf("| Date       | HR    | BP      | Temp | Sugar | SpO2  | Risk       |\n");
        printf("=============================================================================\n");
        resetColor();

        while(fread(&rec, sizeof(HealthRecord), 1, fp)) {
            if(rec.patient_Id == patientId) {
                printf("| %-10s | %-5.0f | %3d/%-3d | %-4.1f | %-5.0f | %-5.1f | ",
                       rec.date, rec.heart_Rate, rec.bpSystolic, rec.bpDiastolic,
                       rec.temperature, rec.bloodSugar, rec.spo2);

                if(strcmp(rec.risk_Level, "HIGH") == 0) setColor(COLOR_RED);
                else if(strcmp(rec.risk_Level, "MEDIUM") == 0) setColor(COLOR_YELLOW);
                else setColor(COLOR_GREEN);

                printf("%-10s", rec.risk_Level);
                resetColor();
                printf(" |\n");
                count++;
            }
        }

        setColor(COLOR_CYAN);
        printf("=============================================================================\n");
        resetColor();
        setColor(COLOR_GREEN);
        printf("\nTotal Records: %d\n", count);
        resetColor();
        fclose(fp);
    } else {
        printBox("[ERROR] No records found!", COLOR_RED);
    }

    pressAnyKey();
}

void viewMyPatients() {
    HealthRecord rec;
    Patient pat;
    FILE *fp;
    int patientIds[100] = {0};
    int count = 0;

    system(CLEAR);
    printHeader("MY PATIENTS");

    fp = fopen("health_records.dat", "rb");
    if(fp) {
        while(fread(&rec, sizeof(HealthRecord), 1, fp)) {
            if(rec.doctor_Id == loggedInDoctorId) {
                int exists = 0;
                for(int i = 0; i < count; i++) {
                    if(patientIds[i] == rec.patient_Id) {
                        exists = 1;
                        break;
                    }
                }
                if(!exists && count < 100) {
                    patientIds[count++] = rec.patient_Id;
                }
            }
        }
        fclose(fp);
    }

    setColor(COLOR_CYAN);
    printf("\n========================================================================\n");
    printf("| ID | Name              | Age | Gender | Blood | Phone         |\n");
    printf("========================================================================\n");
    resetColor();

    for(int i = 0; i < count; i++) {
        pat = getPatientById(patientIds[i]);
        if(pat.id != 0) {
            printf("|%-4d| %-17s | %-3d | %-6s | %-5s | %-13s |\n",
                   pat.id, pat.name, pat.age, pat.gender, pat.bloodGroup, pat.phone);
        }
    }

    setColor(COLOR_CYAN);
    printf("========================================================================\n");
    resetColor();
    setColor(COLOR_GREEN);
    printf("\nTotal Patients: %d\n", count);
    resetColor();

    pressAnyKey();
}

void generateHealthReport(int patientId) {
    Patient pat;
    HealthRecord rec, records[10];
    Doctor doc;
    FILE *fp;
    int count = 0;
    float avgHR = 0, avgBP = 0, avgSugar = 0, avgSpO2 = 0;

    system(CLEAR);
    printHeader("COMPREHENSIVE HEALTH REPORT");

    pat = getPatientById(patientId);
    if(pat.id == 0) {
        printBox("[ERROR] Patient not found!", COLOR_RED);
        pressAnyKey();
        return;
    }

    fp = fopen("health_records.dat", "rb");
    if(fp) {
        while(fread(&rec, sizeof(HealthRecord), 1, fp)) {
            if(rec.patient_Id == patientId && count < 10) {
                records[count++] = rec;
            }
        }
        fclose(fp);
    }

    if(count == 0) {
        printBox("[ERROR] No records found for this patient!", COLOR_RED);
        pressAnyKey();
        return;
    }

    for(int i = 0; i < count; i++) {
        avgHR += records[i].heart_Rate;
        avgBP += records[i].bpSystolic;
        avgSugar += records[i].bloodSugar;
        avgSpO2 += records[i].spo2;
    }
    avgHR /= count;
    avgBP /= count;
    avgSugar /= count;
    avgSpO2 /= count;

    setColor(COLOR_BLUE);
    printf("\n================================================================\n");
    printf("||                    PATIENT INFORMATION                     ||\n");
    printf("================================================================\n");
    resetColor();
    printf("|| Name: %-53s||\n", pat.name);
    printf("|| Patient ID: %-47d||\n", pat.id);
    printf("|| Age: %-3d  Gender: %-6s  Blood Group: %-5s             ||\n",
           pat.age, pat.gender, pat.bloodGroup);
    printf("|| Phone: %-52s||\n", pat.phone);
    setColor(COLOR_BLUE);
    printf("================================================================\n");
    resetColor();

    setColor(COLOR_MAGENTA);
    printf("\n================================================================\n");
    printf("||              HEALTH ANALYTICS (Last %d Visits)             ||\n", count);
    printf("================================================================\n");
    resetColor();
    printf("|| Average Heart Rate      : %-5.1f bpm                       ||\n", avgHR);
    printf("|| Average Blood Pressure  : %-5.1f mmHg                      ||\n", avgBP);
    printf("|| Average Blood Sugar     : %-5.1f mg/dL                     ||\n", avgSugar);
    printf("|| Average SpO2            : %-5.1f %%                         ||\n", avgSpO2);
    setColor(COLOR_MAGENTA);
    printf("================================================================\n");
    resetColor();

    rec = records[count-1];
    doc = getDoctorById(rec.doctor_Id);

    setColor(COLOR_CYAN);
    printf("\n================================================================\n");
    printf("||                  LATEST EXAMINATION                        ||\n");
    printf("================================================================\n");
    resetColor();
    printf("|| Date: %-53s||\n", rec.date);
    printf("|| Examined By: Dr. %-42s||\n", doc.name);
    printf("||                                                            ||\n");
    printf("|| Vital Signs:                                               ||\n");
    printf("||   * Heart Rate: %-5.0f bpm                                  ||\n", rec.heart_Rate);
    printf("||   * Blood Pressure: %d/%d mmHg                              ||\n",
           rec.bpSystolic, rec.bpDiastolic);
    printf("||   * Temperature: %-5.1f F                                   ||\n", rec.temperature);
    printf("||   * Blood Sugar: %-5.0f mg/dL                               ||\n", rec.bloodSugar);
    printf("||   * SpO2: %-5.1f %%                                          ||\n", rec.spo2);
    printf("||   * Respiration: %-5.1f per min                             ||\n", rec.respirationRate);
    setColor(COLOR_CYAN);
    printf("================================================================\n");
    resetColor();

    setColor(COLOR_GREEN);
    printf("\n================================================================\n");
    printf("||                  DIAGNOSIS & SYMPTOMS                      ||\n");
    printf("================================================================\n");
    resetColor();
    printf("|| Symptoms: %-50s||\n", rec.symptoms);
    printf("|| Diagnosis: %-49s||\n", rec.diagnosis);
    setColor(COLOR_GREEN);
    printf("================================================================\n");
    resetColor();

    printf("\n");
    if(strcmp(rec.risk_Level, "HIGH") == 0) setColor(COLOR_RED);
    else if(strcmp(rec.risk_Level, "MEDIUM") == 0) setColor(COLOR_YELLOW);
    else setColor(COLOR_GREEN);

    printf("================================================================\n");
    printf("||              AI RISK ASSESSMENT                            ||\n");
    printf("================================================================\n");
    resetColor();
    printf("|| Risk Level: ");
    if(strcmp(rec.risk_Level, "HIGH") == 0) setColor(COLOR_RED);
    else if(strcmp(rec.risk_Level, "MEDIUM") == 0) setColor(COLOR_YELLOW);
    else setColor(COLOR_GREEN);
    printf("%-11s", rec.risk_Level);
    resetColor();
    printf("                                     ||\n");
    printf("|| Risk Score: %d/100                                          ||\n", rec.risk_Score);
    printf("||                                                            ||\n");

    if(strcmp(rec.risk_Level, "HIGH") == 0) {
        printf("|| [!] IMMEDIATE ATTENTION REQUIRED                           ||\n");
        printf("||    * Schedule immediate follow-up                          ||\n");
        printf("||    * Monitor vitals closely                                ||\n");
        printf("||    * Consider hospitalization if worsens                   ||\n");
    } else if(strcmp(rec.risk_Level, "MEDIUM") == 0) {
        printf("|| [!] MODERATE RISK - FOLLOW-UP RECOMMENDED                  ||\n");
        printf("||    * Schedule follow-up within 7 days                      ||\n");
        printf("||    * Monitor symptoms                                      ||\n");
        printf("||    * Follow prescribed medication                          ||\n");
    } else {
        printf("|| [OK] LOW RISK - NORMAL HEALTH STATUS                       ||\n");
        printf("||    * Continue healthy lifestyle                            ||\n");
        printf("||    * Regular check-ups recommended                         ||\n");
        printf("||    * Maintain current medication if any                    ||\n");
    }

    if(strcmp(rec.risk_Level, "HIGH") == 0) setColor(COLOR_RED);
    else if(strcmp(rec.risk_Level, "MEDIUM") == 0) setColor(COLOR_YELLOW);
    else setColor(COLOR_GREEN);
    printf("================================================================\n");
    resetColor();

    setColor(COLOR_YELLOW);
    printf("\n================================================================\n");
    printf("||                  DETECTED RISK FACTORS                     ||\n");
    printf("================================================================\n");
    resetColor();

    int riskCount = 0;
    if(rec.bpSystolic > 140 || rec.bpDiastolic > 90) {
        printf("|| * Hypertension (High Blood Pressure)                       ||\n");
        riskCount++;
    }
    if(rec.bloodSugar > 180) {
        printf("|| * Hyperglycemia (High Blood Sugar - Diabetes Risk)        ||\n");
        riskCount++;
    }
    if(rec.spo2 < 92) {
        printf("|| * Hypoxemia (Low Oxygen - Respiratory Risk)               ||\n");
        riskCount++;
    }
    if(rec.temperature > 101) {
        printf("|| * Fever (Possible Infection)                               ||\n");
        riskCount++;
    }
    if(rec.heart_Rate > 110) {
        printf("|| * Tachycardia (Elevated Heart Rate - Cardiac Risk)        ||\n");
        riskCount++;
    }
    if(rec.heart_Rate < 60) {
        printf("|| * Bradycardia (Low Heart Rate)                             ||\n");
        riskCount++;
    }

    if(riskCount == 0) {
        printf("|| No significant risk factors detected [OK]                  ||\n");
    }

    setColor(COLOR_YELLOW);
    printf("================================================================\n");
    resetColor();

    setColor(COLOR_GREEN);
    printf("\n+------------------------------------------------------------+\n");
    printf("| Report Generated: ");
    char currentDate[20];
    getCurrentDate(currentDate);
    printf("%-41s|\n", currentDate);
    printf("| System: AI Health Monitoring v1.0                          |\n");
    printf("+------------------------------------------------------------+\n");
    resetColor();

    pressAnyKey();
}

// ==================== PATIENT FUNCTIONS ====================
void patientLogin() {
    char username[50], password[50];
    Patient pat;
    FILE *fp;
    int found = 0;

    system(CLEAR);
    printHeader("PATIENT LOGIN");

    setColor(COLOR_CYAN);
    printf("\n+-- Enter Credentials -----------------------------------------+\n");
    resetColor();
    printf("| Username: ");
    scanf("%s", username);
    printf("| Password: ");
    scanf("%s", password);
    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();
    getchar();

    loadingAnimation("Authenticating");

    fp = fopen("patients.dat", "rb");
    if(fp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(strcmp(pat.username, username) == 0 &&
               strcmp(pat.password, password) == 0 &&
               pat.active == 1) {
                found = 1;
                loggedInPatientId = pat.id;
                break;
            }
        }
        fclose(fp);
    }

    if(found) {
        char msg[100];
        sprintf(msg, "[SUCCESS] Welcome %s!", pat.name);
        printBox(msg, COLOR_GREEN);
        SLEEP(1000);
        patientPanel();
    } else {
        printBox("[ERROR] Invalid credentials!", COLOR_RED);
        SLEEP(1500);
    }
}

void patientPanel() {
    int choice;
    Patient pat = getPatientById(loggedInPatientId);

    while(1) {
        system(CLEAR);
        printHeader("PATIENT DASHBOARD");

        setColor(COLOR_GREEN);
        printf("\nWelcome, %s\n", pat.name);
        setColor(COLOR_CYAN);
        printf("Patient ID: %d\n", pat.id);
        resetColor();

        setColor(COLOR_BLUE);
        printf("\n================================================================\n");
        printf("||                   PATIENT OPERATIONS                       ||\n");
        printf("================================================================\n");
        resetColor();
        printf("||  1. View My Profile                                        ||\n");
        printf("||  2. View My Health Reports                                 ||\n");
        printf("||  3. View My Health Analytics                               ||\n");
        printf("||  4. Logout                                                 ||\n");
        setColor(COLOR_BLUE);
        printf("================================================================\n");
        resetColor();

        setColor(COLOR_GREEN);
        printf("\n>> Enter choice: ");
        resetColor();
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: viewMyProfile(); break;
            case 2: viewMyHealthReports(); break;
            case 3: viewMyAnalytics(); break;
            case 4:
                loggedInPatientId = -1;
                return;
            default:
                printBox("[ERROR] Invalid choice!", COLOR_RED);
                SLEEP(1000);
        }
    }
}

void viewMyProfile() {
    Patient pat = getPatientById(loggedInPatientId);

    system(CLEAR);
    printHeader("MY PROFILE");

    setColor(COLOR_CYAN);
    printf("\n================================================================\n");
    printf("||                   PERSONAL INFORMATION                     ||\n");
    printf("================================================================\n");
    resetColor();
    printf("|| Patient ID: %-48d||\n", pat.id);
    printf("|| Name: %-53s||\n", pat.name);
    printf("|| Username: %-49s||\n", pat.username);
    printf("|| Age: %-55d||\n", pat.age);
    printf("|| Gender: %-51s||\n", pat.gender);
    printf("|| Blood Group: %-46s||\n", pat.bloodGroup);
    printf("|| Phone: %-52s||\n", pat.phone);
    printf("|| Address: %-50s||\n", pat.address);
    setColor(COLOR_CYAN);
    printf("================================================================\n");
    resetColor();

    pressAnyKey();
}

void viewMyHealthReports() {
    HealthRecord rec;
    FILE *fp;
    int count = 0;

    system(CLEAR);
    printHeader("MY HEALTH REPORTS");

    fp = fopen("health_records.dat", "rb");
    if(fp) {
        setColor(COLOR_CYAN);
        printf("\n=============================================================================\n");
        printf("| Date       | HR    | BP      | Temp | Sugar | SpO2  | Risk       |\n");
        printf("=============================================================================\n");
        resetColor();

        while(fread(&rec, sizeof(HealthRecord), 1, fp)) {
            if(rec.patient_Id == loggedInPatientId) {
                printf("| %-10s | %-5.0f | %3d/%-3d | %-4.1f | %-5.0f | %-5.1f | ",
                       rec.date, rec.heart_Rate, rec.bpSystolic, rec.bpDiastolic,
                       rec.temperature, rec.bloodSugar, rec.spo2);

                if(strcmp(rec.risk_Level, "HIGH") == 0) setColor(COLOR_RED);
                else if(strcmp(rec.risk_Level, "MEDIUM") == 0) setColor(COLOR_YELLOW);
                else setColor(COLOR_GREEN);

                printf("%-10s", rec.risk_Level);
                resetColor();
                printf(" |\n");
                count++;
            }
        }

        setColor(COLOR_CYAN);
        printf("=============================================================================\n");
        resetColor();

        if(count > 0) {
            setColor(COLOR_GREEN);
            printf("\nTotal Records: %d\n", count);
            resetColor();
        } else {
            printBox("No health records found!", COLOR_YELLOW);
        }

        fclose(fp);
    } else {
        printBox("[ERROR] Error reading records!", COLOR_RED);
    }

    pressAnyKey();
}

void viewMyAnalytics() {
    HealthRecord rec;
    FILE *fp;
    int count = 0;
    float totalHR = 0, totalBP = 0, totalSugar = 0, totalSpO2 = 0, totalTemp = 0;
    float maxSugar = 0, minSugar = 999;
    int highRisk = 0, mediumRisk = 0, lowRisk = 0;

    system(CLEAR);
    printHeader("MY HEALTH ANALYTICS");

    fp = fopen("health_records.dat", "rb");
    if(fp) {
        while(fread(&rec, sizeof(HealthRecord), 1, fp)) {
            if(rec.patient_Id == loggedInPatientId) {
                totalHR += rec.heart_Rate;
                totalBP += rec.bpSystolic;
                totalSugar += rec.bloodSugar;
                totalSpO2 += rec.spo2;
                totalTemp += rec.temperature;

                if(rec.bloodSugar > maxSugar) maxSugar = rec.bloodSugar;
                if(rec.bloodSugar < minSugar) minSugar = rec.bloodSugar;

                if(strcmp(rec.risk_Level, "HIGH") == 0) highRisk++;
                else if(strcmp(rec.risk_Level, "MEDIUM") == 0) mediumRisk++;
                else lowRisk++;

                count++;
            }
        }
        fclose(fp);
    }

    if(count == 0) {
        printBox("No health data available for analysis!", COLOR_YELLOW);
        pressAnyKey();
        return;
    }

    float avgHR = totalHR / count;
    float avgBP = totalBP / count;
    float avgSugar = totalSugar / count;
    float avgSpO2 = totalSpO2 / count;
    float avgTemp = totalTemp / count;

    setColor(COLOR_MAGENTA);
    printf("\n================================================================\n");
    printf("||              HEALTH STATISTICS OVERVIEW                   ||\n");
    printf("================================================================\n");
    resetColor();
    printf("|| Total Check-ups: %-43d||\n", count);
    printf("||                                                            ||\n");
    printf("|| Average Heart Rate      : %-5.1f bpm                       ||\n", avgHR);
    printf("|| Average Blood Pressure  : %-5.1f mmHg                      ||\n", avgBP);
    printf("|| Average Blood Sugar     : %-5.1f mg/dL                     ||\n", avgSugar);
    printf("|| Average SpO2            : %-5.1f %%                         ||\n", avgSpO2);
    printf("|| Average Temperature     : %-5.1f F                         ||\n", avgTemp);
    printf("||                                                            ||\n");
    printf("|| Highest Blood Sugar     : %-5.0f mg/dL                     ||\n", maxSugar);
    printf("|| Lowest Blood Sugar      : %-5.0f mg/dL                     ||\n", minSugar);
    setColor(COLOR_MAGENTA);
    printf("================================================================\n");
    resetColor();

    setColor(COLOR_CYAN);
    printf("\n================================================================\n");
    printf("||                 RISK LEVEL DISTRIBUTION                    ||\n");
    printf("================================================================\n");
    resetColor();

    printf("|| ");
    setColor(COLOR_RED);
    printf("High Risk Records   : %-3d (%5.1f%%)", highRisk, (highRisk*100.0)/count);
    resetColor();
    printf("                       ||\n");

    printf("|| ");
    setColor(COLOR_YELLOW);
    printf("Medium Risk Records : %-3d (%5.1f%%)", mediumRisk, (mediumRisk*100.0)/count);
    resetColor();
    printf("                       ||\n");

    printf("|| ");
    setColor(COLOR_GREEN);
    printf("Low Risk Records    : %-3d (%5.1f%%)", lowRisk, (lowRisk*100.0)/count);
    resetColor();
    printf("                       ||\n");

    setColor(COLOR_CYAN);
    printf("================================================================\n");
    resetColor();

    setColor(COLOR_GREEN);
    printf("\n================================================================\n");
    printf("||              HEALTH STATUS INTERPRETATION                  ||\n");
    printf("================================================================\n");
    resetColor();

    if(avgHR >= 60 && avgHR <= 100) {
        printf("|| [OK] Heart Rate: Normal range                              ||\n");
    } else {
        printf("|| [!] Heart Rate: Needs attention                            ||\n");
    }

    if(avgBP >= 90 && avgBP <= 120) {
        printf("|| [OK] Blood Pressure: Normal range                          ||\n");
    } else {
        printf("|| [!] Blood Pressure: Needs attention                        ||\n");
    }

    if(avgSugar >= 70 && avgSugar <= 140) {
        printf("|| [OK] Blood Sugar: Normal range                             ||\n");
    } else {
        printf("|| [!] Blood Sugar: Needs attention                           ||\n");
    }

    if(avgSpO2 >= 95) {
        printf("|| [OK] Oxygen Level: Normal range                            ||\n");
    } else {
        printf("|| [!] Oxygen Level: Needs attention                          ||\n");
    }

    setColor(COLOR_GREEN);
    printf("================================================================\n");
    resetColor();

    pressAnyKey();
}

// ==================== UTILITY FUNCTIONS ====================
int getNextId(const char* filename) {
    FILE *fp;
    int maxId = 0;

    if(strcmp(filename, "doctors.dat") == 0) {
        Doctor doc;
        fp = fopen(filename, "rb");
        if(fp) {
            while(fread(&doc, sizeof(Doctor), 1, fp)) {
                if(doc.id > maxId) maxId = doc.id;
            }
            fclose(fp);
        }
    } else if(strcmp(filename, "patients.dat") == 0) {
        Patient pat;
        fp = fopen(filename, "rb");
        if(fp) {
            while(fread(&pat, sizeof(Patient), 1, fp)) {
                if(pat.id > maxId) maxId = pat.id;
            }
            fclose(fp);
        }
    }

    return maxId + 1;
}

void getCurrentDate(char* buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(buffer, "%02d/%02d/%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
}

int calculateRiskScore(HealthRecord rec) {
    int score = 0;

    if(rec.heart_Rate < 60) score += 15;
    else if(rec.heart_Rate > 100 && rec.heart_Rate <= 110) score += 10;
    else if(rec.heart_Rate > 110) score += 20;

    if(rec.bpSystolic > 180 || rec.bpDiastolic > 120) score += 25;
    else if(rec.bpSystolic > 140 || rec.bpDiastolic > 90) score += 20;
    else if(rec.bpSystolic > 130 || rec.bpDiastolic > 85) score += 10;
    else if(rec.bpSystolic < 90 || rec.bpDiastolic < 60) score += 15;

    if(rec.temperature > 103) score += 20;
    else if(rec.temperature > 101) score += 15;
    else if(rec.temperature > 99.5) score += 10;
    else if(rec.temperature < 95) score += 15;

    if(rec.bloodSugar > 250) score += 20;
    else if(rec.bloodSugar > 180) score += 15;
    else if(rec.bloodSugar > 140) score += 10;
    else if(rec.bloodSugar < 70) score += 15;

    if(rec.spo2 < 90) score += 15;
    else if(rec.spo2 < 92) score += 12;
    else if(rec.spo2 < 95) score += 8;

    if(rec.respirationRate > 24 || rec.respirationRate < 12) score += 10;
    else if(rec.respirationRate > 20 || rec.respirationRate < 14) score += 5;

    return score;
}

void determineRiskLevel(HealthRecord* rec) {
    if(rec->risk_Score >= 60) {
        strcpy(rec->risk_Level, "HIGH");
    } else if(rec->risk_Score >= 30) {
        strcpy(rec->risk_Level, "MEDIUM");
    } else {
        strcpy(rec->risk_Level, "LOW");
    }
}

void displayVitalStatus(float value, float min, float max, const char* name) {
    const char* status;
    int color;

    if(value < min) {
        status = "LOW";
        color = COLOR_YELLOW;
    } else if(value > max) {
        status = "HIGH";
        color = COLOR_RED;
    } else {
        status = "NORMAL";
        color = COLOR_GREEN;
    }

    printf("|| %-20s: %6.1f  [", name, value);
    setColor(color);
    printf("%-7s", status);
    resetColor();
    printf("]                  ||\n");
}

Patient getPatientById(int id) {
    Patient pat;
    FILE *fp;

    pat.id = 0;

    fp = fopen("patients.dat", "rb");
    if(fp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(pat.id == id && pat.active == 1) {
                fclose(fp);
                return pat;
            }
        }
        fclose(fp);
    }

    pat.id = 0;
    return pat;
}

Doctor getDoctorById(int id) {
    Doctor doc;
    FILE *fp;

    doc.id = 0;

    fp = fopen("doctors.dat", "rb");
    if(fp) {
        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(doc.id == id && doc.active == 1) {
                fclose(fp);
                return doc;
            }
        }
        fclose(fp);
    }

    doc.id = 0;
    return doc;
}

void trim(char* str) {
    int len = strlen(str);

    while(len > 0 && (str[len-1] == '\n' || str[len-1] == '\r' || str[len-1] == ' ')) {
        str[len-1] = '\0';
        len--;
    }

    int i = 0;
    while(str[i] == ' ') i++;

    if(i > 0) {
        int j = 0;
        while(str[i] != '\0') {
            str[j++] = str[i++];
        }
        str[j] = '\0';
    }
}
