#pragma once

#include "Movie.h"
#include "User.h"
#include "Programmer_func.h"
#include "Function.h"
#include "User_func.h"

void INIT_window(); //초기화면 (로그인 , 회원가입)
void Run();
void Programmer_window();
void User_window();
void Programmer_Run(int menu, User* user);
void User_Run(int menu, User* user);