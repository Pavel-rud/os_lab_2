#include "background.hpp"
#include <iostream>
#include <string>

void run_background_process(const std::string& programPath) {
    try {
        BackgroundProcess bg(programPath);
        bg.run();
        int exitCode = bg.wait();
        std::cout << "Program exited with code: " << exitCode << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }   
}

int main(int argc, char** argv) {
    std::string defaultProgramPath;

#ifdef _WIN32
    defaultProgramPath = "..\\subprogram.exe";
#else
    defaultProgramPath = "ps aux";
#endif

    std::string programPath = (argc > 1) ? argv[1] : defaultProgramPath;

    run_background_process(programPath);

    return 0;
}
