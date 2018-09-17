#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Transitions{
	int currentState;
	char currentSymbol;
	int nextState;
	char nextSymbol;
	char direction;
};

bool reachedEnd(int currState, vector<int> endStates){
	for(int x = 0; x < endStates.size(); x++){
		if(currState == endStates.at(x))
			return true;
	}
	return false;
}

int main(int argc, char* argv[]){

	if(argc != 4){
		cout << "Please enter in the following format ./mmangal_p1 <machine_definition_filename> <sample_input_string> <maximum_transition_numbers>" << endl;
		exit(1);		
	}

	string filename = argv[1];
	string input_string = argv[2];
	int max_transitions = atoi(argv[3]);

	vector<int> accept_states;
	vector<int> reject_states;
	vector<Transitions*> transitions;

	int start_state;

	ifstream fp;
	fp.open(filename);

	if(fp.is_open()){
		string line;
		while(getline(fp, line)){
			istringstream iss(line);
			//getline(iss, line, '\t');
		
			string state;
			int state_num;
			string state_def;

			if(line.find("state") != std::string::npos){
				if(!(iss >> state >> state_num >> state_def)){
					cout << "Invalid number of args in state line" << endl;
					exit(1);
				}
				if(state_def == "accept"){
					accept_states.push_back(state_num);
				}else if(state_def == "reject"){
					reject_states.push_back(state_num);
				}else{
					start_state = state_num;
				}
			}else if(line.find("transition") != std::string::npos){
				Transitions* transition = new Transitions();
				string transition_str;
				if(!(iss >> transition_str >> transition->currentState >> transition->currentSymbol 
					>> transition->nextState >> transition->nextSymbol >> transition->direction)){
					cout << "Invalid number of args in transitions line" << endl;
					exit(1);
				}
				transitions.push_back(transition);
			}else{
				cout << "Invalid line" << endl;
				exit(1);
			}
		}
		
	}else{
		cout << "Cannot open given file" << endl;
		exit(1);
	}
	
	int curr_state = start_state;
	int num_transitions = 0;
	int curr_ind = 10000;

	vector<char> input_symbols(20000+input_string.length());

	for(int x = 10000; x < 10000+input_string.length(); x++){
		input_symbols.at(x) = input_string.at(x-10000);
	}
	for(int x = 0; x < 10000; x++){
		input_symbols.at(x) = '_';
	}
	for(int x = 10000+input_string.length(); x < 20000+input_string.length(); x++){
		input_symbols.at(x) = '_';
	}
	

	cout << curr_state;
	while(num_transitions < max_transitions && !(reachedEnd(curr_state, accept_states)) && !(reachedEnd(curr_state, reject_states))){
		for(int x = 0; x < transitions.size(); x++){
			//cout << "transitions : " << transitions.at(x)->currentState << " curr_symbol : " << input_symbols.at(curr_ind) <<  endl;
			if((transitions.at(x))->currentState == curr_state && (transitions.at(x))->currentSymbol == input_symbols.at(curr_ind)){
				curr_state = transitions.at(x)->nextState;
				input_symbols.at(curr_ind) = transitions.at(x)->nextSymbol;
				if((transitions.at(x))->direction == 'R'){
					curr_ind++;
				}else{
					curr_ind--;
				}
				cout << "->" << curr_state;
				break;
			}
		}
		num_transitions++;
	}

	if(reachedEnd(curr_state, accept_states)){
		cout << " accept" << endl;
	}else if(reachedEnd(curr_state, reject_states)){
		cout << " reject" << endl;
	}else{
//		cout << num_transitions << endl;
		cout << " quit" << endl;
	}

	return 0;
	



}
