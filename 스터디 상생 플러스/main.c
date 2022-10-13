#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>


#include "Window.h"
#include "Movie.h"
#include "User.h"
#include "Programmer_func.h"
#include "Function.h"
#include "User_func.h"

extern User* user_head = NULL, * user_tail = NULL;
extern Movie* movie_head = NULL, * movie_tail = NULL;

int main()
{
	while (1)
	{
		INIT_window();
	}
	return 0;
}