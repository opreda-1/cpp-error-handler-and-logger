using namespace std;

#ifndef ERROR_HANDLER
#define ERROR_HANDLER

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "log.h"       // Include logging system (uses LOG macro)

// The Handler class manages error and warning reporting,
// including printing to console and logging to file.
class Handler
{
public:
    Handler() {}

    // Enum representing different error types.
    // You can expand this list as needed.
    enum class error_types
    {
        error_one // These are examples, change them.
    };

    // Enum representing different warning types.
    enum class warning_types
    {
        warning_one
    };

    // Handles warnings: prints to console and logs to file.
    static void Warning_Handler(warning_types type)
    {
        string log_message;

        switch (type)
        {
        case warning_types::warning_one:
            // Show warning message on screen
            cerr << "Warning: " << "<Put warning message here>\n";

            // Message to be logged
            log_message = "<Put warning message to log here>";
            break;
        }

        // Log the warning (writes to timestamped file if enabled)
        LOG(log_message);
    }

    // Handles errors: prints to console, logs to file, and exits if fatal.
    static void Error_Handler(error_types type, bool is_fatal)
    {
        string log_message;

        switch (type)
        {
        default:
            // Unknown error fallback
            cerr << "An unknown error occurred.\n";
            log_message = "An unkown error occurred.";
            break;

        case error_types::error_one:
            // Show error on screen
            cerr << "Error: " << "<Put Error message here>";
            log_message = "Error: <Put Error message to log here>";
            break;
        }

        // Log the error message
        LOG(log_message);

        // Exit the program if the error is fatal
        if (is_fatal)
        {
            exit(1);
        }
    }
};

#endif // ERROR_HANDLER
