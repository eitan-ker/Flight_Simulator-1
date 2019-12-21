// Copyright 2019 Meni Ashurov


void check_line(string &line, vector<string> &str_array) {
  const char* token = &(line[0]);
  const char* start = token;
  const char* check_space=token;
  int i = 0, passednumberingflag = 0, foundpattern = 0, astrophesflag=0,enterstringtoarray=0,counter=0,encounterlotofspaces=0;
  string c;
  regex r1("[0-9]*[.][ ]");
  if (*token == '/') {
    token++;
    if (*token == '/') {
      return;
    }
  }
  while (*token != '\0' && passednumberingflag==0) {
    token++;
    if (isalpha(*token) || *token == '}' ) {
      if (!regex_match(start, token, r1)) {
        cout << "illegal line format" << endl;
        return;
      }
      passednumberingflag=1;
    }
  }
  start = token;
  while (*token!='\0' && *token!='\n') {
    if(encounterlotofspaces==1) {
      start=check_space;
      token=check_space;
      counter=0;
    }
    if(*token == ' ' || *token == '(' || *token == ')' || *token == ',' ) {
      foundpattern=1;
      if(*token == ' ') {
        check_space = token;
        check_space++;
        while(*check_space==' ') {
          check_space++;
          counter++;
        }
        if(counter>0) {
          foundpattern=0;
          encounterlotofspaces=1;
        }
      }
    }
    if ((int)*token==34 && astrophesflag==0) {
      astrophesflag++;
      token++;
      start=token;
    }
    if((int)*token==34 && astrophesflag==1) {
      astrophesflag++;
    }
    if (astrophesflag==2) {
      foundpattern=1;
    }
    if(foundpattern==1) {
      foundpattern=0;
      enterstringtoarray=1;
      string key_str(start,token);
      c= key_str;
      if(c.compare("////") != 0 && c.compare("") != 0) {
        str_array.insert(str_array.end(), c);
        token++;
        start = token;
      } else {
        return; //encounter comment
      }
      if(astrophesflag==2) {
        token++;
        start=token;
        foundpattern=0;
      }
    }
    if(enterstringtoarray==0) {
      token++;
    } else {
      enterstringtoarray=0;
    }
  }
  string key_str(start,token);
  if(start!=token && *start!='\0') {
    c = key_str;
    str_array.insert(str_array.end(), c);
  }
}
void lexer(const char* file_path, vector<string> &str_array) {
  char *ptr = nullptr;
  string line;
  try {
    ifstream my_file(file_path);
    if (my_file.is_open()) {
      while ( getline (my_file,line) ) {
        check_line(line,str_array);
      }
      my_file.close();
    }
  }catch (const char *e) {
    cout << e << endl;
  }
}
void parser(char *str_array[]) {

}
int main(int argc, char* argv[]) {

  vector<string> str_array;
  lexer(argv[1], str_array);
  return 0;
}

