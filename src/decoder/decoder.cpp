
#include <cstdint>

class Decoder {
private:
    uint8_t *buffer{nullptr};
public:
    int initDecoder(const char *fileName);
};





