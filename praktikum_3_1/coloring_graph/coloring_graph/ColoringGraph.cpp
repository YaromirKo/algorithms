#include "ColoringGraph.h"

ColoringGraph::ColoringGraph() {}

ColoringGraph::ColoringGraph(int num_color, int dimension, vector<bool> &matrix, char path_out[256]) {

 this->num_color = num_color;
 this->dimension = dimension;
 this->matrix = &matrix;
 this->path_out[256] = *path_out;

 STEP_MODE = false;
}

ColoringGraph::ColoringGraph(int num_color, int dimension, vector<bool> &matrix, vector<vector<int>> &list_edge, char path_out[256]) {

 this->num_color = num_color;
 this->dimension = dimension;
 this->matrix = &matrix;
 this->list_edge = &list_edge;
 this->path_out[256] = *path_out;

 answer.reserve(dimension * 2);

 for (int j = 0; j < dimension; j++) {
	answer.push_back(j);
	answer.push_back(0);
 }

 //cout << *(&list_edge[9][4]) << endl;
 //cout << (*this->list_edge)[9][4] << endl;

 STEP_MODE = false;
}

ColoringGraph::~ColoringGraph() {}

void ColoringGraph::print_answer_in_file(char path_out[256]) {

 fs.open(path_out, fstream::app);
 if (!fs.is_open()) {
	cout << "error open file" << endl;
 } else {
	fs << '\n';
	fs << "answer: ";
	if (answer.size() > 1) {
	 int k = 0;
	 for (int i = 0; i < answer.size(); i += 2) {
		if (answer[i] == k % dimension) {
		 fs << answer[i] + 1 << '-' << answer[i + 1] << ' ';
		 k++;
		}
	 } fs << '\n';
	}
	else { fs << answer[0] << '\n'; }
	fs << '\n';
	fs << "answer: ";
	if (answer_not_opti.size() > 1) {
	 int k = 0;
	 for (int i = 0; i < answer_not_opti.size(); i += 2) {
		if (answer_not_opti[i] == k % dimension) {
		 fs << answer_not_opti[i] + 1 << '-' << answer_not_opti[i + 1] << ' ';
		 k++;
		}
	 } fs << '\n';
	}
	else { fs << answer_not_opti[0] << '\n'; }
 }
 fs.close();
}
void ColoringGraph::print_statistic_in_file(char path_out[256]) {

 fs.open(path_out, fstream::app);
 if (!fs.is_open()) {
	cout << "error open file" << endl;
 } else {
	fs << '\n';
	fs << "num_vertex=" << dimension << ' ';							 	  ///1
	fs << "total_time=" << total_time.count() << ' ';									///2
	fs << "total_steps=" << count_steps << ' ';								///3
	fs << "total_time/total_steps=" << (total_time.count() / count_steps) << ' '; ///4
	fs << "non_optimized_solver_time=" << total_time_not_opti.count() << ' ';												///5
	fs << "non_optimized_steps=" << count_steps_not_opti << ' ';											///6
	fs << "num_edge=" << count_edge << '\n';
 }
 fs.close();
}

vector<int> ColoringGraph::get_answer() { return answer; }
vector<int> ColoringGraph::get_not_opti_answer() { return answer_not_opti; }

int ColoringGraph::get_dimension() { return dimension; }
int ColoringGraph::get_count_edge() { return count_edge; }

int ColoringGraph::get_total_steps() { return count_steps; }
int ColoringGraph::get_not_opti_total_steps() { return count_steps_not_opti; }

float ColoringGraph::get_total_time() { return total_time.count(); }
float ColoringGraph::get_not_opti_total_time() { return total_time_not_opti.count(); }

void ColoringGraph::step_mode(bool STEP_MODE) { this->STEP_MODE = STEP_MODE; }
bool ColoringGraph::step_mode() { return STEP_MODE; }


void ColoringGraph::step() {

 int count = 0;
 int active_count = 0;
 check_mux_color = 0;
 /*for (int i = 0; i < (*list_edge).size(); i++)
 {
	cout << i + 1 << ": ";
	for (int j = 0; j < (*list_edge)[i].size(); j++)
	{
	 cout << (*list_edge)[i][j] + 1 << " ";
	} cout << endl;
 }*/

 for (i; i < dimension; i++) {

	start = chrono::high_resolution_clock::now();

	vector<bool> ans(dimension, 0);
	for (int j = 0; j < (*list_edge)[i].size(); j++) {
	 ans[answer[(*list_edge)[i][j] * 2 + 1]] = 1;
	 count_edge++;
	 }
	for (int j = 0; j < dimension; j++) {
	 count_steps++;
	 if (!ans[j]) {
		answer[i * 2 + 1] = j;
		break;
	 }
	} 

	end = chrono::high_resolution_clock::now();
	count_steps++;
	total_time += (end - start);
	
	if (not_enough_colors) {
	 STEP_MODE = false;
	 break;
	}
	if (STEP_MODE) {
	 i++;
	 if (i == dimension) {
		STEP_MODE = false;
	 }
	 break;
	}
 }

 if (not_enough_colors) {
	not_enough_colors = false;
	answer.clear();
	answer.push_back(-1);
 }
}

void ColoringGraph::step_not_opti() {
 i = 0;
 int count = 0;
 int active_count = 0;
 check_mux_color = 0;
 answer_not_opti.reserve(dimension * 2);

 for (i;  i < dimension; i++) {

	start_not_opti = chrono::high_resolution_clock::now();

	if (i == 0) {
	 for (int j = 0; j < dimension; j++) {
		answer_not_opti.push_back(((i * dimension) + j) % dimension);
		if ((*matrix)[(i * dimension) + j]) {
		 answer_not_opti.push_back(1);
		}
		else {
		 answer_not_opti.push_back(0);
		}
	 }
	}
	else {
	 int max_color = 0;
	 for (int j = 0; j < dimension; j++) {
		if ((*matrix)[(i * dimension) + j]) {
		 answer_not_opti[(j * 2) + 1] > max_color ? max_color = answer_not_opti[(j * 2) + 1] : max_color;
		 if (answer_not_opti[(i * 2) + 1] == answer_not_opti[(j * 2) + 1]) {
			if (i > j) {
			 answer_not_opti[(i * 2) + 1] = max_color + 1;
			 if (answer_not_opti[(i * 2) + 1] > check_mux_color) { check_mux_color = answer_not_opti[(i * 2) + 1]; }
			}
			else {
			 answer_not_opti[(j * 2) + 1]++;
			 if (answer_not_opti[(j * 2) + 1] > check_mux_color) { check_mux_color = answer_not_opti[(j * 2) + 1]; }
			}
			if (check_mux_color + 1 > num_color) {
			 not_enough_colors = true;
			 break;
			}
		 }
		} count_steps_not_opti++;
	 }
	}
	end_not_opti = chrono::high_resolution_clock::now();
	count_steps_not_opti++;
	total_time_not_opti += (end_not_opti - start_not_opti);

	if (not_enough_colors) { 
	 STEP_MODE = false; 
	 break; 
	}
	if (STEP_MODE) {
	 i++;
	 if (i == dimension) {
		STEP_MODE = false;
	 }

	 break;
	}
 }
 if (not_enough_colors) {
	not_enough_colors = false;
	answer_not_opti.clear();
	answer_not_opti.push_back(-1);
 }
}