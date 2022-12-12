#pragma once
#include "UsefulType.h"

template <typename T>
inline T Min(const T&, const T&);

template <typename T>
inline T Max(const T&, const T&);

template <typename T>
inline void Swap(T&, T&);

inline int MakeRandByRange(const int&, const int&);

bool IsInRange(const int&, const int&, const int&);

void Shuffle(uint* arr, const uint& arr_length, const uint& n_shuffle);

void GetRandomsNoOverlap(int* arr, const uint& arr_length, const uint& num);