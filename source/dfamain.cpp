/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dfamain.cpp
 * Author: fordem
 *
 * Created on June 9, 2016, 8:52 AM
 */

#include <cstdlib>
#include "GroupHistogramCalculation.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    GroupHistogramCalculation gh("/home/fordem/Dropbox/FernandoDoutorado/LibPython/GraphUtils/simrng/res_arthur/", 3, 100000, 1.4);
    gh.calculateDFABarabasiFiles();
    gh.exportOriginReturn("histogramtest.dat");
    return 0;
}

