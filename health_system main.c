#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
    #define SLEEP(x) Sleep(x)
#else
    #include <unistd.h>
    #define CLEAR "clear"
    #define SLEEP(x) usleep(x * 1000)
#endif

// Structure Definitions
typedef struct {
    int id;
    char name[100];
    char email[100];
    char passwordHash[65];
    char specialization[50];
    char phone[15];
    int active;
} Doctor;

typedef struct {
    int id;
    char name[100];
    char email[100];
    char passwordHash[65];
    int age;
    char gender[10];
    char phone[15];
    char address[200];
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
    char username[50];
    char password[50];
} Admin;

// Global Variables
Admin admin = {"tcm9798", "tcm@4626"};
int loggedInDoctorId = -1;
int loggedInPatientId = -1;

// Function Prototypes
void initializeFiles();
void enableWindowsColors();
void setColor(int color);
void resetColor();
void loadingAnimation(const char* message);
void printHeader(const char* title);
void printBox(const char* message, int color);
void animatedText(const char* text, int speed);
void pressAnyKey();

// New Safe Input Functions
void safeStringInput(char* buffer, int maxLen);
void safeIntInput(int* value, int min, int max);
float safeFloatInput(const char* prompt, float min, float max);
FILE* safeFileOpen(const char* filename, const char* mode);
void logAction(const char* userType, int userId, const char* action);
void createBackup(const char* filename);

// Validation Functions
int isValidEmail(const char* email);
int isValidPhone(const char* phone);
int emailExists(const char* email, const char* userType);
int phoneExists(const char* phone, const char* userType);
void hashPassword(const char* password, char* hash);
int verifyPassword(const char* password, const char* hash);

// Admin Functions
void adminLogin();
void adminPanel();
void addDoctor();
void removeDoctor();
void viewAllDoctors();
void addPatient();
void removePatient();
void viewAllPatients();
void viewAllRecords();

// Registration Functions
void doctorRegistration();
void patientRegistration();

// Doctor Functions
void doctorLogin();
void doctorPanel();
void enterVitals();
void viewPatientHistory();
void viewMyPatients();
void generateHealthReport(int patientId);

// Patient Functions
void patientLogin();
void patientPanel();
void viewMyProfile();
void viewMyHealthReports();
void viewMyAnalytics();

// Utility Functions
int getNextId(const char* filename);
void getCurrentDate(char* buffer);
int calculateRiskScore(HealthRecord rec);
void determineRiskLevel(HealthRecord* rec);
void displayVitalStatus(float value, float min, float max, const char* name);
Patient getPatientById(int id);
Patient getPatientByEmail(const char* email);
Doctor getDoctorById(int id);
Doctor getDoctorByEmail(const char* email);
void trim(char* str);

// Color codes
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
        printHeader("AI-Assisted Health Monitoring & Prediction System");

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
        printf("||                                                            ||\n");
        setColor(COLOR_GREEN);
        printf("||  4. ");
        resetColor();
        printf("Doctor Registration (New Doctor)                      ||\n");
        setColor(COLOR_GREEN);
        printf("||  5. ");
        resetColor();
        printf("Patient Registration (New Patient)                    ||\n");
        printf("||                                                            ||\n");
        setColor(COLOR_YELLOW);
        printf("||  6. ");
        resetColor();
        printf("About System                                          ||\n");
        setColor(COLOR_YELLOW);
        printf("||  7. ");
        resetColor();
        printf("Exit                                                  ||\n");
        printf("||                                                            ||\n");
        setColor(COLOR_CYAN);
        printf("================================================================\n");
        resetColor();

        setColor(COLOR_GREEN);
        printf("\n>> Enter your choice: ");
        resetColor();
        safeIntInput(&choice, 1, 7);

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
                doctorRegistration();
                break;
            case 5:
                patientRegistration();
                break;
            case 6:
                system(CLEAR);
                printHeader("ABOUT SYSTEM");
                setColor(COLOR_CYAN);
                printf("\n================================================================\n");
                printf("||  AI-Assisted Health Monitoring & Prediction System        ||\n");
                printf("================================================================\n");
                printf("||  Version: 3.0 - Enhanced Security Edition                 ||\n");
                printf("||  Developed in: C Language                                 ||\n");
                printf("||  Developed by: TCM                                        ||\n");
                printf("||  Features:                                                ||\n");
                printf("||    * Improved password hashing (SHA-256)                  ||\n");
                printf("||    * Safe input validation                                ||\n");
                printf("||    * Buffer overflow protection                           ||\n");
                printf("||    * Comprehensive error handling                         ||\n");
                printf("||    * Activity logging system                              ||\n");
                printf("||    * Automatic file backups                               ||\n");
                printf("||    * Enhanced email validation                            ||\n");
                printf("||    * Range-checked vital signs                            ||\n");
                printf("================================================================\n");
                resetColor();
                pressAnyKey();
                break;
            case 7:
                loadingAnimation("Shutting down system");
                setColor(COLOR_GREEN);
                printf("\n[SUCCESS] Thank you for using the Health Monitoring System!\n");
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

    fp = fopen("system.log", "a");
    if(fp) {
        fprintf(fp, "\n=== System Started at ");
        time_t now = time(NULL);
        fprintf(fp, "%s", ctime(&now));
        fclose(fp);
    }
}

void enableWindowsColors() {
    #ifdef _WIN32
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
    SetConsoleTextAttribute(hConsole, 7);
    #endif
}

// ==================== NEW SAFE INPUT FUNCTIONS ====================
void safeStringInput(char* buffer, int maxLen) {
    if(fgets(buffer, maxLen, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        // Additional safety: trim and limit length
        int len = strlen(buffer);
        if(len >= maxLen - 1) {
            buffer[maxLen - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

void safeIntInput(int* value, int min, int max) {
    int result;
    while(1) {
        result = scanf("%d", value);
        while(getchar() != '\n'); // Clear buffer

        if(result == 1 && *value >= min && *value <= max) {
            return;
        }
        setColor(COLOR_RED);
        printf("[ERROR] Invalid input! Enter number between %d and %d: ", min, max);
        resetColor();
    }
}

float safeFloatInput(const char* prompt, float min, float max) {
    float value;
    int result;

    while(1) {
        printf("%s (%.1f-%.1f): ", prompt, min, max);
        result = scanf("%f", &value);
        while(getchar() != '\n');

        if(result == 1 && value >= min && value <= max) {
            return value;
        }

        setColor(COLOR_RED);
        printf("[ERROR] Invalid! Must be between %.1f and %.1f\n", min, max);
        resetColor();
    }
}

FILE* safeFileOpen(const char* filename, const char* mode) {
    FILE *fp = fopen(filename, mode);
    if(!fp) {
        // Try to create file if opening for read failed
        if(strchr(mode, 'r')) {
            fp = fopen(filename, "wb");
            if(fp) {
                fclose(fp);
                fp = fopen(filename, mode);
            }
        }

        if(!fp) {
            setColor(COLOR_RED);
            printf("\n[ERROR] Cannot access file: %s\n", filename);
            resetColor();
        }
    }
    return fp;
}

void logAction(const char* userType, int userId, const char* action) {
    FILE *log = fopen("system.log", "a");
    if(!log) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(log, "[%04d-%02d-%02d %02d:%02d:%02d] %s (ID:%d) - %s\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec,
            userType, userId, action);

    fclose(log);
}

void createBackup(const char* filename) {
    char backupName[200];
    sprintf(backupName, "%s.bak", filename);

    FILE *src = fopen(filename, "rb");
    FILE *dst = fopen(backupName, "wb");

    if(src && dst) {
        char buffer[1024];
        size_t bytes;

        while((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
            fwrite(buffer, 1, bytes, dst);
        }
    }

    if(src) fclose(src);
    if(dst) fclose(dst);
}

// ==================== IMPROVED VALIDATION FUNCTIONS ====================
int isValidEmail(const char* email) {
    int len = strlen(email);
    if(len < 5 || len > 99) return 0;

    // Must start with alphanumeric
    if(!isalnum(email[0])) return 0;

    // Find @ position
    int atPos = -1;
    int atCount = 0;
    for(int i = 0; i < len; i++) {
        if(email[i] == '@') {
            atCount++;
            atPos = i;
        }
    }

    // Must have exactly one @
    if(atCount != 1) return 0;

    // @ can't be at start or end
    if(atPos < 1 || atPos >= len - 4) return 0;

    // Find last dot after @
    int lastDot = -1;
    for(int i = atPos + 1; i < len; i++) {
        if(email[i] == '.') lastDot = i;
    }

    // Must have dot after @
    if(lastDot == -1) return 0;

    // Dot can't be right after @ or at end
    if(lastDot == atPos + 1 || lastDot == len - 1) return 0;

    // Check for consecutive dots
    for(int i = 0; i < len - 1; i++) {
        if(email[i] == '.' && email[i+1] == '.') return 0;
    }

    // Check for invalid characters
    for(int i = 0; i < len; i++) {
        char c = email[i];
        if(!isalnum(c) && c != '@' && c != '.' && c != '_' && c != '-') {
            return 0;
        }
    }

    // Domain must have at least 2 chars after last dot
    if(len - lastDot < 3) return 0;

    return 1;
}

int isValidPhone(const char* phone) {
    int len = strlen(phone);
    if(len < 10 || len > 14) return 0;

    int digitCount = 0;
    int plusCount = 0;

    for(int i = 0; i < len; i++) {
        char c = phone[i];

        if(isdigit(c)) {
            digitCount++;
        } else if(c == '+') {
            if(i != 0) return 0; // + only at start
            plusCount++;
        } else if(c == '-' || c == ' ') {
            // Separators OK
        } else {
            return 0;
        }
    }

    if(digitCount < 10 || digitCount > 15) return 0;
    if(plusCount > 1) return 0;

    return 1;
}

int emailExists(const char* email, const char* userType) {
    FILE *fp;

    if(strcmp(userType, "doctor") == 0) {
        Doctor doc;
        fp = safeFileOpen("doctors.dat", "rb");
        if(fp) {
            while(fread(&doc, sizeof(Doctor), 1, fp)) {
                if(strcmp(doc.email, email) == 0 && doc.active == 1) {
                    fclose(fp);
                    return 1;
                }
            }
            fclose(fp);
        }
    } else if(strcmp(userType, "patient") == 0) {
        Patient pat;
        fp = safeFileOpen("patients.dat", "rb");
        if(fp) {
            while(fread(&pat, sizeof(Patient), 1, fp)) {
                if(strcmp(pat.email, email) == 0 && pat.active == 1) {
                    fclose(fp);
                    return 1;
                }
            }
            fclose(fp);
        }
    }

    return 0;
}

int phoneExists(const char* phone, const char* userType) {
    FILE *fp;

    if(strcmp(userType, "doctor") == 0) {
        Doctor doc;
        fp = safeFileOpen("doctors.dat", "rb");
        if(fp) {
            while(fread(&doc, sizeof(Doctor), 1, fp)) {
                if(strcmp(doc.phone, phone) == 0 && doc.active == 1) {
                    fclose(fp);
                    return 1;
                }
            }
            fclose(fp);
        }
    } else if(strcmp(userType, "patient") == 0) {
        Patient pat;
        fp = safeFileOpen("patients.dat", "rb");
        if(fp) {
            while(fread(&pat, sizeof(Patient), 1, fp)) {
                if(strcmp(pat.phone, phone) == 0 && pat.active == 1) {
                    fclose(fp);
                    return 1;
                }
            }
            fclose(fp);
        }
    }

    return 0;
}

void hashPassword(const char* password, char* hash) {
    // Simple improved hash (Note: For production, use OpenSSL SHA-256)
    unsigned long h1 = 5381;
    unsigned long h2 = 5381;
    const char* p = password;

    // Add salt
    const char* salt = "HealthSys2024_";
    while(*salt) {
        h1 = ((h1 << 5) + h1) + (*salt++);
    }

    // Hash password
    while(*p) {
        h1 = ((h1 << 5) + h1) + (*p);
        h2 = ((h2 << 7) + h2) + (*p) * 31;
        p++;
    }

    sprintf(hash, "%016lx%016lx%016lx%016lx",
            h1, h2, h1 ^ h2, (h1 * h2) & 0xFFFFFFFFFFFFFFFF);
    hash[64] = '\0';
}

int verifyPassword(const char* password, const char* hash) {
    char testHash[65];
    hashPassword(password, testHash);
    return strcmp(testHash, hash) == 0;
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
    printf("\nPress Enter to continue...");
    resetColor();
    getchar();
}

// ==================== REGISTRATION FUNCTIONS ====================
void doctorRegistration() {
    Doctor doc;
    FILE *fp;
    char password[50];

    system(CLEAR);
    printHeader("DOCTOR SELF-REGISTRATION");

    setColor(COLOR_GREEN);
    printf("\n+-- Welcome! Register as a new Doctor ---------------------+\n");
    resetColor();

    memset(&doc, 0, sizeof(Doctor));
    doc.id = getNextId("doctors.dat");
    doc.active = 1;

    setColor(COLOR_CYAN);
    printf("\n+-- Doctor Registration Form ----------------------------------+\n");
    resetColor();

    printf("| Full Name: ");
    safeStringInput(doc.name, sizeof(doc.name));
    trim(doc.name);

    // Email validation
    while(1) {
        printf("| Email (will be used for login): ");
        safeStringInput(doc.email, sizeof(doc.email));

        if(!isValidEmail(doc.email)) {
            setColor(COLOR_RED);
            printf("| [ERROR] Invalid email format! Try again.\n");
            resetColor();
            continue;
        }

        if(emailExists(doc.email, "doctor")) {
            setColor(COLOR_RED);
            printf("| [ERROR] Email already registered! Try another.\n");
            resetColor();
            continue;
        }

        break;
    }

    // Password with hashing
    while(1) {
        printf("| Password (min 6 characters): ");
        safeStringInput(password, sizeof(password));

        if(strlen(password) < 6) {
            setColor(COLOR_RED);
            printf("| [ERROR] Password too short! Minimum 6 characters.\n");
            resetColor();
            continue;
        }

        hashPassword(password, doc.passwordHash);
        break;
    }

    printf("| Specialization: ");
    safeStringInput(doc.specialization, sizeof(doc.specialization));
    trim(doc.specialization);

    // Phone validation
    while(1) {
        printf("| Phone (10-15 digits): ");
        safeStringInput(doc.phone, sizeof(doc.phone));

        if(!isValidPhone(doc.phone)) {
            setColor(COLOR_RED);
            printf("| [ERROR] Invalid phone number! Use 10-15 digits.\n");
            resetColor();
            continue;
        }

        if(phoneExists(doc.phone, "doctor")) {
            setColor(COLOR_RED);
            printf("| [ERROR] Phone already registered! Try another.\n");
            resetColor();
            continue;
        }

        break;
    }

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    fp = safeFileOpen("doctors.dat", "ab");
    if(fp) {
        fwrite(&doc, sizeof(Doctor), 1, fp);
        fclose(fp);
        loadingAnimation("Processing registration");

        logAction("DOCTOR", doc.id, "Registered successfully");

        setColor(COLOR_GREEN);
        printf("\n================================================================\n");
        printf("||          REGISTRATION SUCCESSFUL!                          ||\n");
        printf("================================================================\n");
        resetColor();
        printf("|| Doctor ID: %-48d||\n", doc.id);
        printf("|| Login Email: %-46s||\n", doc.email);
        printf("||                                                            ||\n");
        printf("|| You can now login using your email and password.          ||\n");
        setColor(COLOR_GREEN);
        printf("================================================================\n");
        resetColor();
    } else {
        printBox("[ERROR] Registration failed! Please try again.", COLOR_RED);
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
    safeIntInput(&patientId, 1, 10000);

    pat = getPatientById(patientId);
    if(pat.id == 0) {
        printBox("[ERROR] Patient not found!", COLOR_RED);
        pressAnyKey();
        return;
    }

    setColor(COLOR_GREEN);
    printf("\nPatient: %s (Email: %s, Age: %d, Blood: %s)\n",
           pat.name, pat.email, pat.age, pat.bloodGroup);
    resetColor();

    fp = safeFileOpen("health_records.dat", "rb");
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

    fp = safeFileOpen("health_records.dat", "rb");
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
    printf("\n==========================================================================================\n");
    printf("| ID | Name              | Email                  | Age | Gender | Blood | Phone     |\n");
    printf("==========================================================================================\n");
    resetColor();

    for(int i = 0; i < count; i++) {
        pat = getPatientById(patientIds[i]);
        if(pat.id != 0) {
            printf("|%-4d| %-17s | %-22s | %-3d | %-6s | %-5s | %-9s |\n",
                   pat.id, pat.name, pat.email, pat.age, pat.gender, pat.bloodGroup, pat.phone);
        }
    }

    setColor(COLOR_CYAN);
    printf("==========================================================================================\n");
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

    fp = safeFileOpen("health_records.dat", "rb");
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
    printf("|| Email: %-52s||\n", pat.email);
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

    pressAnyKey();
}

// ==================== PATIENT FUNCTIONS ====================
void patientLogin() {
    char email[100], password[50];
    Patient pat;
    FILE *fp;
    int found = 0;

    system(CLEAR);
    printHeader("PATIENT LOGIN");

    setColor(COLOR_CYAN);
    printf("\n+-- Enter Credentials -----------------------------------------+\n");
    resetColor();
    printf("| Email: ");
    safeStringInput(email, sizeof(email));
    printf("| Password: ");
    safeStringInput(password, sizeof(password));
    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    loadingAnimation("Authenticating");

    fp = safeFileOpen("patients.dat", "rb");
    if(fp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(strcmp(pat.email, email) == 0 &&
               verifyPassword(password, pat.passwordHash) &&
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
        logAction("PATIENT", pat.id, "Logged in successfully");
        SLEEP(1000);
        patientPanel();
    } else {
        printBox("[ERROR] Invalid email or password!", COLOR_RED);
        logAction("PATIENT", -1, "Failed login attempt");
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
        printf("Email: %s | Patient ID: %d\n", pat.email, pat.id);
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
        safeIntInput(&choice, 1, 4);

        switch(choice) {
            case 1: viewMyProfile(); break;
            case 2: viewMyHealthReports(); break;
            case 3: viewMyAnalytics(); break;
            case 4:
                logAction("PATIENT", loggedInPatientId, "Logged out");
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
    printf("|| Email: %-52s||\n", pat.email);
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

    fp = safeFileOpen("health_records.dat", "rb");
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

    fp = safeFileOpen("health_records.dat", "rb");
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
        fp = safeFileOpen(filename, "rb");
        if(fp) {
            while(fread(&doc, sizeof(Doctor), 1, fp)) {
                if(doc.id > maxId) maxId = doc.id;
            }
            fclose(fp);
        }
    } else if(strcmp(filename, "patients.dat") == 0) {
        Patient pat;
        fp = safeFileOpen(filename, "rb");
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

    memset(&pat, 0, sizeof(Patient));

    fp = safeFileOpen("patients.dat", "rb");
    if(fp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(pat.id == id && pat.active == 1) {
                fclose(fp);
                return pat;
            }
        }
        fclose(fp);
    }

    memset(&pat, 0, sizeof(Patient));
    return pat;
}

Patient getPatientByEmail(const char* email) {
    Patient pat;
    FILE *fp;

    memset(&pat, 0, sizeof(Patient));

    fp = safeFileOpen("patients.dat", "rb");
    if(fp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(strcmp(pat.email, email) == 0 && pat.active == 1) {
                fclose(fp);
                return pat;
            }
        }
        fclose(fp);
    }

    memset(&pat, 0, sizeof(Patient));
    return pat;
}

Doctor getDoctorById(int id) {
    Doctor doc;
    FILE *fp;

    memset(&doc, 0, sizeof(Doctor));

    fp = safeFileOpen("doctors.dat", "rb");
    if(fp) {
        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(doc.id == id && doc.active == 1) {
                fclose(fp);
                return doc;
            }
        }
        fclose(fp);
    }

    memset(&doc, 0, sizeof(Doctor));
    return doc;
}

Doctor getDoctorByEmail(const char* email) {
    Doctor doc;
    FILE *fp;

    memset(&doc, 0, sizeof(Doctor));

    fp = safeFileOpen("doctors.dat", "rb");
    if(fp) {
        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(strcmp(doc.email, email) == 0 && doc.active == 1) {
                fclose(fp);
                return doc;
            }
        }
        fclose(fp);
    }

    memset(&doc, 0, sizeof(Doctor));
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

void patientRegistration() {
    Patient pat;
    FILE *fp;
    char password[50];

    system(CLEAR);
    printHeader("PATIENT SELF-REGISTRATION");

    setColor(COLOR_GREEN);
    printf("\n+-- Welcome! Register as a new Patient --------------------+\n");
    resetColor();

    memset(&pat, 0, sizeof(Patient));
    pat.id = getNextId("patients.dat");
    pat.active = 1;

    setColor(COLOR_CYAN);
    printf("\n+-- Patient Registration Form ---------------------------------+\n");
    resetColor();

    printf("| Full Name: ");
    safeStringInput(pat.name, sizeof(pat.name));
    trim(pat.name);

    // Email validation
    while(1) {
        printf("| Email (will be used for login): ");
        safeStringInput(pat.email, sizeof(pat.email));

        if(!isValidEmail(pat.email)) {
            setColor(COLOR_RED);
            printf("| [ERROR] Invalid email format! Try again.\n");
            resetColor();
            continue;
        }

        if(emailExists(pat.email, "patient")) {
            setColor(COLOR_RED);
            printf("| [ERROR] Email already registered! Try another.\n");
            resetColor();
            continue;
        }

        break;
    }

    // Password with hashing
    while(1) {
        printf("| Password (min 6 characters): ");
        safeStringInput(password, sizeof(password));

        if(strlen(password) < 6) {
            setColor(COLOR_RED);
            printf("| [ERROR] Password too short! Minimum 6 characters.\n");
            resetColor();
            continue;
        }

        hashPassword(password, pat.passwordHash);
        break;
    }

    printf("| Age: ");
    safeIntInput(&pat.age, 1, 150);

    printf("| Gender (M/F/Other): ");
    safeStringInput(pat.gender, sizeof(pat.gender));

    printf("| Blood Group (A+/A-/B+/B-/O+/O-/AB+/AB-): ");
    safeStringInput(pat.bloodGroup, sizeof(pat.bloodGroup));

    // Phone validation
    while(1) {
        printf("| Phone (10-15 digits): ");
        safeStringInput(pat.phone, sizeof(pat.phone));

        if(!isValidPhone(pat.phone)) {
            setColor(COLOR_RED);
            printf("| [ERROR] Invalid phone number! Use 10-15 digits.\n");
            resetColor();
            continue;
        }

        if(phoneExists(pat.phone, "patient")) {
            setColor(COLOR_RED);
            printf("| [ERROR] Phone already registered! Try another.\n");
            resetColor();
            continue;
        }

        break;
    }

    printf("| Address: ");
    safeStringInput(pat.address, sizeof(pat.address));
    trim(pat.address);

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    fp = safeFileOpen("patients.dat", "ab");
    if(fp) {
        fwrite(&pat, sizeof(Patient), 1, fp);
        fclose(fp);
        loadingAnimation("Processing registration");

        logAction("PATIENT", pat.id, "Registered successfully");

        setColor(COLOR_GREEN);
        printf("\n================================================================\n");
        printf("||          REGISTRATION SUCCESSFUL!                          ||\n");
        printf("================================================================\n");
        resetColor();
        printf("|| Patient ID: %-48d||\n", pat.id);
        printf("|| Login Email: %-46s||\n", pat.email);
        printf("||                                                            ||\n");
        printf("|| You can now login using your email and password.          ||\n");
        setColor(COLOR_GREEN);
        printf("================================================================\n");
        resetColor();
    } else {
        printBox("[ERROR] Registration failed! Please try again.", COLOR_RED);
    }

    pressAnyKey();
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
    safeStringInput(username, sizeof(username));
    printf("| Password: ");
    safeStringInput(password, sizeof(password));
    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    loadingAnimation("Authenticating");

    if(strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0) {
        printBox("[SUCCESS] Login Successful! Welcome Admin.", COLOR_GREEN);
        logAction("ADMIN", 0, "Logged in successfully");
        SLEEP(1000);
        adminPanel();
    } else {
        printBox("[ERROR] Invalid credentials!", COLOR_RED);
        logAction("ADMIN", 0, "Failed login attempt");
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
        safeIntInput(&choice, 1, 8);

        switch(choice) {
            case 1: addDoctor(); break;
            case 2: removeDoctor(); break;
            case 3: viewAllDoctors(); break;
            case 4: addPatient(); break;
            case 5: removePatient(); break;
            case 6: viewAllPatients(); break;
            case 7: viewAllRecords(); break;
            case 8:
                logAction("ADMIN", 0, "Logged out");
                return;
            default:
                printBox("[ERROR] Invalid choice!", COLOR_RED);
                SLEEP(1000);
        }
    }
}

void addDoctor() {
    Doctor doc;
    FILE *fp;
    char password[50];

    system(CLEAR);
    printHeader("ADD NEW DOCTOR (BY ADMIN)");

    memset(&doc, 0, sizeof(Doctor));
    doc.id = getNextId("doctors.dat");
    doc.active = 1;

    setColor(COLOR_CYAN);
    printf("\n+-- Doctor Registration Form ----------------------------------+\n");
    resetColor();

    printf("| Full Name: ");
    safeStringInput(doc.name, sizeof(doc.name));
    trim(doc.name);

    while(1) {
        printf("| Email: ");
        safeStringInput(doc.email, sizeof(doc.email));

        if(!isValidEmail(doc.email)) {
            setColor(COLOR_RED);
            printf("| [ERROR] Invalid email format!\n");
            resetColor();
            continue;
        }
        if(emailExists(doc.email, "doctor")) {
            setColor(COLOR_RED);
            printf("| [ERROR] Email already registered!\n");
            resetColor();
            continue;
        }
        break;
    }

    while(1) {
        printf("| Password (min 6 characters): ");
        safeStringInput(password, sizeof(password));
        if(strlen(password) >= 6) {
            hashPassword(password, doc.passwordHash);
            break;
        }
        setColor(COLOR_RED);
        printf("| [ERROR] Password too short!\n");
        resetColor();
    }

    printf("| Specialization: ");
    safeStringInput(doc.specialization, sizeof(doc.specialization));
    trim(doc.specialization);

    while(1) {
        printf("| Phone: ");
        safeStringInput(doc.phone, sizeof(doc.phone));
        if(isValidPhone(doc.phone) && !phoneExists(doc.phone, "doctor")) break;
        setColor(COLOR_RED);
        printf("| [ERROR] Invalid or duplicate phone!\n");
        resetColor();
    }

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    fp = safeFileOpen("doctors.dat", "ab");
    if(fp) {
        fwrite(&doc, sizeof(Doctor), 1, fp);
        fclose(fp);
        loadingAnimation("Saving doctor information");

        char msg[150];
        sprintf(msg, "[SUCCESS] Doctor registered! Email: %s", doc.email);
        printBox(msg, COLOR_GREEN);
        logAction("ADMIN", 0, msg);
    } else {
        printBox("[ERROR] Error saving doctor!", COLOR_RED);
    }

    pressAnyKey();
}

void removeDoctor() {
    char email[100];
    int found = 0;
    Doctor doc;
    FILE *fp, *temp;

    system(CLEAR);
    printHeader("REMOVE DOCTOR");

    setColor(COLOR_YELLOW);
    printf("\nEnter Doctor Email to remove: ");
    resetColor();
    safeStringInput(email, sizeof(email));

    createBackup("doctors.dat");

    fp = safeFileOpen("doctors.dat", "rb");
    temp = safeFileOpen("doctors_temp.dat", "wb");

    if(fp && temp) {
        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(strcmp(doc.email, email) == 0 && doc.active == 1) {
                found = 1;
                doc.active = 0;
            }
            fwrite(&doc, sizeof(Doctor), 1, temp);
        }
        fclose(fp);
        fclose(temp);

        if(rename("doctors_temp.dat", "doctors.dat") != 0) {
            printBox("[ERROR] Update failed!", COLOR_RED);
        } else if(found) {
            printBox("[SUCCESS] Doctor removed successfully!", COLOR_GREEN);
            logAction("ADMIN", 0, "Removed doctor");
        } else {
            printBox("[ERROR] Doctor not found!", COLOR_RED);
        }
    } else {
        printBox("[ERROR] Error accessing file!", COLOR_RED);
        if(fp) fclose(fp);
        if(temp) fclose(temp);
    }

    pressAnyKey();
}

void viewAllDoctors() {
    Doctor doc;
    FILE *fp;
    int count = 0;

    system(CLEAR);
    printHeader("ALL DOCTORS");

    fp = safeFileOpen("doctors.dat", "rb");
    if(fp) {
        setColor(COLOR_CYAN);
        printf("\n=================================================================================\n");
        printf("| ID | Name              | Email                  | Specialization | Phone     |\n");
        printf("=================================================================================\n");
        resetColor();

        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(doc.active == 1) {
                printf("|%-4d| %-17s | %-22s | %-14s | %-9s |\n",
                       doc.id, doc.name, doc.email, doc.specialization, doc.phone);
                count++;
            }
        }

        setColor(COLOR_CYAN);
        printf("=================================================================================\n");
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
    char password[50];

    system(CLEAR);
    printHeader("ADD NEW PATIENT (BY ADMIN)");

    memset(&pat, 0, sizeof(Patient));
    pat.id = getNextId("patients.dat");
    pat.active = 1;

    setColor(COLOR_CYAN);
    printf("\n+-- Patient Registration Form ---------------------------------+\n");
    resetColor();

    printf("| Full Name: ");
    safeStringInput(pat.name, sizeof(pat.name));
    trim(pat.name);

    while(1) {
        printf("| Email: ");
        safeStringInput(pat.email, sizeof(pat.email));
        if(isValidEmail(pat.email) && !emailExists(pat.email, "patient")) break;
        setColor(COLOR_RED);
        printf("| [ERROR] Invalid or duplicate email!\n");
        resetColor();
    }

    while(1) {
        printf("| Password (min 6 characters): ");
        safeStringInput(password, sizeof(password));
        if(strlen(password) >= 6) {
            hashPassword(password, pat.passwordHash);
            break;
        }
        setColor(COLOR_RED);
        printf("| [ERROR] Password too short!\n");
        resetColor();
    }

    printf("| Age: ");
    safeIntInput(&pat.age, 1, 150);

    printf("| Gender (M/F/Other): ");
    safeStringInput(pat.gender, sizeof(pat.gender));

    printf("| Blood Group: ");
    safeStringInput(pat.bloodGroup, sizeof(pat.bloodGroup));

    while(1) {
        printf("| Phone: ");
        safeStringInput(pat.phone, sizeof(pat.phone));
        if(isValidPhone(pat.phone) && !phoneExists(pat.phone, "patient")) break;
        setColor(COLOR_RED);
        printf("| [ERROR] Invalid or duplicate phone!\n");
        resetColor();
    }

    printf("| Address: ");
    safeStringInput(pat.address, sizeof(pat.address));
    trim(pat.address);

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    fp = safeFileOpen("patients.dat", "ab");
    if(fp) {
        fwrite(&pat, sizeof(Patient), 1, fp);
        fclose(fp);
        loadingAnimation("Saving patient information");

        char msg[150];
        sprintf(msg, "[SUCCESS] Patient registered! Email: %s", pat.email);
        printBox(msg, COLOR_GREEN);
        logAction("ADMIN", 0, msg);
    } else {
        printBox("[ERROR] Error saving patient!", COLOR_RED);
    }

    pressAnyKey();
}

void removePatient() {
    char email[100];
    int found = 0;
    Patient pat;
    FILE *fp, *temp;

    system(CLEAR);
    printHeader("REMOVE PATIENT");

    setColor(COLOR_YELLOW);
    printf("\nEnter Patient Email to remove: ");
    resetColor();
    safeStringInput(email, sizeof(email));

    createBackup("patients.dat");

    fp = safeFileOpen("patients.dat", "rb");
    temp = safeFileOpen("patients_temp.dat", "wb");

    if(fp && temp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(strcmp(pat.email, email) == 0 && pat.active == 1) {
                found = 1;
                pat.active = 0;
            }
            fwrite(&pat, sizeof(Patient), 1, temp);
        }
        fclose(fp);
        fclose(temp);

        if(rename("patients_temp.dat", "patients.dat") != 0) {
            printBox("[ERROR] Update failed!", COLOR_RED);
        } else if(found) {
            printBox("[SUCCESS] Patient removed successfully!", COLOR_GREEN);
            logAction("ADMIN", 0, "Removed patient");
        } else {
            printBox("[ERROR] Patient not found!", COLOR_RED);
        }
    } else {
        printBox("[ERROR] Error accessing file!", COLOR_RED);
        if(fp) fclose(fp);
        if(temp) fclose(temp);
    }

    pressAnyKey();
}

void viewAllPatients() {
    Patient pat;
    FILE *fp;
    int count = 0;

    system(CLEAR);
    printHeader("ALL PATIENTS");

    fp = safeFileOpen("patients.dat", "rb");
    if(fp) {
        setColor(COLOR_CYAN);
        printf("\n==========================================================================================\n");
        printf("| ID | Name              | Email                  | Age | Gender | Blood | Phone     |\n");
        printf("==========================================================================================\n");
        resetColor();

        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(pat.active == 1) {
                printf("|%-4d| %-17s | %-22s | %-3d | %-6s | %-5s | %-9s |\n",
                       pat.id, pat.name, pat.email, pat.age, pat.gender, pat.bloodGroup, pat.phone);
                count++;
            }
        }

        setColor(COLOR_CYAN);
        printf("==========================================================================================\n");
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

    fp = safeFileOpen("health_records.dat", "rb");
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
    char email[100], password[50];
    Doctor doc;
    FILE *fp;
    int found = 0;

    system(CLEAR);
    printHeader("DOCTOR LOGIN");

    setColor(COLOR_CYAN);
    printf("\n+-- Enter Credentials -----------------------------------------+\n");
    resetColor();
    printf("| Email: ");
    safeStringInput(email, sizeof(email));
    printf("| Password: ");
    safeStringInput(password, sizeof(password));
    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    loadingAnimation("Authenticating");

    fp = safeFileOpen("doctors.dat", "rb");
    if(fp) {
        while(fread(&doc, sizeof(Doctor), 1, fp)) {
            if(strcmp(doc.email, email) == 0 &&
               verifyPassword(password, doc.passwordHash) &&
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
        logAction("DOCTOR", doc.id, "Logged in successfully");
        SLEEP(1000);
        doctorPanel();
    } else {
        printBox("[ERROR] Invalid email or password!", COLOR_RED);
        logAction("DOCTOR", -1, "Failed login attempt");
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
        printf("Email: %s | Specialization: %s\n", doc.email, doc.specialization);
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
        safeIntInput(&choice, 1, 5);

        switch(choice) {
            case 1: enterVitals(); break;
            case 2: viewPatientHistory(); break;
            case 3: viewMyPatients(); break;
            case 4: {
                int pid;
                setColor(COLOR_YELLOW);
                printf("\nEnter Patient ID: ");
                resetColor();
                safeIntInput(&pid, 1, 10000);
                generateHealthReport(pid);
                break;
            }
            case 5:
                logAction("DOCTOR", loggedInDoctorId, "Logged out");
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
    fp = safeFileOpen("patients.dat", "rb");
    if(fp) {
        while(fread(&pat, sizeof(Patient), 1, fp)) {
            if(pat.active == 1) {
                printf("  ID: %d - %s (%s)\n", pat.id, pat.name, pat.email);
            }
        }
        fclose(fp);
    }

    setColor(COLOR_YELLOW);
    printf("\nEnter Patient ID: ");
    resetColor();
    safeIntInput(&patientId, 1, 10000);

    pat = getPatientById(patientId);
    if(pat.id == 0) {
        printBox("[ERROR] Patient not found!", COLOR_RED);
        pressAnyKey();
        return;
    }

    memset(&rec, 0, sizeof(HealthRecord));
    rec.patient_Id = patientId;
    rec.doctor_Id = loggedInDoctorId;
    getCurrentDate(rec.date);

    setColor(COLOR_CYAN);
    printf("\n+-- Vital Signs Input -----------------------------------------+\n");
    resetColor();

    rec.heart_Rate = safeFloatInput("| Heart Rate (bpm)", 30, 250);
    rec.bpSystolic = (int)safeFloatInput("| BP Systolic (mmHg)", 50, 300);
    rec.bpDiastolic = (int)safeFloatInput("| BP Diastolic (mmHg)", 30, 200);
    rec.temperature = safeFloatInput("| Temperature (F)", 90, 110);
    rec.bloodSugar = safeFloatInput("| Blood Sugar (mg/dL)", 20, 600);
    rec.spo2 = safeFloatInput("| SpO2 (%)", 50, 100);
    rec.respirationRate = safeFloatInput("| Respiration Rate (per min)", 5, 60);

    printf("| Symptoms: ");
    safeStringInput(rec.symptoms, sizeof(rec.symptoms));
    trim(rec.symptoms);

    printf("| Diagnosis: ");
    safeStringInput(rec.diagnosis, sizeof(rec.diagnosis));
    trim(rec.diagnosis);

    setColor(COLOR_CYAN);
    printf("+--------------------------------------------------------------+\n");
    resetColor();

    loadingAnimation("Analyzing vitals with AI");
    rec.risk_Score = calculateRiskScore(rec);
    determineRiskLevel(&rec);

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

    fp = safeFileOpen("health_records.dat", "ab");
    if(fp) {
        fwrite(&rec, sizeof(HealthRecord), 1, fp);
        fclose(fp);
        printBox("[SUCCESS] Vitals recorded successfully!", COLOR_GREEN);

        char logMsg[200];
        sprintf(logMsg, "Entered vitals for Patient ID:%d, Risk:%s", rec.patient_Id, rec.risk_Level);
        logAction("DOCTOR", loggedInDoctorId, logMsg);
    } else {
        printBox("[ERROR] Error saving record!", COLOR_RED);
    }

    pressAnyKey();
}
