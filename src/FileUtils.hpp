
 #ifndef __FILEUTILS_HPP__
 #define __FILEUTILS_HPP__

#include <fstream>

class FileUtils {
  public:
    // Endian Independent
    static bool       openBinary        (std::ifstream& file, std::string filename);
    static char       readByte          (std::ifstream& file);
    static uint8_t    readByteAsUINT8   (std::ifstream& file);
    static int8_t     readByteAsINT8    (std::ifstream& file);

    // Big Endian
    static uint16_t   readBytesAsUINT16 (std::ifstream& file);
    static int16_t    readBytesAsINT16  (std::ifstream& file);
};

 #endif // __FILEUTILS_HPP__
