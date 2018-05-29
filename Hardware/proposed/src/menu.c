
#include "../include/menu.h"
#include "../include/uart.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern ring_buffer buffor_tx;

static void display_menu(void);

/**
 * \brief Initialize and display the current menu
 * \param[in] menu - array of menu items
 * \param[in] count - number of menu items (max 9)
 */
void menu_init()
{
    display_menu();
}


/**
 * \brief Read an unsigned integer from the menu prompt
 * \param[in] prompt - the text to display
 * \return the unsigned integer read 
 */


static void display_menu(void)
{

    put_string(&buffor_tx,"Menu: \n\r");
    put_string(&buffor_tx,"[s]. Start/Stop \n\r");
    put_string(&buffor_tx,"[z]. Zapisz miedzyczas \n\r");
    put_string(&buffor_tx,"[r]. Reset \n\r");

    /* Print prompt */
    put_string(&buffor_tx,"\n\r");
}
