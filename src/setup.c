#include "include/setup.h"

void Setup()
{
    int temp = 1;

    printf("Choose if you want to use special mode [0 - false; 1 - true]: ");
    scanf("%d", &temp);
    set.special_mode = temp;
    temp = 1;

    printf("Choose if you want to use debug mode [0 - false; 1 - true]: ");
    scanf("%d", &temp);
    set.debug_mode = temp;
    temp = 1;

    printf("Choose if you want enable/disable swap card [0 - false; 1 - true]: ");
    scanf("%d", &temp);
    set.swap_card = temp;
    temp = 1;

    printf("Your current settings are:\n");
    printf("\tSpecial mode: %d\n", set.special_mode);
    printf("\tDebug mode: %d\n", set.debug_mode);
    printf("\tSwap card: %d\n", set.swap_card);
}