#pragma once
#include "Test.h"

class ConsoleInterface
{
public:
 ConsoleInterface();
 ~ConsoleInterface();

 void start();
 void preparing_work(char path_in[256]);
 void print_statistic(ColoringGraph *obj);
 void print_answer(ColoringGraph *obj);
 void print_answer_not_opti(ColoringGraph *obj);
 void run_step_mode(ColoringGraph *obj);
 

private:
 char path_in[256] = "in.txt";
 char path_out[256] = "out.txt";
 char user_key;

 bool flag_check_valid = false;

 int Vertex;
 int q;
 int quantity;
 int L;
 int dimension;

 vector<bool> matrix;
 vector<vector<int>> list_edge;

 ColoringGraph *work;

 fstream fs;

 void title();


};

