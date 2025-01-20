#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <string>
#include <stdexcept>
#include <exception>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

class BackgroundProcess {
public:
    explicit BackgroundProcess(const std::string& program);
    ~BackgroundProcess();

    void run();
    int wait();

private:
    std::string program_;
    
#ifdef _WIN32
    PROCESS_INFORMATION processInfo_;
#else
    pid_t pid_;
#endif
};

#endif // BACKGROUND_HPP
