#include "Monte Carlo.h"

MT* MT::_instance = nullptr;
std::mutex MT::_mutex;