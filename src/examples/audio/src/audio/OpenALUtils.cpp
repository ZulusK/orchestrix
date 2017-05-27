#include <audio/OpenAL.h>

inline std::string GetOpenALErrorString(int errID) {
    if (errID == AL_NO_ERROR) {
        return "";
    }
    if (errID == AL_INVALID_NAME) {
        return "Invalid name";
    } else if (errID == AL_INVALID_ENUM) {
        return " Invalid enum ";
    } else if (errID == AL_INVALID_VALUE) {
        return " Invalid value ";
    } else if (errID == AL_INVALID_OPERATION) {
        return " Invalid operation ";
    } else if (errID == AL_OUT_OF_MEMORY) {
        return " Out of memory like! ";
    }
    return " Don't know ";
}

inline void CheckOpenALError(const char *stmt, int line) {
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cout << "OpenAL error " << err << " <" << GetOpenALErrorString(err) << " >";
        std::cout << "at " << line << "with " << std::string(stmt);
        abort();
    }
};




