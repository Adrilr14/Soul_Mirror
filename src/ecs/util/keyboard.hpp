#include <X11/X.h>
#include <X11/keysym.h>
#include <unordered_map>

 


struct Keyboard_t {
    
    explicit Keyboard_t() = default;

    using OptIter = std::optional<std::unordered_map<KeySym,bool>::iterator>;

    Keyboard_t(const Keyboard_t&)           = delete;
    Keyboard_t(Keyboard_t&&)                = delete;
    Keyboard_t& operator=(const Keyboard_t) = delete;
    Keyboard_t& operator=(Keyboard_t&&)     = delete;

    bool isKeyPressed(KeySym k) noexcept;
    void keyPressed(KeySym k) noexcept {
        if(auto it = getIterator(k)){
            (*it)->second = true;
        }
    }

    void keyReleased(KeySym k) noexcept {
        if(auto it = getIterator(k)){
            (*it)->second = false;
        }
    }



private:
    OptIter getIterator(KeySym s) noexcept;
    std::unordered_map<KeySym,bool> m_pressedKeys {
          { XK_BackSpace                      , false}  /* Back space, back char */
        , { XK_Tab                            , false}
        , { XK_Linefeed                       , false}  /* Linefeed, LF */
        , { XK_Clear                          , false}
        , { XK_Return                         , false}  /* Return, enter */
        , { XK_Pause                          , false}  /* Pause, hold */
        , { XK_Scroll_Lock                    , false}
        , { XK_Sys_Req                        , false}
        , { XK_Escape                         , false}
        , { XK_Delete                         , false}  /* Delete, rubout */
        , { XK_Home                           , false}
        , { XK_Left                           , false}  /* Move left, left arrow */
        , { XK_Up                             , false}  /* Move up, up arrow */
        , { XK_Right                          , false}  /* Move right, right arrow */
        , { XK_Down                           , false}  /* Move down, down arrow */
        , { XK_Prior                          , false}  /* Prior, previous */
        , { XK_Page_Up                        , false}
        , { XK_Next                           , false}  /* Next */
        , { XK_Page_Down                      , false}
        , { XK_End                            , false}  /* EOL */
        , { XK_Begin                          , false}  /* BOL */
        , { XK_space                          , false}  /* U+0020 SPACE */
        , { XK_exclam                         , false}  /* U+0021 EXCLAMATION MARK */
        , { XK_quotedbl                       , false}  /* U+0022 QUOTATION MARK */
        , { XK_numbersign                     , false}  /* U+0023 NUMBER SIGN */
        , { XK_dollar                         , false}  /* U+0024 DOLLAR SIGN */
        , { XK_percent                        , false}  /* U+0025 PERCENT SIGN */
        , { XK_ampersand                      , false}  /* U+0026 AMPERSAND */
        , { XK_apostrophe                     , false}  /* U+0027 APOSTROPHE */
        , { XK_quoteright                     , false}  /* deprecated */
        , { XK_parenleft                      , false}  /* U+0028 LEFT PARENTHESIS */
        , { XK_parenright                     , false}  /* U+0029 RIGHT PARENTHESIS */
        , { XK_asterisk                       , false}  /* U+002A ASTERISK */
        , { XK_plus                           , false}  /* U+002B PLUS SIGN */
        , { XK_comma                          , false}  /* U+002C COMMA */
        , { XK_minus                          , false}  /* U+002D HYPHEN-MINUS */
        , { XK_period                         , false}  /* U+002E FULL STOP */
        , { XK_slash                          , false}  /* U+002F SOLIDUS */
        , { XK_0                              , false}  /* U+0030 DIGIT ZERO */
        , { XK_1                              , false}  /* U+0031 DIGIT ONE */
        , { XK_2                              , false}  /* U+0032 DIGIT TWO */
        , { XK_3                              , false}  /* U+0033 DIGIT THREE */
        , { XK_4                              , false}  /* U+0034 DIGIT FOUR */
        , { XK_5                              , false}  /* U+0035 DIGIT FIVE */
        , { XK_6                              , false}  /* U+0036 DIGIT SIX */
        , { XK_7                              , false}  /* U+0037 DIGIT SEVEN */
        , { XK_8                              , false}  /* U+0038 DIGIT EIGHT */
        , { XK_9                              , false}  /* U+0039 DIGIT NINE */
        , { XK_colon                          , false}  /* U+003A COLON */
        , { XK_semicolon                      , false}  /* U+003B SEMICOLON */
        , { XK_less                           , false}  /* U+003C LESS-THAN SIGN */
        , { XK_equal                          , false}  /* U+003D EQUALS SIGN */
        , { XK_greater                        , false}  /* U+003E GREATER-THAN SIGN */
        , { XK_question                       , false}  /* U+003F QUESTION MARK */
        , { XK_at                             , false}  /* U+0040 COMMERCIAL AT */
        , { XK_A                              , false}  /* U+0041 LATIN CAPITAL LETTER A */
        , { XK_B                              , false}  /* U+0042 LATIN CAPITAL LETTER B */
        , { XK_C                              , false}  /* U+0043 LATIN CAPITAL LETTER C */
        , { XK_D                              , false}  /* U+0044 LATIN CAPITAL LETTER D */
        , { XK_E                              , false}  /* U+0045 LATIN CAPITAL LETTER E */
        , { XK_F                              , false}  /* U+0046 LATIN CAPITAL LETTER F */
        , { XK_G                              , false}  /* U+0047 LATIN CAPITAL LETTER G */
        , { XK_H                              , false}  /* U+0048 LATIN CAPITAL LETTER H */
        , { XK_I                              , false}  /* U+0049 LATIN CAPITAL LETTER I */
        , { XK_J                              , false}  /* U+004A LATIN CAPITAL LETTER J */
        , { XK_K                              , false}  /* U+004B LATIN CAPITAL LETTER K */
        , { XK_L                              , false}  /* U+004C LATIN CAPITAL LETTER L */
        , { XK_M                              , false}  /* U+004D LATIN CAPITAL LETTER M */
        , { XK_N                              , false}  /* U+004E LATIN CAPITAL LETTER N */
        , { XK_O                              , false}  /* U+004F LATIN CAPITAL LETTER O */
        , { XK_P                              , false}  /* U+0050 LATIN CAPITAL LETTER P */
        , { XK_Q                              , false}  /* U+0051 LATIN CAPITAL LETTER Q */
        , { XK_R                              , false}  /* U+0052 LATIN CAPITAL LETTER R */
        , { XK_S                              , false}  /* U+0053 LATIN CAPITAL LETTER S */
        , { XK_T                              , false}  /* U+0054 LATIN CAPITAL LETTER T */
        , { XK_U                              , false}  /* U+0055 LATIN CAPITAL LETTER U */
        , { XK_V                              , false}  /* U+0056 LATIN CAPITAL LETTER V */
        , { XK_W                              , false}  /* U+0057 LATIN CAPITAL LETTER W */
        , { XK_X                              , false}  /* U+0058 LATIN CAPITAL LETTER X */
        , { XK_Y                              , false}  /* U+0059 LATIN CAPITAL LETTER Y */
        , { XK_Z                              , false}  /* U+005A LATIN CAPITAL LETTER Z */
        , { XK_bracketleft                    , false}  /* U+005B LEFT SQUARE BRACKET */
        , { XK_backslash                      , false}  /* U+005C REVERSE SOLIDUS */
        , { XK_bracketright                   , false}  /* U+005D RIGHT SQUARE BRACKET */
        , { XK_asciicircum                    , false}  /* U+005E CIRCUMFLEX ACCENT */
        , { XK_underscore                     , false}  /* U+005F LOW LINE */
        , { XK_grave                          , false}  /* U+0060 GRAVE ACCENT */
        , { XK_quoteleft                      , false}  /* deprecated */
        , { XK_a                              , false}  /* U+0061 LATIN SMALL LETTER A */
        , { XK_b                              , false}  /* U+0062 LATIN SMALL LETTER B */
        , { XK_c                              , false}  /* U+0063 LATIN SMALL LETTER C */
        , { XK_d                              , false}  /* U+0064 LATIN SMALL LETTER D */
        , { XK_e                              , false}  /* U+0065 LATIN SMALL LETTER E */
        , { XK_f                              , false}  /* U+0066 LATIN SMALL LETTER F */
        , { XK_g                              , false}  /* U+0067 LATIN SMALL LETTER G */
        , { XK_h                              , false}  /* U+0068 LATIN SMALL LETTER H */
        , { XK_i                              , false}  /* U+0069 LATIN SMALL LETTER I */
        , { XK_j                              , false}  /* U+006A LATIN SMALL LETTER J */
        , { XK_k                              , false}  /* U+006B LATIN SMALL LETTER K */
        , { XK_l                              , false}  /* U+006C LATIN SMALL LETTER L */
        , { XK_m                              , false}  /* U+006D LATIN SMALL LETTER M */
        , { XK_n                              , false}  /* U+006E LATIN SMALL LETTER N */
        , { XK_o                              , false}  /* U+006F LATIN SMALL LETTER O */
        , { XK_p                              , false}  /* U+0070 LATIN SMALL LETTER P */
        , { XK_q                              , false}  /* U+0071 LATIN SMALL LETTER Q */
        , { XK_r                              , false}  /* U+0072 LATIN SMALL LETTER R */
        , { XK_s                              , false}  /* U+0073 LATIN SMALL LETTER S */
        , { XK_t                              , false}  /* U+0074 LATIN SMALL LETTER T */
        , { XK_u                              , false}  /* U+0075 LATIN SMALL LETTER U */
        , { XK_v                              , false}  /* U+0076 LATIN SMALL LETTER V */
        , { XK_w                              , false}  /* U+0077 LATIN SMALL LETTER W */
        , { XK_x                              , false}  /* U+0078 LATIN SMALL LETTER X */
        , { XK_y                              , false}  /* U+0079 LATIN SMALL LETTER Y */
        , { XK_z                              , false}  /* U+007A LATIN SMALL LETTER Z */
        , { XK_braceleft                      , false}  /* U+007B LEFT CURLY BRACKET */
        , { XK_bar                            , false}  /* U+007C VERTICAL LINE */
        , { XK_braceright                     , false}  /* U+007D RIGHT CURLY BRACKET */
        , { XK_asciitilde                     , false}  /* U+007E TILDE */
    };
};
