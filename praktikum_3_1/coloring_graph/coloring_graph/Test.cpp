#include "Test.h"


Test::Test() {}

Test::Test(int Vertex, int num_color, float q, int num_tests, bool check_answer, bool print_in_file_answer, bool print_in_file_matrix) {
 
 this->V = Vertex;
 this->L = num_color;
 this->q = q;
 //this->quantity = num_tests;
 this->v_check_answer = check_answer;
 this->print_in_file_answer = print_in_file_answer;
 this->print_in_file_matrix = print_in_file_matrix;

}

Test::~Test() {}

void Test::save_matrix(int V, int L) {

 fs_out.open(path_out, fstream::app);
 if (!fs_out.is_open()) {
	cout << "error opening file" << endl;
 } else {
	fs_out << '\n';
	fs_out << L << '\n';
	for (int a = 0; a < matrix.size(); a++) {
	 if (a % V == 0 && a > 0) {
		fs_out << '\n';
	 } fs_out << matrix[a];
	}
 }
 fs_out.close();
}

int Test::dot(int i, int j) {
  //cout << i << " " << j << " ";
 return ((i * t) + j);
}

void Test::matrix_gen_plan_graph() {
 int Vertex = t*t;
 vector<vector<bool>> mat(t*t, vector<bool>(t*t, 0));
 

 for (int i = 1; i < t-1; i += 1) {
	for (int j = 1; j < t-1; j += 1) {

	 mat[dot(i, j)][dot(i, j + 1)] = 1;
	 mat[dot(i, j + 1)][dot(i, j)] = 1;

	 mat[dot(i, j)][dot(i, j - 1)] = 1;
	 mat[dot(i, j - 1)][dot(i, j)] = 1;

	 mat[dot(i, j)][dot(i + 1, j)] = 1;
	 mat[dot(i + 1, j)][dot(i, j)] = 1;

	 mat[dot(i, j)][dot(i - 1, j)] = 1;
	 mat[dot(i - 1, j)][dot(i, j)] = 1;

	 if (i % 2 == 1 && j %2 == 1) {
		mat[dot(i, j)][dot(i + 1, j + 1)] = 1;
		mat[dot(i + 1, j + 1)][dot(i, j)] = 1;

		mat[dot(i, j)][dot(i + 1, j - 1)] = 1;
		mat[dot(i + 1, j - 1)][dot(i, j)] = 1;

		mat[dot(i, j)][dot(i - 1, j + 1)] = 1;
		mat[dot(i - 1, j + 1)][dot(i, j)] = 1;

		mat[dot(i, j)][dot(i - 1, j - 1)] = 1;
		mat[dot(i - 1, j - 1)][dot(i, j)] = 1;
	 }

	}

 }

 fs_out.open(path_out, fstream::app);
 if (!fs_out.is_open()) {
	cout << "error opening file" << endl;
 }
 else {
	fs_out << '\n';
	fs_out << L << '\n';
	for (int i = 0; i < mat.size(); i++) {
	 for (int j = 0; j < mat[i].size(); j++)
	 {
		//fs_out << mat[i][j];
		matrix.push_back(mat[i][j]);
	 }//fs_out << '\n';
	} cout << matrix.size() << endl;
	for (int i = 0; i < Vertex; i++) {
	 vector<int> list;
	 for (int j = 0; j < i; j++) {
		if (matrix[(i * Vertex) + j] == 1)  list.push_back(j);
	 }
	 list_edge.push_back(list);
	}
	
	//fs_out << '\n';
	/*for (int i = 0; i < 900; i++)
	{
	 for (int j = 0; j < 900; j++)
	 {
		fs_out << matrix[i * 900 + j];
	 } fs_out << '\n';
	}*/
	fs_out.close();
 }
}

void Test::matrix_generation(int Vertex, int l) {

 srand(time(NULL));
// cout << Vertex << endl;
 for (int i = Vertex - 1; i != -1; i--) {
	//vector<int> list;
	if (matrix.size() > Vertex - 2) {
	 for (int j = 0; j < Vertex - i - 1; j++) {
		int top_el_matrix = Vertex * j + (Vertex - i - 1); // элемент верхней матрицы
		if (matrix[top_el_matrix]) {
		 matrix.push_back(1);
		 //list.push_back(top_el_matrix);
		}
		else matrix.push_back(0);
	 }
	}
	//list_edge.push_back(list);
	matrix.push_back(0);
	
	int el;  // элементы после диагонального элемента
	for (int j = i; j != 0; j--) {
	 el = rand() % 2;
	 matrix.push_back(el);
	}
 }
 for (int i = 0; i < Vertex; i++) {
	vector<int> list;
	list.reserve(Vertex);
	for (int j = 0; j < i; j++) {
	 if (matrix[(i * Vertex) + j] == 1)  list.push_back(j);
	}
	list_edge.push_back(list);
 }

 /*for (int i = 0; i < list_edge.size(); i++)
 {
	cout << i << ": ";
	for (int j = 0; j < list_edge[i].size(); j++)
	{
	 cout << list_edge[i][j] << " ";
	} cout << endl;
 }*/


}

bool Test::check_answer(vector<int> &answer, vector<bool> &matrix, int dimension) {

 fs_out.open(path_out, fstream::app);
 if (!fs_out.is_open()) {
	cout << "error opening file" << endl;
 } else {
	cout << "ya tut bil" << endl;
	for (int i = 0; i < dimension; i++) {
	 for (int j = 0; j < dimension; j++) {
		if (matrix[(i * dimension) + j] && answer[(i * 2) + 1] == answer[(j * 2) + 1]) {
		 check = true;
		 cout << "error" << '\n';
		 break;
		}
	 }
	 if (check) { break; }
	}
	fs_out.close();	
	return check;
 }
}

void Test::delete_test_data() { 
 delete work_test; 
}

ColoringGraph* Test::create_test() {


	int v, l;

	v = t*t;
	l = 3;
	//v = int(V * (pow(q, i)));
	//l = int(L * (pow(q, i)));
	//v = int(V + q*i);
	//l = int(L + q*i);

	list_edge.reserve(v);
	matrix.reserve(v * v);
	//matrix_generation(v, l);
	matrix_gen_plan_graph();
	//if(print_in_file_matrix) save_matrix(v, l);
	//save_matrix(v, l);
	work_test = new ColoringGraph(l, v, matrix, list_edge, path_out);
	work_test->step();
	work_test->step_not_opti();
	
	for (int i = 0; i < work_test->get_not_opti_answer().size(); i += 2) {
	 if (work_test->get_not_opti_answer()[i + 1] != work_test->get_answer()[i + 1]) cout << "er";
	}

	if(print_in_file_answer) work_test->print_answer_in_file(path_out);

	
	if (v_check_answer) {
	 if (work_test->get_answer().size() > 1) {
		check_answer(work_test->get_answer(), matrix, v);
	 }
	 if (work_test->get_not_opti_answer().size() > 1) {
		check_answer(work_test->get_not_opti_answer(), matrix, v);
	 }
	}

	matrix.clear();
	list_edge.clear();
	i++;
	return work_test;
}
