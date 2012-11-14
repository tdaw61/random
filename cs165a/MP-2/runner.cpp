/* 
 * File:   main.cpp
 * Author: Taylor
 *
 * Created on March 13, 2012, 6:57 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <math.h>


using namespace std;

vector<string> vocab;
int which;
double total_docs; //total number of docs
double total_f; //total number of docs that have faculty
double total_s;
double total_p;
double total_c;
double n_total_f; // total number of words that target faculty
double n_total_s;
double n_total_c;
double n_total_p;
bool push;

struct entry {
    string word;
    double freq;
};

/*
 * 
 */
int main(int argc, char** argv) {
    
    if(argc != 3)
    {
        cout << "wrong number of arguments.";
                
    }
    string line;

    ifstream myfile(argv[1]);
    if (myfile.is_open()) {
        while (myfile.good()) {
            getline(myfile, line);
            string tok;
            istringstream str(line);
            str >> tok;
            if (tok == "faculty") {
                which = 1;
                total_docs++;
                total_f++;
            } else if (tok == "course") {
                which = 2;
                total_docs++;
                total_c++;
            } else if (tok == "student") {
                which = 3;
                total_docs++;
                total_s++;
            } else if (tok == "project") {
                which = 4;
                total_docs++;
                total_p++;
            } else {
                //cout << "rand" << endl;
            }

            while (getline(str, tok, ' ')) {
                push = true;

                switch (which) {
                    case(1):
                        n_total_f++;
                        break;
                    case(2):
                        n_total_c++;
                        break;
                    case(3):
                        n_total_s++;
                        break;
                    case(4):
                        n_total_p++;
                        break;
                    default:
                        //cout << "random";
                        break;
                }
                if (vocab.size() == 0)
                    vocab.push_back(tok);

                for (int i = 0; i < vocab.size(); i++) {
                    if (tok == vocab[i]) {
                        push = false;
                        break;
                    }
                }
                if (push)
                    vocab.push_back(tok);
            }
        }
        myfile.close();
    }
    //done with vocab and random stuff
    ifstream file(argv[1]);
    string liner;
    int voc = vocab.size();
    double size = vocab.size();
    double f_array [voc];
    double s_array [voc];
    double p_array [voc];
    double c_array [voc];
    for (int i = 0; i < voc; i++) {
        f_array[i] = 0;
        s_array[i] = 0;
        p_array[i] = 0;
        c_array[i] = 0;
    }

    if (file.is_open()) {
        while (file.good()) {
            getline(file, liner);
            stringstream stream(liner);
            string tok;
            stream >> tok;
            //getline(stream, tok, ' ');
            if (tok == "faculty") {
                which = 1;
            }
            if (tok == "course") {
                which = 2;
            }
            if (tok == "student") {
                which = 3;
            }
            if (tok == "project") {
                which = 4;
            }           
                while (getline(stream, tok, ' ')) {
                 for (int i = 0; i < voc; i++) {
                    if (tok == (vocab[i])) {
                        switch (which) {
                            case(1):
                                f_array[i] = f_array[i] + 1;
                                break;
                            case(2):
                                c_array[i] = c_array[i] + 1;
                                break;
                            case(3):
                                s_array[i] = s_array[i] + 1;
                                break;
                            case(4):
                                p_array[i] = p_array[i] + 1;
                                break;


                        }
                    }
                }
            }

            //cout << tok << endl;
        }
        file.close();
    }
    /*
    cout << n_total_c << endl;
    cout << n_total_f << endl;
    cout << n_total_p << endl;
    cout << n_total_s << endl;
    cout << total_c << endl;
    cout << total_f << endl;
    cout << total_s << endl;
    cout << total_p << endl;
    cout << total_docs << endl;
    cout << "voc size " << voc;
     * /
   
    //calculate probabilities.
    /*for( int i = 0; i < voc; i++)
    {
          f_prob += log(((double)f_array[i] + 1)/(n_total_f + voc));
          c_prob += log(((double)c_array[i] + 1)/(n_total_c + voc));
          s_prob += log(((double)s_array[i] + 1)/(n_total_s + voc));
          p_prob += log(((double)p_array[i] + 1)/(n_total_p + voc));
          f_prob += log(total_f/total_docs);
          c_prob += log(total_c/total_docs);
          s_prob += log(total_s/total_docs);
          p_prob += log(total_p/total_docs);
    }*/

    vector<string> output;
    file.open(argv[2]);
    //file.open("pred_test.txt");
    double res[4];
    int index;

    //ofstream out;
    //out.open("results.txt");

    if (file.is_open()) {
        while (file.good()) {

            res[0] = 0;
            res[1] = 0;
            res[2] = 0;
            res[3] = 0;

            getline(file, line);
            string token;

                istringstream is(line);
                while (getline(is, token, ' ')) 
                {
                    for (int i = 0; i < voc; i++)
                    {
                        if (token == vocab[i])
                        {
                            res[0] += log((f_array[i] + 1)/(n_total_f + size));
                            res[1] += log((c_array[i] + 1)/(n_total_c + size));
                            res[2] += log((s_array[i] + 1)/(n_total_s + size));
                            res[3] += log((p_array[i] + 1)/(n_total_p + size));
                            break;
                        }
                    }
                }
                
                res[0] = res[0] + log(total_f/total_docs);
                res[1] = res[1] + log(total_c/total_docs);
                res[2] = res[2] + log(total_s/total_docs);
                res[3] = res[3] + log(total_p/total_docs);
                //out << "f " << res[0] << endl;
                //out << "c " << res[1] << endl;
                //out << "s " << res[2] << endl;
                ///out << "p " << res[3] << endl;
                
                index = 0;
                double maxval;
                maxval = res[0];
                
                for(int i = 0; i < 4;i++)
                {
                    if(res[i] > maxval)
                    {
                        index = i;
                        maxval = res[i];
                    }
                }
                switch(index)
                {
                    case(0): output.push_back("faculty"); break;
                    case(1): output.push_back("course"); break;
                    case(2): output.push_back("student"); break;
                    default: output.push_back("project"); break;
                    
                }
            
        }
    }
    //cout << t << endl;
    
    file.close();
    
    ofstream outfile;
    outfile.open("predictions.txt");
    
    for(int i = 0; i < output.size();i++)
        outfile << output[i] << endl;
    
    outfile.close();
    
    
    
    ///testing accuracy stuff
    /*
    vector<string> ans;
    double count = 0;
    double total = output.size();
    file.open("pred_test.txt");
    if(file.is_open())
    {
        while(file.good())
        {
            getline(file,line);
    
            
            istringstream is(line);
            
            is >> line;
            
            if((line == "\0")!=0)
                ans.push_back(line);
        }
    }
    if(ans.size() != total)
        cout << "different lengths" << endl;
    
    for(int i = 0; i < total; i++)
    {
        if(output[i] == ans[i])
            count++;
    }
    
    cout << "accuracy : " << count/total*100 << "%";
      */
    

    return 0;
}


