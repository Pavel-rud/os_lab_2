#include "background.hpp"

BackgroundProcess::BackgroundProcess(const std::string& program)
    : program_(program) {
#ifdef _WIN32
    ZeroMemory(&processInfo_, sizeof(processInfo_));
#endif
}

BackgroundProcess::~BackgroundProcess() {
#ifdef _WIN32
    if (processInfo_.hProcess) {
        CloseHandle(processInfo_.hProcess);
    }
    if (processInfo_.hThread) {
        CloseHandle(processInfo_.hThread);
    }
#endif
}

void BackgroundProcess::run() {
#ifdef _WIN32
    STARTUPINFO startupInfo = {0};
    startupInfo.cb = sizeof(startupInfo);

    if (!CreateProcess(NULL, const_cast<char*>(program_.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo_)) {
        throw std::runtime_error("Failed to launch program");
    }
#else
    pid_ = fork();
    if (pid_ == 0) {
        execl("/bin/sh", "sh", "-c", program_.c_str(), (char*)nullptr);
        _exit(1); // Чтобы избежать продолжения выполнения в случае ошибки execl
    } else if (pid_ < 0) {
        throw std::runtime_error("Failed to fork process");
    }
#endif
}

int BackgroundProcess::wait() {
#ifdef _WIN32
    WaitForSingleObject(processInfo_.hProcess, INFINITE);
    DWORD exitCode;
    GetExitCodeProcess(processInfo_.hProcess, &exitCode);
    return static_cast<int>(exitCode);
#else
    int status;
    waitpid(pid_, &status, 0);
    return WEXITSTATUS(status);
#endif
}
