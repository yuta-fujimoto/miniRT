#ifndef KEYSYMDEF_H
# define KEYSYMDEF_H

/*
 * TTY function keys, cleverly chosen to map to ASCII, for convenience of
 * programming, but could have been arbitrary (at the cost of lookup
 * tables in client code).
 */

# define XK_TAB			0xff09
# define XK_ESCAPE		0xff1b

# define XK_LEFT		0xff51  /* Move left, left arrow */
# define XK_UP			0xff52  /* Move up, up arrow */
# define XK_RIGHT		0xff53  /* Move right, right arrow */
# define XK_DOWN		0xff54  /* Move down, down arrow */

# define XK_A			0x0061  /* U+0061 LATIN SMALL LETTER A */
# define XK_B			0x0062  /* U+0062 LATIN SMALL LETTER B */
# define XK_C			0x0063  /* U+0063 LATIN SMALL LETTER C */
# define XK_D			0x0064  /* U+0064 LATIN SMALL LETTER D */
# define XK_E			0x0065  /* U+0065 LATIN SMALL LETTER E */
# define XK_F			0x0066  /* U+0066 LATIN SMALL LETTER F */
# define XK_G			0x0067  /* U+0067 LATIN SMALL LETTER G */
# define XK_H			0x0068  /* U+0068 LATIN SMALL LETTER H */
# define XK_I			0x0069  /* U+0069 LATIN SMALL LETTER I */
# define XK_J			0x006a  /* U+006A LATIN SMALL LETTER J */
# define XK_K			0x006b  /* U+006B LATIN SMALL LETTER K */
# define XK_L			0x006c  /* U+006C LATIN SMALL LETTER L */
# define XK_M			0x006d  /* U+006D LATIN SMALL LETTER M */
# define XK_N			0x006e  /* U+006E LATIN SMALL LETTER N */
# define XK_O			0x006f  /* U+006F LATIN SMALL LETTER O */
# define XK_P			0x0070  /* U+0070 LATIN SMALL LETTER P */
# define XK_Q			0x0071  /* U+0071 LATIN SMALL LETTER Q */
# define XK_R			0x0072  /* U+0072 LATIN SMALL LETTER R */
# define XK_S			0x0073  /* U+0073 LATIN SMALL LETTER S */
# define XK_T			0x0074  /* U+0074 LATIN SMALL LETTER T */
# define XK_U			0x0075  /* U+0075 LATIN SMALL LETTER U */
# define XK_V			0x0076  /* U+0076 LATIN SMALL LETTER V */
# define XK_W			0x0077  /* U+0077 LATIN SMALL LETTER W */
# define XK_X			0x0078  /* U+0078 LATIN SMALL LETTER X */
# define XK_Y			0x0079  /* U+0079 LATIN SMALL LETTER Y */
# define XK_Z			0x007a  /* U+007A LATIN SMALL LETTER Z */

# define XK_ZOOM_IN		0x0004
# define XK_ZOOM_OUT	0x0005
# define XK_LEFT_CLICK	0x0001
# define XK_RIGHT_CLICK	0x0003
# define XK_PLUS		0x003b  /* U+002B PLUS SIGN */
# define XK_MINUS		0x002d  /* U+002D HYPHEN-MINUS */

#endif
