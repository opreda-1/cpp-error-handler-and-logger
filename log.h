using namespace std;

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <string>

// Logger class handles optional logging to file with timestamps
class Logger 
{
public:

    bool is_windows()
    {
        #if defined(_WIN32) || defined(_WIN64)
            return true;
        #else
            return false;
        #endif
    }


    Logger() = default;

    // Initialize logging if "--log" or "/log" is present in args
    void init(int argc, char* argv[]) 
    {
        for (int i = 1; i < argc; i++) 
        {
            if (string(argv[i]) == "--log" && !is_windows() || string(argv[i]) == "/log" && is_windows()) 
            {
                enabled = true;
                open_log_file();
                break;
            }
        }
    }

    // Log a message with a timestamp
    const void log(const string& message) 
    {
        if (enabled && logFile.is_open()) 
        {
            logFile << current_time_stamp() << " - " << message << '\n';
        }
    }

    // Cleanup
    ~Logger() 
    {
        if (logFile.is_open()) 
        {
            logFile.close();
        }
    }

private:

    bool enabled = false;
    mutable ofstream logFile;

    // Open a log file named with current date-time
    void open_log_file() 
    {
        time_t now = time(nullptr);
        tm* tm_info = localtime(&now);

        ostringstream filename;
        filename << "log_" << put_time(tm_info, "%Y-%m-%d_%H-%M-%S") << ".txt";

        logFile.open(filename.str(), ios::out); // use ios::app if you want to keep appending
    }

    const static string current_time_stamp() 
    {
        time_t now = time(nullptr);
        tm* tm_info = localtime(&now);

        ostringstream ss;
        ss << put_time(tm_info, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

// External logger instance (defined in a separate .cpp file)
extern Logger logger;

// Convenience macro for logging
#define LOG(msg) logger.log(msg)

#endif
