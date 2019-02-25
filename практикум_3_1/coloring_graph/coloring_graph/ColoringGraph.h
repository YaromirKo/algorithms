#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

class ColoringGraph
{
public:

	ColoringGraph();
	ColoringGraph(int num_color, int dimension, vector<bool> &matrix, char path_out[256]);
	ColoringGraph(int num_color, int dimension, vector<bool> &matrix, vector<vector<int>> &list_edge, char path_out[256]);


	~ColoringGraph();

	void step();
	void step_not_opti();
	void print_answer_in_file(char path_out[256]);
	void print_statistic_in_file(char path_out[256]);
	void step_mode(bool STEP_MODE);

	bool step_mode();

	int get_total_steps();
	int get_not_opti_total_steps();
	int get_dimension();
	int get_count_edge();
	
	float get_total_time();
	float get_not_opti_total_time();

	vector<int> get_answer();
	vector<int> get_not_opti_answer();


private:
 vector<int> answer;
 vector<int> answer_not_opti;
 vector<bool> *matrix;
 vector<vector<int>> *list_edge;

 fstream fs;

 char path_out[256];

 bool STEP_MODE;
 bool not_enough_colors;

 int dimension;
 int i = 0;
 int num_color;
 int check_mux_color = 0;

 ///statistic
 int count_steps = 0;
 int count_steps_not_opti = 0;
 int count_edge = 0;

 chrono::time_point<chrono::steady_clock> start, end, start_not_opti, end_not_opti;
 chrono::duration<float> total_time, total_time_not_opti;

};
