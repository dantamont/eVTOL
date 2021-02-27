/////////////////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef J_STRING_H
#define J_STRING_H

// std
#include <string>


namespace joby {
/////////////////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Type Defs
/////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
// Class definitions
/////////////////////////////////////////////////////////////////////////////////////////////
/// @class JString
/// @brief Class with string helper methods
class JString {
public:

    //--------------------------------------------------------------------------------------------
    /// @name Static
    /// @{

    /// @brief Convert a hex string to an unsigned integer
    static size_t HexToInt(const char* s) {
        return strtoul(s, nullptr, 16);
    }

    /// @brief Reentrant version of string tokenization
    /// @param[in] savePtr A pointer used to avoid a static char* in the implementation of strtok, must be passed as a reference to modify the original ptr
    static char* Strtok_r(char* str, const char* delim, char*& savePtr) {
        char* tok = nullptr;
        char* match = nullptr;

        // If the delimiter is invalid, return nullptr
        if (delim == nullptr) {
            return nullptr;
        }

        // If the input string is null, strtok resumes from the most recent location (saveptr)
        tok = (str) ? str : savePtr;
        if (tok == nullptr) {
            return nullptr;
        }

        // Find the first match of the delimiter token in the string
        match = strstr(tok, delim);

        // TODO: Create a strtok version that doesn't even modify the original str
        if (match) {
            savePtr = match + strlen(delim);
            match[0] = '\0';
        }
        else {
            savePtr = nullptr;
        }

        return tok;
    }

    /// @brief Format a std::string like a const char*        
    /// @details Write to a char* using std;:snprintf and then convert to a std::string
    /// @note See https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
    template<typename ... Args>
    static std::string Format(const std::string& format, Args ... args)
    {
        // Check formatting with a null char pointer, to avoid silent errors
        int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size <= 0) { throw std::runtime_error("Error during formatting."); }

        // Allocate a buffer of the appropriate size
        std::string str(size - 1, ' '); // Don't need the null character at end, so subtract 1 from size
        snprintf(&str[0], size, format.c_str(), args ...); // Need to write full size, or lose last character
        return str; 
    }


    /// @}
};

/////////////////////////////////////////////////////////////////////////////////////////////
} // End namespace


#endif