//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_font.h"

#ifdef USE_FONT_5x8

const uint16_t Font_5x8_Table [] = {
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // Ascii = [ ]
0x05,0x00,0x04,0x04,0x04,0x04,0x00,0x04,0x00,  // Ascii = [!]
0x05,0x00,0x0A,0x0A,0x0A,0x00,0x00,0x00,0x00,  // Ascii = ["]
0x05,0x0A,0x0A,0x1F,0x0A,0x1F,0x0A,0x0A,0x00,  // Ascii = [#]
0x05,0x04,0x0E,0x14,0x0E,0x28,0x0E,0x04,0x00,  // Ascii = [$]
0x05,0x00,0x08,0x0A,0x04,0x0A,0x02,0x00,0x00,  // Ascii = [%]
0x05,0x08,0x14,0x14,0x08,0x14,0x14,0x0A,0x00,  // Ascii = [&]
0x05,0x00,0x04,0x04,0x04,0x00,0x00,0x00,0x00,  // Ascii = [']
0x05,0x00,0x04,0x08,0x08,0x08,0x08,0x04,0x00,  // Ascii = [(]
0x05,0x00,0x08,0x04,0x04,0x04,0x04,0x08,0x00,  // Ascii = [)]
0x05,0x00,0x00,0x12,0x0C,0x1E,0x0C,0x12,0x00,  // Ascii = [*]
0x05,0x00,0x00,0x04,0x04,0x1F,0x04,0x04,0x00,  // Ascii = [+]
0x05,0x00,0x00,0x00,0x00,0x00,0x06,0x04,0x08,  // Ascii = [,]
0x05,0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,  // Ascii = [-]
0x05,0x00,0x00,0x00,0x00,0x00,0x04,0x0E,0x04,  // Ascii = [.]
0x05,0x00,0x02,0x02,0x04,0x08,0x10,0x10,0x00,  // Ascii = [/]
0x05,0x00,0x04,0x0A,0x0A,0x0A,0x0A,0x04,0x00,  // Ascii = [0]
0x05,0x00,0x04,0x0C,0x04,0x04,0x04,0x0E,0x00,  // Ascii = [1]
0x05,0x00,0x0C,0x12,0x02,0x0C,0x10,0x1E,0x00,  // Ascii = [2]
0x05,0x00,0x1E,0x04,0x0C,0x02,0x12,0x0C,0x00,  // Ascii = [3]
0x05,0x00,0x04,0x0C,0x14,0x1E,0x04,0x04,0x00,  // Ascii = [4]
0x05,0x00,0x1E,0x10,0x1C,0x02,0x12,0x0C,0x00,  // Ascii = [5]
0x05,0x00,0x0C,0x10,0x1C,0x12,0x12,0x0C,0x00,  // Ascii = [6]
0x05,0x00,0x1E,0x02,0x04,0x04,0x08,0x08,0x00,  // Ascii = [7]
0x05,0x00,0x0C,0x12,0x0C,0x12,0x12,0x0C,0x00,  // Ascii = [8]
0x05,0x00,0x0C,0x12,0x12,0x0E,0x02,0x0C,0x00,  // Ascii = [9]
0x05,0x00,0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00,  // Ascii = [:]
0x05,0x00,0x00,0x06,0x06,0x00,0x06,0x04,0x08,  // Ascii = [;]
0x05,0x00,0x02,0x04,0x08,0x08,0x04,0x02,0x00,  // Ascii = [<]
0x05,0x00,0x00,0x00,0x1E,0x00,0x1E,0x00,0x00,  // Ascii = [=]
0x05,0x00,0x08,0x04,0x02,0x02,0x04,0x08,0x00,  // Ascii = [>]
0x05,0x00,0x04,0x0A,0x02,0x04,0x00,0x04,0x00,  // Ascii = [?]
0x05,0x06,0x48,0x98,0x15,0x15,0x12,0x08,0x06,  // Ascii = [@]
0x05,0x00,0x0C,0x12,0x12,0x1E,0x12,0x12,0x00,  // Ascii = [A]
0x05,0x00,0x1C,0x12,0x1C,0x12,0x12,0x1C,0x00,  // Ascii = [B]
0x05,0x00,0x0C,0x12,0x10,0x10,0x12,0x0C,0x00,  // Ascii = [C]
0x05,0x00,0x1C,0x12,0x12,0x12,0x12,0x1C,0x00,  // Ascii = [D]
0x05,0x00,0x1E,0x10,0x1C,0x10,0x10,0x1E,0x00,  // Ascii = [E]
0x05,0x00,0x1E,0x10,0x1C,0x10,0x10,0x10,0x00,  // Ascii = [F]
0x05,0x00,0x0C,0x12,0x10,0x16,0x12,0x0C,0x00,  // Ascii = [G]
0x05,0x00,0x12,0x12,0x1E,0x12,0x12,0x12,0x00,  // Ascii = [H]
0x05,0x00,0x0E,0x04,0x04,0x04,0x04,0x0E,0x00,  // Ascii = [I]
0x05,0x00,0x0E,0x04,0x04,0x04,0x14,0x08,0x00,  // Ascii = [J]
0x05,0x00,0x12,0x14,0x18,0x14,0x14,0x12,0x00,  // Ascii = [K]
0x05,0x00,0x10,0x10,0x10,0x10,0x10,0x1E,0x00,  // Ascii = [L]
0x05,0x00,0x12,0x1E,0x1E,0x12,0x12,0x12,0x00,  // Ascii = [M]
0x05,0x00,0x12,0xD0,0x1E,0x16,0x16,0x12,0x00,  // Ascii = [N]
0x05,0x00,0x0C,0x12,0x12,0x12,0x12,0x0C,0x00,  // Ascii = [O]
0x05,0x00,0x1C,0x12,0x12,0x1C,0x10,0x10,0x00,  // Ascii = [P]
0x05,0x00,0x0C,0x12,0x12,0xD0,0x16,0x0C,0x02,  // Ascii = [Q]
0x05,0x00,0x1C,0x12,0x12,0x1C,0x12,0x12,0x00,  // Ascii = [R]
0x05,0x00,0x0C,0x12,0x08,0x04,0x12,0x0C,0x00,  // Ascii = [S]
0x05,0x00,0x0E,0x04,0x04,0x04,0x04,0x04,0x00,  // Ascii = [T]
0x05,0x00,0x12,0x12,0x12,0x12,0x12,0x0C,0x00,  // Ascii = [U]
0x05,0x00,0x12,0x12,0x12,0x12,0x0C,0x0C,0x00,  // Ascii = [V]
0x05,0x00,0x12,0x12,0x12,0x1E,0x1E,0x12,0x00,  // Ascii = [W]
0x05,0x00,0x12,0x12,0x0C,0x0C,0x12,0x12,0x00,  // Ascii = [X]
0x05,0x00,0x11,0x11,0x0A,0x04,0x04,0x04,0x00,  // Ascii = [Y]
0x05,0x00,0x1E,0x02,0x04,0x08,0x10,0x1E,0x00,  // Ascii = [Z]
0x05,0x00,0x0E,0x08,0x08,0x08,0x08,0x0E,0x00,  // Ascii = [[]
0x05,0x00,0x10,0x10,0x08,0x04,0x02,0x02,0x00,  // Ascii = [\]
0x05,0x00,0x0E,0x02,0x02,0x02,0x02,0x0E,0x00,  // Ascii = []]
0x05,0x00,0x04,0x0A,0x00,0x00,0x00,0x00,0x00,  // Ascii = [^]
0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,  // Ascii = [_]
0x05,0x00,0x08,0x04,0x00,0x00,0x00,0x00,0x00,  // Ascii = [`]
0x05,0x00,0x00,0x00,0x0E,0x12,0x12,0x0E,0x00,  // Ascii = [a]
0x05,0x00,0x10,0x10,0x1C,0x12,0x12,0x1C,0x00,  // Ascii = [b]
0x05,0x00,0x00,0x00,0x06,0x08,0x08,0x06,0x00,  // Ascii = [c]
0x05,0x00,0x02,0x02,0x0E,0x12,0x12,0x0E,0x00,  // Ascii = [d]
0x05,0x00,0x00,0x00,0x0C,0x16,0x18,0x0C,0x00,  // Ascii = [e]
0x05,0x00,0x04,0x0A,0x08,0x1C,0x08,0x08,0x00,  // Ascii = [f]
0x05,0x00,0x00,0x00,0x0C,0x12,0x0E,0x02,0x0C,  // Ascii = [g]
0x05,0x00,0x10,0x10,0x1C,0x12,0x12,0x12,0x00,  // Ascii = [h]
0x05,0x00,0x04,0x00,0x0C,0x04,0x04,0x0E,0x00,  // Ascii = [i]
0x05,0x00,0x02,0x00,0x02,0x02,0x02,0x0A,0x04,  // Ascii = [j]
0x05,0x00,0x10,0x10,0x12,0x1C,0x12,0x12,0x00,  // Ascii = [k]
0x05,0x00,0x0C,0x04,0x04,0x04,0x04,0x0E,0x00,  // Ascii = [l]
0x05,0x00,0x00,0x00,0xD0,0x15,0x15,0x15,0x00,  // Ascii = [m]
0x05,0x00,0x00,0x00,0x1C,0x12,0x12,0x12,0x00,  // Ascii = [n]
0x05,0x00,0x00,0x00,0x0C,0x12,0x12,0x0C,0x00,  // Ascii = [o]
0x05,0x00,0x00,0x00,0x1C,0x12,0x1C,0x10,0x10,  // Ascii = [p]
0x05,0x00,0x00,0x00,0x0E,0x12,0x0E,0x02,0x02,  // Ascii = [q]
0x05,0x00,0x00,0x00,0x14,0xD0,0x10,0x10,0x00,  // Ascii = [r]
0x05,0x00,0x00,0x00,0x06,0x0C,0x02,0x0C,0x00,  // Ascii = [s]
0x05,0x00,0x08,0x08,0x1C,0x08,0x0A,0x04,0x00,  // Ascii = [t]
0x05,0x00,0x00,0x00,0x12,0x12,0x12,0x0E,0x00,  // Ascii = [u]
0x05,0x00,0x00,0x00,0x0A,0x0A,0x0A,0x04,0x00,  // Ascii = [v]
0x05,0x00,0x00,0x00,0x11,0x15,0x15,0x0A,0x00,  // Ascii = [w]
0x05,0x00,0x00,0x00,0x12,0x0C,0x0C,0x12,0x00,  // Ascii = [x]
0x05,0x00,0x00,0x00,0x12,0x12,0x0E,0x12,0x0C,  // Ascii = [y]
0x05,0x00,0x00,0x00,0x1E,0x04,0x08,0x1E,0x00,  // Ascii = [z]
0x05,0x06,0x08,0x04,0x18,0x04,0x08,0x06,0x00,  // Ascii = [{]
0x05,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x00,  // Ascii = [|]
0x05,0x18,0x04,0x08,0x06,0x08,0x04,0x18,0x00,  // Ascii = [}]
0x05,0x00,0x0A,0x14,0x00,0x00,0x00,0x00,0x00   // Ascii = [~]
};

//--------------------------------------------------------------
// ?????????????????? ????????????
//--------------------------------------------------------------
UB_pFont Font_5x8 = {
  8,               // ????????????  (in Pixel)
  32,              // ?????????????????? ???????????? (Ascii)
  126,             // ???????????????? ???????????? (Ascii)
  Font_5x8_Table,  // ???????????? ????????????
};

#endif //USE_FONT_5x8
