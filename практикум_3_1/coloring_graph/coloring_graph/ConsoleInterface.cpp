#include "ConsoleInterface.h"

ConsoleInterface::ConsoleInterface() {start();}
ConsoleInterface::~ConsoleInterface() {}

void ConsoleInterface::title() {

 for (int i = 0; i < 117; i++) { cout << "*"; }
 cout << '\n';
 // cout << "num_vertex " << " total_time " << " total_steps " << " total_time/total_steps " << " physics_time_for_theoretical_evaluation " << " non_optimized_solver_time " << "num_edge " << endl;
 cout << "num_vertex " << " total_time " << " total_steps " << " total_time/total_steps " << " non_optimized_solver_time " << " non_optimized_steps " << " num_edge " << endl;
}
void ConsoleInterface::print_statistic(ColoringGraph *obj) {
 
 cout << '\n';
 printf("%10d %11.8f %12d %23.18f", obj->get_dimension(), obj->get_total_time(), obj->get_total_steps(), obj->get_total_time() / obj->get_total_steps());
 printf("%25.8f %22d %9d\n", obj->get_not_opti_total_time(), obj->get_not_opti_total_steps(), obj->get_count_edge());
 obj->print_statistic_in_file(path_out);
}

void ConsoleInterface::print_answer(ColoringGraph* obj) {

 cout << "* answer: ";
 if (obj->get_answer().size() > 1) {
	int k = 0;
	for (int i = 0; i < obj->get_answer().size(); i += 2) {
	 if (obj->get_answer()[i] == k % dimension) {
		cout << obj->get_answer()[i] + 1 << '-' << char(obj->get_answer()[i + 1] + 65) << ' ';
		k++;
	 }
	} cout << endl;
 }
 else { 
	cout << obj->get_answer()[0];
	cout << endl;
 }
}
void ConsoleInterface::print_answer_not_opti(ColoringGraph *obj) {

 cout << "* answer: ";
 if (obj->get_not_opti_answer().size() > 1) {
	int k = 0;
	for (int i = 0; i < obj->get_not_opti_answer().size(); i += 2) {
	 if (obj->get_not_opti_answer()[i] == k % dimension) {
		cout << obj->get_not_opti_answer()[i] + 1 << '-' << char(obj->get_not_opti_answer()[i + 1] + 65) << ' ';
		k++;
	 }
	} cout << endl;
 }
 else {
	cout << obj->get_not_opti_answer()[0];
	cout << endl;
 }
}

void ConsoleInterface::run_step_mode(ColoringGraph *obj) {

 obj->step_mode(true);
 for (int i = 0; i < 117; i++) { cout << "*"; } cout << endl;
 while (obj->step_mode()) {

	 cout << "next step? (y/n): ";
	 cin >> user_key;

	if (user_key == 'y') {
	 obj->step();
	 print_answer(obj);
	}
	else if (user_key == 'n') {
	 obj->step_mode(false);
	 obj->step();
	 print_answer(obj);
	}
 }
 obj->print_answer_in_file(path_out);
 title();
 print_statistic(obj);
}

void ConsoleInterface::preparing_work(char path_in[256]) {

 fs.open(path_in); 
 if (!fs) {
	flag_check_valid = true;
 }
 if (!fs.is_open()) { // проверка на откртие файла
	cout << "error opening file" << endl;
	flag_check_valid = true;
 }
 else {
	char ch;
	fs >> L;
	while (fs.get(ch)) {
	 if (ch == '\n') continue;
	 matrix.push_back((int)ch - 48); // заполняем наш вектор значениями матрицы
	}

	dimension = (int)sqrt(matrix.size()); // кол - во элементов в строке каждой матрицы

	for (int i = 0; i < dimension; i++) {
	 vector<int> list;
	 for (int j = 0; j < i; j++) {
		if (matrix[(i * dimension) + j] == 1)  list.push_back(j);
	 }
	 list_edge.push_back(list);
	}

	/*for (int i = 0; i < dimension; i++)
	{
	 cout << i <<": ";
	 for (int j = 0; j < list_edge[i].size(); j++)
	 {
		cout << list_edge[i][j] << " ";
	 } cout << endl;
	}*/

	for (int j = 0; j < dimension; j++) { // проверка на симметричность матрицы
	 if (matrix[j * (1 + dimension)]) {
		cout << "matrix error" << endl;
		flag_check_valid = true;
	 }
	 if (j < dimension - 1) {
		for (int k = 0; k < dimension - 1 - j; k++) {
		 int top_el_matrix = dimension * j + j + k + 1; // элемент верхней матрицы
		 int bottom_el_matrix = dimension * (1 + j + k) + j; // элемент нижней матрицы
		 if (matrix[top_el_matrix] != matrix[bottom_el_matrix]) {
			cout << "matrix error" << endl;
			flag_check_valid = true;
		 }
		}
	 }
	}
 }
 fs.close();
}


void ConsoleInterface::start() {

	cout << "Start testing (press on 'y') or read data from file (press on 'n') : ";
	cin >> user_key;

	if (user_key == 'y') {
	 char u_k_check_answer, u_k_print_in_file_ansver, u_k_print_in_file_matrix;

	 cout << "we start testing" << endl;
	 cout << "use default data (y/n): ";
	 cin >> user_key;
	 
	 if (user_key == 'y') {
		cout << "begin all test..." << endl;
		title();
		Test* test = new Test(100, 3, 1000, 5, true, true, false);
		for (int i = 0; i <1; i++)
		{
		 print_statistic(test->create_test());
		 test->delete_test_data();
		}

		for (int i = 0; i < 117; i++) { cout << "*"; }
		cout << '\n' << "tests finished" << endl;
	 }
	 else if (user_key == 'n') {

		cout << "Enter the following(4) parameters" << endl;
		cout << "initial number of vertices : ";
		cin >> Vertex;
		cout << "Number color : ";
		cin >> L;
		cout << "speed increase complexity : ";
		cin >> q;
		cout << "quantity tests : ";
		cin >> quantity;
		cout << "check the answer? (y/n): ";
		cin >> u_k_check_answer;
		cout << "print_in_file_ansver? (y/n): ";
		cin >> u_k_print_in_file_ansver;
		cout << "print_in_file_matrix? (y/n): ";
		cin >> u_k_print_in_file_matrix;

		cout << "begin all test..." << endl;
		title();
		Test* test = new Test(Vertex, L, q, quantity, (u_k_check_answer == 'y' ? true : false), (u_k_print_in_file_ansver == 'y' ? true : false), (u_k_print_in_file_matrix == 'y' ? true : false));
		
		for (int i = 0; i < quantity; i++)
		{
		 print_statistic(test->create_test());
		 test->delete_test_data();
		}
		

		for (int i = 0; i < 117; i++) { cout << "*"; }
		cout << '\n' << "tests finished" << endl;
	 }
	}
	else if (user_key == 'n') {

	 preparing_work(path_in);
	 if(!flag_check_valid) {
		//work = new ColoringGraph(L, dimension, matrix, path_out);
		// vector<bool> ().swap(matrix);

		cout << "all_mode or step_mode (y/n): ";
		cin >> user_key;

		if (user_key == 'y') {

		 cout << "begin all mode..." << endl;
		 work = new ColoringGraph(L, dimension, matrix, list_edge, path_out);

		 work->step();
		 work->step_not_opti();
		 for (int i = 0; i < 117; i++) { cout << "*"; } cout << '\n';
		 print_answer(work);
		 print_answer_not_opti(work);
		 Test test;
		 test.check_answer(work->get_answer(), matrix, dimension);
		 title();

		 work->print_answer_in_file(path_out);
		

		 print_statistic(work);
		 for (int i = 0; i < 117; i++) { cout << "*"; }
		 cout << '\n' << "end" << endl;
		}
		else if (user_key == 'n') {

		 cout << "begin step mode..." << endl;
		 user_key = ' ';
		 run_step_mode(work);
		 for (int i = 0; i < 117; i++) { cout << "*"; }
		 cout << '\n' << "end" << endl;
		}
	 }
	 else cout << "something is wrong\nmake sure the 'in.txt' file is created\n";
	}
}
