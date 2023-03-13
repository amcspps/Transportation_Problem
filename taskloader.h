#pragma once
#include "task.h"
#include <string>
#include <vector>
#include "matrix_t.h"
#include "vector_t.h"
#include <fstream>
#include <sstream>
#include <algorithm>
class TaskLoader {
private:
	bool is_fake_store = false;
	bool is_fake_storage = false;
public:
	Task load(std::string filename);


};