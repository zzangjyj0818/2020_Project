#pragma once

#include "Window.h"
#include "Movie.h"
#include "User.h"
#include "Programmer_func.h"
#include "Function.h"
#include "User_func.h"

void log_in();
void check_Pw(User* user);
User* search_Id(char Id[]);