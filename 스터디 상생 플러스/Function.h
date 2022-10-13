#pragma once

#include "Window.h"
#include "Movie.h"
#include "User.h"
#include "Programmer_func.h"
#include "User_func.h"
#include "Signin.h"

char* input_title();
char* delete_space(char* title);
Movie* search_title(char* title);
void search_movie();
void print_movie();
void user_info_modification(User* p);
void searching_IDPW_window();
void searching_ID(); 
void searching_PW();