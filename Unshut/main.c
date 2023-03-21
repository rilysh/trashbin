#include <stdio.h>
#include <string.h>
#include <windows.h>

// Oh yeah...just realized policymanager isn't available on win7...
#define DEFAULT_IMAGE_FILE_PATH     "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\shutdown.exe"
#define DEFAULT_HIDE_SHUTDOWN       "SOFTWARE\\Microsoft\\PolicyManager\\default\\Start\\HideShutDown"
#define DEFAULT_HIDE_RESTART        "SOFTWARE\\Microsoft\\PolicyManager\\default\\Start\\HideRestart"
#define DEFAULT_HIDE_HIBERNATE      "SOFTWARE\\Microsoft\\PolicyManager\\default\\Start\\HideHibernate"
#define DEFAULT_HIDE_SLEEP          "SOFTWARE\\Microsoft\\PolicyManager\\default\\Start\\HideSleep"
#define DEFAULT_HIDE_POWERBUTTON    "SOFTWARE\\Microsoft\\PolicyManager\\default\\Start\\HidePowerButton"

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("oh no...\n");
        return 0;
    }

    HKEY hKey;
    LSTATUS lResult;
    LPCVOID data;

    if (!strcmp(argv[1], "/activate") || !strcmp(argv[1], "--activate")) {
        data = "0";

        lResult = RegCreateKeyEx(
            HKEY_LOCAL_MACHINE, DEFAULT_IMAGE_FILE_PATH,
            0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL
        );

        if (lResult != ERROR_SUCCESS) {
            MessageBoxA(NULL, "RegCreateKeyEx failed!", "Unshut", MB_OK | MB_ICONERROR);

            return 1;
        }

        lResult = RegSetKeyValueA(
            HKEY_LOCAL_MACHINE, DEFAULT_IMAGE_FILE_PATH,
            "Debugger", REG_SZ, data, 1
        );

        if (lResult != ERROR_SUCCESS) {
            MessageBoxA(NULL, "RegSetKeyValue failed!", "Unshut", MB_OK | MB_ICONERROR);

            return 1;
        }

        RegCloseKey(hKey);
    } else if (!strcmp(argv[1], "/deactivate") || !strcmp(argv[1], "--deactivate")) {
        lResult = RegDeleteKeyA(
            HKEY_LOCAL_MACHINE, DEFAULT_IMAGE_FILE_PATH
        );

        if (lResult != ERROR_SUCCESS) {
            MessageBoxA(NULL, "RegDeleteKey failed!", "Unshut", MB_OK | MB_ICONERROR);

            return 1;
        }

        RegCloseKey(hKey);
    } else {
        printf("Invalid arguments!\n");
        return 1;
    }
}
