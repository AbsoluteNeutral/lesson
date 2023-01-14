#ifndef DDD_ENDIAN_H_
#define DDD_ENDIAN_H_

namespace ddd
{
    bool IsLittleEndian();
    
    unsigned    FlipEndian  (unsigned number);
    int         FlipEndian  (int number);
    float       FlipEndian  (float number);

    unsigned long   FlipEndian  (unsigned long number);
    long            FlipEndian  (long number);
    double          FlipEndian  (double number);
}

#endif //DDD_ENDIAN_H_
