#pragma once

#include "Window.h"
#include "Movie.h"
#include "User.h"
#include "Programmer_func.h"
#include "Function.h"

void user_withdrawal(User* user);
void reserve_movie(User* user);
Movie* reserve_number();
void seat_reservation(Movie* movie, User* user);
void print_reservated_list(User* user);
void cancel_reservation(User* user);
