
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int main (int argc, char *argv[]) {

    setlocale (LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALE_PATH);
    textdomain (PACKAGE);

    printf(_("Guess the number from 1 to 100\n"));

    int l = 1, r = 100;

    while (l < r) {
        int m = (l+r) / 2;
        printf(_("Your number is more than %i, y\\n\n"), m);
        char ans;
        scanf("%c", &ans);
        if (ans == _("y")[0]) {
            l = m+1;
        } else if (ans == _("n")[0]) {
            r = m;
        } else {
            printf(_("Incorrect response\n"));
            return 0;
        }
        scanf("%c", &ans);
    }
    printf(_("Your number is %i\n"), l);
    return 0;
}
