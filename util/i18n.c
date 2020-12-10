#include <stdlib.h>
#include <locale.h>
#include "i18n.h"

void i18n_init(void)
{
	setlocale (LC_ALL, "");
	bindtextdomain("default", getenv("PWD"));
	textdomain("default");
}

