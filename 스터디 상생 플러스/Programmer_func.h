#pragma once

#include "Window.h"
#include "Movie.h"
#include "User.h"
#include "Function.h"
#include "User_func.h"

void movie_information(Movie* movie);
int movie_title_compare(char* title);
void insert_movie();
Movie* search_pre_node(Movie* p);
void delete_movie(Movie* p);
void user_management();
User* search_pre_user(User* p);
void print_user_list();
void delete_user();
