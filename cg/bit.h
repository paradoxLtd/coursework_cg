#ifndef BIT_H
#define BIT_H

// Макросы для работы с битами
#define SET_BIT(word, bit_flag) \
    ((word) = ((word) | (bit_flag)))
#define RESET_BIT(word, bit_flag) \
    ((word) = ((word) & (~bit_flag)))


#endif // BIT_H
