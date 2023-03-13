#include "taskloader.h"

Task TaskLoader::load(std::string filename) {
	std::ifstream file(filename);
	std::string line;
	int N = 0, M = 0;
	std::vector<std::vector<std::string>> parsed_C;
	std::vector<double> A;
	std::vector<double> B;
	int stage = 0;
	bool nextIter = false;
	while (std::getline(file, line)) {
		std::vector<std::string> result;
		std::istringstream iss(line);

		for (std::string s; iss >> s;) {
			result.push_back(s);
		}
		if (stage == 0) {
			N = std::stoi(result[0]);
			M = std::stoi(result[1]);
		}
		else if (stage == 1) {
			parsed_C.push_back(result);
			if (parsed_C.size() != N) {
				continue;
			}
		}
		else if (stage == 2) {
			for (int i = 0; i < result.size(); i++) {
				A.push_back(std::stod(result[i]));
			}
		}
		else if (stage == 3) {
			for (int i = 0; i < result.size(); i++) {
				B.push_back(std::stod(result[i]));
			}
		}
		stage++;
	}

	Matrix C(N, M);
	vector_t a(N), b(M);
	double sum_A = 0;
	double sum_B = 0;

	for (int i = 0; i < A.size(); i++) {
		a[i] = A[i];
		sum_A += A[i];
	}
	for (int i = 0; i < B.size(); i++)
	{
		b[i] = B[i];
		sum_B += B[i];
	}

	for (int i = 0; i < C.rows; i++) {
		for (int j = 0; j < C.cols; j++) {
			C(i, j) = std::stod(parsed_C[i][j]);
		}
	}

	if (sum_A != sum_B) {
		//open transportation problem
		if (sum_A < sum_B) {
			//add fake store
			is_fake_store = true;
			a.push_back(sum_B - sum_A);
			std::cout << a << std::endl;
			vector_t fake(b.size());
			C.appendDown(fake);
			std::cout << C << std::endl;
		}
		else {
			is_fake_storage = true;
			b.push_back(sum_A - sum_B);
			std::cout << b << std::endl;
			vector_t fake(a.size());
			C.appendRight(fake);
			std::cout << C;
		}
	}
	//std::cout << C << std::endl;
	try {
		return Task(C, a, b);
	}
	catch (std::exception& ex) {
		throw ex;
	}
}