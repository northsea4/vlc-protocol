#define _WIN32_WINNT 0x0600
#define _WIN32_IE 0x0600

#include <windows.h>
#include <shlwapi.h>
#include <wininet.h>
#include <time.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define WEBLINK_PREFIX L"vlc://weblink?url="
#define LOG_FILE L"vlc-protocol.log"
#define MAX_URL 2048

// Global variable: indicates whether the console was successfully attached
BOOL g_has_console = FALSE;

// Initialize console
void init_console() {
    // Try to attach to the parent process console that launched this program (e.g., CMD, PowerShell, MSYS2 Bash)
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        g_has_console = TRUE;
        
        // Redirect standard output (stdout) and standard error (stderr) to the attached console
        FILE* dummy;
        freopen_s(&dummy, "CONOUT$", "w", stdout);
        freopen_s(&dummy, "CONOUT$", "w", stderr);
        
        // Disable stdout buffering to ensure logs are immediately flushed to the terminal
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
    }
}

// 日志函数
void log_message(const wchar_t* format, ...) {
    wchar_t timestamp[64];
    wchar_t message[4096];
    time_t now;
    struct tm* tm_info;
    va_list args;
    
    time(&now);
    tm_info = localtime(&now);
    wcsftime(timestamp, sizeof(timestamp)/sizeof(wchar_t), L"%Y-%m-%d %H:%M:%S", tm_info);
    
    va_start(args, format);
    _vsnwprintf(message, sizeof(message)/sizeof(wchar_t), format, args);
    va_end(args);
    
    // 写入日志文件
    wchar_t log_path[MAX_PATH];
    GetTempPathW(MAX_PATH, log_path);
    wcscat(log_path, LOG_FILE);
    
    FILE* f = _wfopen(log_path, L"a");
    if (f) {
        fwprintf(f, L"[%ls] %ls\n", timestamp, message);
        fclose(f);
    }
    
    // If console was attached, output log directly to the terminal
    if (g_has_console) {
        wprintf(L"[%ls] %ls\n", timestamp, message);
        fflush(stdout);
    }
}

// URL 解码
wchar_t* decode_url(const wchar_t* encoded_url) {
    wchar_t* decoded = (wchar_t*)calloc(MAX_URL, sizeof(wchar_t));
    DWORD decoded_length = MAX_URL;
    
    if (!decoded) {
        log_message(L"Error: Failed to allocate memory for URL decoding");
        return NULL;
    }
    
    if (InternetCanonicalizeUrlW(encoded_url, decoded, &decoded_length, ICU_DECODE | ICU_NO_ENCODE)) {
        log_message(L"URL decoded successfully");
        return decoded;
    }
    
    DWORD error = GetLastError();
    log_message(L"Error: Failed to decode URL (error code: %lu)", error);
    free(decoded);
    return NULL;
}

// 修复损坏的 URL
wchar_t* fix_broken_url(wchar_t* url) {
    log_message(L"Fixing URL: %ls", url);
    
    if (wcsncmp(url, L"http//", 6) == 0) {
        log_message(L"Found broken http URL format");
        // 在原字符串中插入 ":"
        size_t len = wcslen(url);
        memmove(url + 6, url + 5, (len - 5 + 1) * sizeof(wchar_t));  // +1 for null terminator
        url[4] = L':';
        log_message(L"Fixed http URL: %ls", url);
    }
    else if (wcsncmp(url, L"https//", 7) == 0) {
        log_message(L"Found broken https URL format");
        // 在原字符串中插入 ":"
        size_t len = wcslen(url);
        memmove(url + 7, url + 6, (len - 6 + 1) * sizeof(wchar_t));  // +1 for null terminator
        url[5] = L':';
        log_message(L"Fixed https URL: %ls", url);
    }
    return url;
}

// 检查URL是否合法
BOOL is_valid_url(const wchar_t* url) {
    return url && wcslen(url) > 0 && (wcsstr(url, L"http://") == url || wcsstr(url, L"https://") == url);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Initialize console attachment logic
    init_console();
    
    log_message(L"Starting VLC Protocol Handler");
    log_message(L"Command line: %ls", pCmdLine);
    
    if (wcslen(pCmdLine) < 10) {
        log_message(L"Error: Command line too short");
        return 1;
    }

    // Handle quotes
    if (pCmdLine[0] == '"') {
        pCmdLine++;
        if (pCmdLine[wcslen(pCmdLine)-1] == '"') {
            pCmdLine[wcslen(pCmdLine)-1] = 0;
        }
    }

    wchar_t* url = _wcsdup(pCmdLine);
    wchar_t* final_url = NULL;

    // Remove vlc:// prefix
    if (wcsncmp(url, L"vlc://", 6) == 0) {
        wcscpy(url, url + 6);
        log_message(L"Removed vlc:// prefix: %ls", url);
    }

    // Handle weblink format
    if (wcsncmp(url, L"weblink?url=", 11) == 0 || wcsncmp(url, L"weblink/?url=", 12) == 0) {
        wchar_t* weblink_url = wcsstr(url, L"url=");
        if (weblink_url) {
            weblink_url += 4;  // Skip "url="
            log_message(L"Extracting weblink URL: %ls", weblink_url);
            
            // URL decode
            wchar_t* decoded = decode_url(weblink_url);
            if (!decoded) {
                log_message(L"Error: URL decoding failed");
                free(url);
                return 1;
            }
            
            final_url = decoded;
            log_message(L"Decoded URL: %ls", final_url);
        } else {
            log_message(L"Error: Invalid weblink format");
            free(url);
            return 1;
        }
        free(url);
    } else {
        final_url = fix_broken_url(url);
    }

    // 检查URL合法性
    if (!is_valid_url(final_url)) {
        log_message(L"Error: Invalid URL: %ls", final_url);
        free(final_url);
        return 1;
    }

    // 确保空格被编码
    for (wchar_t* p = final_url; *p; p++) {
        if (*p == L' ') *p = L'+';
    }

    // 获取 VLC 路径
    wchar_t path[MAX_PATH];
    DWORD path_size = sizeof(path);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\VideoLAN\\VLC", L"InstallDir", RRF_RT_REG_SZ, NULL, path, &path_size) != ERROR_SUCCESS) {
        log_message(L"Error: Failed to get VLC path from registry");
        free(final_url);
        return 1;
    }
    wcscat(path, L"\\vlc.exe");

    log_message(L"VLC path: %ls", path);

    // 构建命令行参数
    wchar_t* args = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(final_url) + 64));
    wcscpy(args, L"--open \"");
    wcscat(args, final_url);
    wcscat(args, L"\"");

    log_message(L"Arguments: %ls", args);

    // Start vlc.exe
    int ret = (INT_PTR)ShellExecute(NULL, NULL, path, args, NULL, SW_SHOWNORMAL);
    if (ret <= 32) {
        log_message(L"Error: Failed to start VLC (error code: %d)", ret);
        free(args);
        free(final_url);
        return ret;
    }

    log_message(L"VLC started successfully");
    free(args);
    free(final_url);
    return 0;
}
