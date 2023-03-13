#include "functions.h"
#include <algorithm>
#include <tuple>

using namespace std;



vector <double> gaussian_reverse(Matrix A, vector_t B) {
	vector<double> X(B.size());
	//fill(X.begin(), X.end(), 0);
	for (int i = A.cols - 1; i >= 0; i--) {
		double beta = B[i];
		for (int j = A.cols - 1; j > i; j--) {
			beta -= A(i, j) * X[j];
		}
		X[i] = beta / A(i, i);
		if (fabs(X[i]) < 1e-6) {
			X[i] = 0;
		}
	}
	return X;
};

vector <double> solve(Matrix A, vector_t B) {
	double C, S;
	for (int i = 0; i < A.cols - 1; i++) {
		for (int m = i + 1; m < A.cols; m++) {
			C = A(i, i) / sqrt(A(i, i) * A(i, i) + A(m, i) * A(m, i));

			S = A(m, i) / sqrt(A(i, i) * A(i, i) + A(m, i) * A(m, i));
			if (isnan(C) || (isnan(S))) {
				return vector<double> { BAD_DETERMINANT };
			}
			for (int k = i; k < A.cols; k++) {
				double A1 = C * A(i, k) + S * A(m, k);
				double A2 = C * A(m, k) - S * A(i, k);
				/*if (fabs(A1) < 1e-6) {
					A1 = 0;
				}
				if (fabs(A2) < 1e-6) {
					A2 = 0;
				}*/
				A(i, k) = A1;
				A(m, k) = A2;
			}
			double B1 = C * B[i] + S * B[m];
			double B2 = C * B[m] - S * B[i];
			B[i] = B1;
			B[m] = B2;
		}
	}

	if (determinant_upper_triangle(A) != 0) {
		return gaussian_reverse(A, B);
	}
	else {
		return { BAD_DETERMINANT };
	}

};

double determinant_upper_triangle(Matrix A) {
	double det = 1;
	if (A.rows != A.cols) {
		throw std::invalid_argument("matrix is not square");
	}
	for (int i = 0; i < A.cols; i++) {
		if (fabs(A(i, i)) < 1e-6) { return det = 0; };
		det *= A(i, i);
	}
	if (fabs(det) < 1e-6) {
		return det;
	}

}


double evaluate(vector_t obj_function, vector<double> solution, set<int> variable_indices) {
	double result_value = 0;
	reverse(solution.begin(), solution.end());
	for (auto index : variable_indices) {
		result_value += obj_function[index] * (solution.back());
		solution.pop_back();
	}
	return result_value;
}

vector<set<int>> generate_combinations(vector<int> column_set, int k) {
	vector<int> combination;
	vector <set<int>> combinations;

	go(column_set, combination, combinations, 0, k);
	return combinations;
}

void go(vector <int>& column_set, vector <int>& combination, vector <set<int>>& combmas, int offset, int k) {
	if (k == 0) {
		set<int> cur_comb(combination.begin(), combination.end());
		combmas.push_back(cur_comb);
		return;
	}
	for (int i = offset; i <= column_set.size() - k; ++i) {
		combination.push_back(column_set[i]);
		go(column_set, combination, combmas, i + 1, k - 1);
		combination.pop_back();
	}
}



vector <double> gauss(Matrix A, vector_t B) {
	A.appendRight(B);
	int N = A.rows;
	// Triangularization
	for (int k = 0; k < N; k++) {
		int i_max = k;
		int v_max = fabs(A(i_max,k));

		for (int i = k + 1; i < N; i++)
			if (fabs(A(i,k)) > v_max)
				v_max = A(i,k), i_max = i;
		if (i_max != k)
			for (int t = 0; t <= N; t++) {
				double tmp = A(k,t);
				A(k,t) = A(i_max,t);
				A(i_max,t) = tmp;
			}
		for (int i = k + 1; i < N; i++) {
			double f = A(i,k) / A(k,k);
			for (int j = k + 1; j <= N; j++)
				A(i,j) -= A(k,j) * f;
			A(i,k) = 0;
		}
	}
	// Resolution
	vector <double> x(N,0);

	for (int i = N - 1; i >= 0; i--) {
		x[i] = A(i,N);
		for (int j = i + 1; j < N; j++)
			x[i] -= A(i,j) * x[j];
		x[i] = x[i] / A(i,i);
	}
	return x;

}