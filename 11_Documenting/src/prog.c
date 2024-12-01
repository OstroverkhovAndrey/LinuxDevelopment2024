/** @mainpage
 * # Guesser numbers
 *
 * This is tool guesses numbers from 1 to 100 using binary search.
 */

/** @file prog.c
 * Implementation
 *
 * This is program guesses numbers from 1 to 100 using binary search.
 */

/** @page
 * This is program guesses numbers from 1 to 100 using binary search.
 *
 * Options:
 *  -r          Use roman or arabic number
 *  --help      Help program
 *
 */

#include "config.h"
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _(STRING) gettext(STRING) /**< Translate func */
#define LOCALE_PATH "po"          /**< Translate dir */

int using_arabic = 1; /**< Use arabic number flag */

char *arabic_to_roman[] = {
    "I",       "II",     "III",     "IV",       "V",      "VI",      "VII",
    "VIII",    "IX",     "X",       "XI",       "XII",    "XIII",    "XIV",
    "XV",      "XVI",    "XVII",    "XVIII",    "XIX",    "XX",      "XXI",
    "XXII",    "XXIII",  "XXIV",    "XXV",      "XXVI",   "XXVII",   "XXVIII",
    "XXIX",    "XXX",    "XXXI",    "XXXII",    "XXXIII", "XXXIV",   "XXXV",
    "XXXVI",   "XXXVII", "XXXVIII", "XXXIX",    "XL",     "XLI",     "XLII",
    "XLIII",   "XLIV",   "XLV",     "XLVI",     "XLVII",  "XLVIII",  "XLIX",
    "L",       "LI",     "LII",     "LIII",     "LIV",    "LV",      "LVI",
    "LVII",    "LVIII",  "LIX",     "LX",       "LXI",    "LXII",    "LXIII",
    "LXIV",    "LXV",    "LXVI",    "LXVII",    "LXVIII", "LXIX",    "LXX",
    "LXXI",    "LXXII",  "LXXIII",  "LXXIV",    "LXXV",   "LXXVI",   "LXXVII",
    "LXXVIII", "LXXIX",  "LXXX",    "LXXXI",    "LXXXII", "LXXXIII", "LXXXIV",
    "LXXXV",   "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",      "XCI",
    "XCII",    "XCIII",  "XCIV",    "XCV",      "XCVI",   "XCVII",   "XCVIII",
    "XCIX",    "C"}; /**< Arabic to roman convert map */

/** Translate arabic int number to string roman number.
 *
 * @param number arabic number
 * @return roman string number
 */
char *to_roman(int number) {
  if (1 <= number && number <= 100) {
    return arabic_to_roman[number - 1];
  }
  return "";
}

/** Translate string roman number to arabic int number.
 *
 * @param number roman string number
 * @return arabic number
 */
int to_arabic(char *number) {
  for (int i = 1; i <= 100; ++i) {
    if (arabic_to_roman[i] == number) {
      return i;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {

  if (argc == 2 && strcmp(argv[1], "--help") == 0) {
    printf(
        _("This is tool guesses numbers from 1 to 100 using binary search.\n"));
    return 0;
  }

  if (argc == 2 && strcmp(argv[1], "-r") == 0) {
    using_arabic = 0;
  }

  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALE_PATH);
  textdomain(PACKAGE);

  if (using_arabic) {
    printf(_("Guess the number from %i to %i\n"), 1, 100);
  } else {
    printf(_("Guess the number from %s to %s\n"), to_roman(1), to_roman(100));
  }

  int l = 1, r = 100;

  while (l < r) {
    int m = (l + r) / 2;
    if (using_arabic) {
      printf(_("Your number is more than %i, y\\n\n"), m);
    } else {
      printf(_("Your number is more than %s, y\\n\n"), to_roman(m));
    }
    char ans;
    scanf("%c", &ans);
    if (ans == _("y")[0]) {
      l = m + 1;
    } else if (ans == _("n")[0]) {
      r = m;
    } else {
      printf(_("Incorrect response\n"));
      return 0;
    }
    scanf("%c", &ans);
  }
  if (using_arabic) {
    printf(_("Your number is %i\n"), l);
  } else {
    printf(_("Your number is %s\n"), to_roman(l));
  }
  return 0;
}
