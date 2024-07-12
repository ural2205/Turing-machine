#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

vector<string> split(string s, string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

map<string, map<string, string>> parse_csv(string filename) {
  map<string, map<string, string>> mps;
  ifstream in;
  in.open(filename);

  string s;
  getline(in, s);
  vector<string> tmt = split(s, ";");
  while (getline(in, s)) {
    vector<string> v = split(s, ";");
    for (int i = 0; i < v.size(); i++) {
      if (i != 0) {
        mps[tmt[i]][v[0]] = v[i];
      }
    }
  }
  in.close();
  return mps;
}

void iterations(string &mode, list<string> &lst,
                map<string, map<string, string>> &mps,
                list<string>::iterator &iter) {
  string state = "1";
  while (true) {
    if (mode == "--step") {
      for (list<string>::iterator y = lst.begin(); y != lst.end(); y++) {
        if (y == iter) {
          cout << "|" << *y << "|";
        }
        cout << *y;
      }
      cout << endl;
    }
    string make = mps[*iter][state];
    vector<string> els = split(make, ",");
    string first = els[0];
    string second = els[1];
    string third = els[2];
    if (first != "") {
      if (iter == lst.begin()) {
        *iter = first;
        lst.push_front("λ");
      } else if (distance(iter, lst.end()) == 1) {
        *iter = first;
        lst.push_back("λ");
      } else
        *iter = first;
    }
    if (second != "") {
      if (second == "L")
        iter--;
      else
        iter++;
    }
    if (third != "") {
      if (third == "!")
        break;
      else
        state = third;
    }
  }
}

list<string> input() {
  string input_text;
  cin >> input_text;

  list<string> lst;
  lst.push_back("λ");
  for (int i = 0; i < input_text.size(); i++) {
    string tmp(1, input_text[i]);
    lst.push_back(tmp);
  }
  lst.push_back("λ");
  return lst;
}

void print(string mode, list<string> lst, list<string>::iterator iter) {
  for (list<string>::iterator i = lst.begin(); i != lst.end(); i++) {
    if (mode == "--step" && i == iter) {
      cout << "|" << *i << "|";
    } else
      cout << *i;
  }
}

int main(int argc, char *argv[]) {
  string mode = argv[1];
  string filename = argv[2];
  list<string> lst = input();

  map<string, map<string, string>> mps = parse_csv(filename);

  list<string>::iterator iter = lst.begin();
  iter++;

  iterations(mode, lst, mps, iter);

  print(mode, lst, iter);
}
