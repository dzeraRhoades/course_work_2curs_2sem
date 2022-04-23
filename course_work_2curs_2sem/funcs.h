#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include<random>
#include<iostream>

double calculateTheDistance(double phA, double lA, double phB, double lB);
std::string getTime(time_t _time); // time in seconds