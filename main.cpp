#include "matrix_t.h"
#include "vector_t.h"
#include "taskloader.h"
#include "task.h"
using namespace std;

int main() {
	TaskLoader tl;
	Task task = tl.load("C:\\Users\\kachok na masse\\source\\repos\\transportation problem\\test.txt");
	task.bpe();
	vector<double> vec = { 1, 2, 3,4,5,6 };
	Matrix mat_r = Matrix(vec, 2, 3);

	
}