// https://iq.opengenus.org/detect-operating-system-in-c/


#ifdef _WIN64
# define OS "windows 64bit"
#elif __linux__
# define OS "linux"
#elif __APPLE__
# define OS "apple"
#endif
