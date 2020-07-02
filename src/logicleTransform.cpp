//#include <iostream>
#include "logicle.h"
#include <Rcpp.h>
using namespace std;
/**
 * Logicle tranform/inverse transform wrapper function, makes use of the Logicle
 *  class provided Wayne Moore for the underlying calculation of the transformation.
 *
 * */
//[[Rcpp::export]]
std::vector<double> logicle_transform(std::vector<double> input, double T, double W, double M, double A, bool isInverse) {

	unsigned nLen = input.size();

    try{
			Logicle lg = Logicle(T, W, M, A);
			for (unsigned i = 0; i < nLen; i++) {
			  if(isnan(input.at(i)))
			    continue;
			  
				if(isInverse)
					input.at(i) = lg.inverse(input.at(i)/M);
				else
					input.at(i) = lg.scale(input.at(i)) * M;
			}
    	}
    catch(const char * str){
      std::string tmp= "Logicle Exception: ";
      tmp += "T = " + to_string(T) + ", W = " + to_string(W) + ", M = " + to_string(M) + ", A = " + to_string(A) + "\n";
    	Rcpp::stop(tmp.append(str));
    }


    return(input);
}

