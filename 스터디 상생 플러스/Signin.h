#pragma once

#include "Window.h"
#include "Movie.h"
#include "User.h"
#include "Programmer_func.h"
#include "Function.h"
#include "User_func.h"

void sign_in();
void input_user_info(User* user); //사용자 정보 입력
int compare_duplication(char* Id);
void Pw_cmp(char Pw[]);
int check_IdPw_length(char* user);
int check_eng_digit(char* user);
void bot_check();