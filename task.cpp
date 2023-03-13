#include "task.h"
#include "functions.h"
#include <vector>
#include <algorithm>
using namespace std;
void Task::bpe() {
	//data preparation
	vector_t f(_a);
	f.append(_b);
	/*cout << _a << endl;
	cout << _b << endl;*/
	Matrix tmp = _C.T();
	vector_t z(tmp);
	//cout << z << endl;
	Matrix A = Matrix(f.size(), _C.rows * _C.cols);
	for (int i = 0, A_j = 0; i < _C.rows; i++, A_j += _C.cols) {
		for (int j = 0; j < _C.cols; j++) {
			A(i,j + A_j) = 1;
			A(_C.rows + j, j + A_j) = 1;
		}
	}
	
	A.deleteLastRow();
	f.pop_back();
	//cout << A << endl;
	vector <double> obj_fun_values;
	vector <vector<double>> boundary_points;
	vector<set<int>> solution_variables_indices;
	vector<int> column_set;
	generate_n(inserter(column_set, column_set.end()), A.cols, [n = 0]() mutable { return n++; });
	vector<set<int>> combinations = generate_combinations(column_set, A.rows);
	for (auto combination : combinations) {
		Matrix submatrix = Matrix(A, combination);
		auto sol = gauss(submatrix, f);
		if (sol >= 0 && !isnan(sol[0])) {
			boundary_points.push_back(sol);
			obj_fun_values.push_back(evaluate(z, sol, combination));
			solution_variables_indices.push_back(combination);
		}
		
	}
	auto val = *(min_element(obj_fun_values.begin(), obj_fun_values.end()));
	auto index = find_index(obj_fun_values, val);
	cout << "the min of objective function is: " << val << "\t\n" << "variables are:" << solution_variables_indices[index] << "=" << boundary_points[index] << ", other x_i = 0" << endl;
}