#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


struct node {
  node (int, node*);
  int num;
  node* next;
};

node::node (int num_in, node* next_in){
  num = num_in;
  next = next_in;
}


class linked_list { //this will be used for each element of the vector
  public:
  void add_node(int);
  node* head = new node(-1, nullptr);
  node* tail = head;

  private:
};

void linked_list::add_node(int num_in) { //adds a node to the linked list
  node* new_node = new node(num_in, nullptr);
  node* previous;
  node* current = head;
  bool added = false;

  if (head->next == nullptr) { //if this is the first node added
    head->next = new_node;
    tail = new_node;
  }

  else {
    current = head;
    previous = head;
    
    while (current != nullptr) {
      if (new_node->num < current->num) { //if the node num is lower than others it is inserted before
        previous->next = new_node;
        new_node->next = current;
        added = true;
        break;
      }
      
      previous = current;
      current = current->next;
    }
    
    if (!added) { //if there are no nodes with a larger num it is added to the end
      tail->next = new_node;
      tail = new_node;
    }
  }
}


void resize(vector <linked_list*>& ll_vector, int new_size) { //resizes the vector
  int initial_size = ll_vector.size();

  for (int i = 0; i < new_size - initial_size + 1; i++) {
    ll_vector.push_back(new linked_list);
  }
}

bool edge_found (vector <linked_list*>& ll_vector, int first, int second) { //checks if the edge first to second is already in the vector
  bool found = false;
  node* current;

  if (first >= ll_vector.size()) { //calls resize if first would cause out of range error
    resize(ll_vector, first);
  }
  
  current = ll_vector.at(first)->head; //checks if the edge already exists
  while (current != nullptr) {
    if (current->num == second) {
      found = true;
    }
    current = current->next;
  }

  return found;
}

void construct_adjacency_list (string file_in, string file_out) { //constructs the adjacency file and prints the results
  vector <linked_list*> ll_vector;
  string num1_s, num2_s;
  int num1, num2, num_nodes = 0, num_edges = 0, total_degree = 0, current_degree, max_degree = 0;
  node* current;

  ifstream graph_edges{file_in};
  ofstream file{file_out};

  while (graph_edges.eof() != true) { //Loops through each edge in the file
    graph_edges >> num1_s;
    graph_edges >> num2_s;

    num1 = stoi(num1_s);
    num2 = stoi(num2_s);
    
    if (!edge_found(ll_vector, num1, num2)) {
      ll_vector.at(num1)->add_node(num2); //adds num2 to the linked list of num1
    }
    if (!edge_found(ll_vector, num2, num1)) {
      ll_vector.at(num2)->add_node(num1); //adds num1 to the linked list of num2
    }
  }
  
  graph_edges.close();
  
  for (int i = 0; i < ll_vector.size(); i++) { //outputs the adjacency list to the file, ignoreing repeats and non_existant nodes
    
    current = ll_vector.at(i)->head;
    
    if (current->next != nullptr) { //loops through the linked list
      num_nodes++;
      current_degree = 0;
      
      file << i << ":";
      
      while (current != nullptr) { //adds the non-empty linked lists to the file
        if (current->num != -1) {
          file << " " << current->num;
          current_degree++;
        }
      
        current = current->next;
      }

      total_degree += current_degree;

      if (current_degree > max_degree) {
        max_degree = current_degree;
      }

      file << "\n";
    }
  }

  file.close();

  num_edges = total_degree / 2;

  cout << "Number of nodes: " << num_nodes << endl;
  cout << "Number of edges: " << num_edges << endl;
  cout << "Maximum degree: " << max_degree << endl;
}

void run(const string& src_path, const string& dst_path) {
  construct_adjacency_list(src_path, dst_path);
}


int main() {
  //construct_adjacency_list("tests.txt", "file_out");
  run("karate.txt", "file_out");
  return 0;
}