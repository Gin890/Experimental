/*  XoroShiro x8 (AVX512)
 *
 *  From: https://github.com/PokemonAutomation/
 *
 */

#ifndef PokemonAutomation_XoroShiro8_AVX512_H
#define PokemonAutomation_XoroShiro8_AVX512_H

#include <immintrin.h>
#include "Compiler.h"

namespace PokemonAutomation{

class XoroShiroX8{
public:
    PA_FORCE_INLINE XoroShiroX8(__m512i seed){
        state[0] = seed;
        state[1] = _mm512_set1_epi64(0x82A2B175229D6A5B);
    }

    PA_FORCE_INLINE __m512i get_int64(){
        return _mm512_add_epi64(state[0], state[1]);
    }
    PA_FORCE_INLINE __m512i get_int32(){
        return _mm512_and_si512(get_int64(), _mm512_set1_epi64(0x00000000ffffffff));
    }
    PA_FORCE_INLINE void next(){
        __m512i s0 = state[0];
        __m512i s1 = state[1];
        s1 = _mm512_xor_si512(s1, s0);

        s0 = _mm512_rol_epi64(s0, 24);
        state[1] = _mm512_rol_epi64(s1, 37);

        s1 = _mm512_xor_si512(s1, _mm512_slli_epi64(s1, 16));
        state[0] = _mm512_xor_si512(s0, s1);
    }

private:
    __m512i state[2];
};


}
#endif
