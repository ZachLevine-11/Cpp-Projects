#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace Rcpp;

// [[Rcpp::export]]
std::vector<std::vector<std::string> > read_csv_speedy(std::string fn);

//Helper function to read csv files.
std::vector<std::vector<std::string> > read_csv_speedy(std::string fn){
    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::vector<std::string > > result;
    // Create our input filestream
    std::fstream fin; 
    fin.open(fn, std::ios::in); 
    std::vector<std::vector<std::string > > df;
    std::vector<std::string> row; 
    std:: string line, entry, temp; 
    // Grab a row rows.
    while (fin >> temp) { 
        row.clear(); 
        std::getline(fin, line, ','); 
        std::stringstream s(line); 
        // Grab the data stored in each row and store it in a string variable, 'entry' 
        while (std::getline(s, entry, ',')) {
            //Discard a line that begins with a comment indicator.
            char commentIndicator = '#';
            if (entry[0] == commentIndicator){
                break;
            }
                else{
                // Othwerwise, if we're not dealing with a commment, add all the column data  of that row to a vector
                row.push_back(entry); 
            }
        }
        df.push_back(row);
    }
    return df;
}
