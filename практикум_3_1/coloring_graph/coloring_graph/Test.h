#pragma once
#include <ctime>
#include "ColoringGraph.h"

class Test
{
public:
	Test();
	Test(int Vertex, int num_color, float q, int num_tests, bool check_answer, bool print_in_file_answer, bool print_in_file_matrix);
	~Test();

	ColoringGraph* create_test();
	//void create_test();

	void matrix_generation(int Vertex, int l);
	void matrix_gen_plan_graph();
	void save_matrix(int V, int L);
	void delete_test_data();

	bool check_answer(vector<int> &answer, vector<bool> &matrix, int dimension);

private:
 char path_out[256] = "out.txt";
 int dot(int i, int j);

 bool check = false;
 bool v_check_answer; 
 bool print_in_file_answer; 
 bool print_in_file_matrix;

 int V;
 int L;
 int quantity;
 int i = 0;
 int t = 21;

 float q;
 
 fstream fs_out;

 vector<bool> matrix;
 vector<vector<int>> list_edge;

 ColoringGraph* work_test;

};
