#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <random>

std::vector<std::string> split_string(const std::string& input_str, const char delim)
{
    std::istringstream tmp(input_str);
    std::vector<std::string> input;
    while (tmp){
        std::string s;
        if (!std::getline(tmp, s, ' ')) break;
        input.push_back(s);
    }  
    return input;
}

typedef std::pair<std::vector<std::pair<unsigned,bool> >, double> clause_type;

struct instance_type
{
    std::size_t N_;
    std::vector<clause_type> clauses_;
};

instance_type read_graph_dimacs(const std::string& config_file)
{
    const bool weighted(config_file.find(".wcnf") != std::string::npos);

    instance_type I;

    std::ifstream in(config_file);
    assert(in);

    double hard_threshold(std::numeric_limits<double>::max());

    while(in){

        std::string input_str;

        if(!std::getline(in,input_str)) break;

        if(input_str[0] == 'c' || input_str[0] == 'p'){

            if(input_str[0] == 'p'){
                const auto input(split_string(input_str,' '));
                I.N_ = std::stoul(input[2]);
                if(input.size() == 5)
                    hard_threshold = std::stod(input[4]);
            }

        }
        else{

            const auto input(split_string(input_str,' '));

            const double val(weighted ? std::stod(input[0]) : 1.0);

            assert(val <= hard_threshold);

            if(val != 0.0){

                clause_type clause;

                clause.second = val;

                for(unsigned i = (weighted ? 1 : 0); i < input.size()-1; ++i){
                    const int var(std::stoi(input[i]));
                    const unsigned site(std::abs(var));
                    clause.first.push_back(std::make_pair(site-1,(var > 0)));
                }

                I.clauses_.push_back(clause);
            }
        }
    }
    in.close();

    return I;
}

class solver
{

public:

    solver(const instance_type& I)
        : N_(I.N_)
        , clauses_(I.clauses_)
        , variables_(I.N_)
    {}

    std::vector<bool> get_variables() const {return variables_;}

    void solve()
    {
        //randomly guess a solution
        for(unsigned i = 0; i < N_; ++i)
            variables_[i] = (drand48() < 0.5);
    }

private:

    const std::size_t N_;
    const std::vector<clause_type> clauses_;
    std::vector<bool> variables_;
};

int main(int argc, char* argv[])
{
    assert(argc == 2);
    const std::string graph_file(argv[1]);

    const auto I(read_graph_dimacs(graph_file));

    solver S(I);

    S.solve();

    const auto variables(S.get_variables());

    std::cout << "v ";
    for(unsigned i = 0; i < variables.size(); ++i)
        std::cout << (variables[i] ? "" : "-") << std::to_string(i+1) << " ";
    std::cout << std::endl;

    return 0;
}
