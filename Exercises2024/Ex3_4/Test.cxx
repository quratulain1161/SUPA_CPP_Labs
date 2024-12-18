/* Main File
Student Name: Quratulain Zahoor
Roll No: s2718548
University of Edinburgh 
Assignment# 2
Date : 19-November -2024
Submission Date :  13-December -2024

*/


// adding the header file and required libraries 
#include "FiniteFunctions.h"
#include "NormalDistribution.h"
#include "CauchyLorentzDistribution.h"
#include "NegativeCrystalBallDistribution.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
using namespace std;

//Function to read the mysterfile and read the 500 points as the limit 
vector<double> readDataFromFile(const string& filename) {
    vector<double> data;
    double value;
    int count = 0;
    // just cross check if the file exists inside the directory or not
    if (!std::filesystem::exists(filename)) {
        cout << "Error in reported:file '" << filename << "' does not even present inside the directory." << endl;
        return data;  // return it empty in case of failure
    }
    // opened the file 
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open the file'" << filename << "'." << endl; //returning the error as warning
        return data;  // Return an empty vector as a signal of failure
    }

    // limiting the data to 500 points here 
    while (file >> value && count < 1000000) {
        data.push_back(value); //pushing the values back here
        count++; //doing the increment 
    }

    // warning in case no valid data point exists inside the file
    if (data.empty()) {
        cout << "Warning: No valid data found inside your file '" << filename << "'." << endl;
    } 
    else {
        cout << "File '" << filename << "' successfully read with " << data.size() << " data points." << endl;
    }

    file.close(); 
    // closed the file

    return data;
}
// this is the main section of the Test file

int main() {
    double range_min = -15.0;  
    double range_max = 15.0;
    double step_size = 0.1; 
    int num_samples = 10000000;
    double proposal_stddev = 1.0;
    double sigma = 0.5;
    std::string filename = "Outputs/data/MysteryData16341.txt";   

// this is our data file generated from GenerateRandomData
    std::string sample_filename = "Outputs/data/sampled_data.txt"; 
     //sampling data

    string output_file = "MysteryPlot";
    FiniteFunction funct(range_min, range_max, output_file);
    funct.plotFunction();
     vector<double> Mystry = readDataFromFile(sample_filename); // taking the myster data
    if (!Mystry.empty()) {
     funct.plotData(Mystry, 200, false);   //50 : NBins and data points set true
    }
    //plotting the data as well
    vector<double> datapoints = readDataFromFile(filename); // taking the myster data
    if (!datapoints.empty()) {
     funct.plotData(datapoints, 200, true);   //50 : NBins and data points set true
    }

    cout << "This is default function ..." << endl;
    FiniteFunction function;
   

      std::vector<double> sampled_data = function.sample(num_samples, sigma);

    // Optionally, print the sampled data
    for (const auto& sample : sampled_data) {
        std::cout << sample << std::endl;
    }

   
 
    // Plot the Normal Distribution
    std::cout << "Checking Normal Distributions..." << std::endl;
    double mean = 2.2; //need to set the shape 
    double stddev = 2.0;
    string output_file1 = "NormalDistribution"; // the normal Distribution png 
    // creating the instance
    NormalDistribution normalDist(range_min, range_max, output_file1, mean, stddev); 
    //std::vector<double> sampled_data = normalDist.sample(num_samples, proposal_stddev); 
    normalDist.plotFunction();
    vector<double> normal = readDataFromFile(filename); // taking the myster data
    if (!normal.empty()) {
      normalDist.plotData(normal, 200, true);   //50 : NBins and data points set true
    }
     vector<double> normalsample = readDataFromFile(sample_filename); // taking the myster data
    if (!normalsample.empty()) {
     normalDist.sample(100000,0.5);
     normalDist.plotData(normalsample, 200, false);   //50 : NBins and data points set true
    }

    // This section is CauchyLorentzDistribution 
    double x0 = 2.7;   // Location parameter ,removing it from 0.0
    double gamma = 1.8; //scaling parameters , this helps for fit the distribution
    string output_file4 = "CauchyLorentzDistribution";
    CauchyLorentzDistribution cld(range_min, range_max, output_file4, x0, gamma, step_size);
    cld.plotFunction(); //plot the function 
    vector<double> Cauchy = readDataFromFile(filename);
    if (!Cauchy.empty()) {
        cld.plotData(Cauchy, 200, true);      //plotting the Cauchy function
    }
    
    vector<double> Cauchysample = readDataFromFile(sample_filename);
    if (!Cauchysample.empty()) {
        cld.sample(100000,0.5);
        cld.plotData(Cauchysample, 200, false);      //plotting the Cauchy function
    }
    
   //This section is for NegativeCrystalBallDistribution 
    double x_bar = 3.0;   //mean value, i adjusted it to fit 3.0
    double sigma1 = 2.2;   // standard deviation value 
    double alpha = 2.0;   // transition parameter to 2
    double n = 3.0;       // n is the tail parameter
    string output_file2 = "NegativeCrystalBallDistribution"; // this png for distribution
    NegativeCrystalBallDistribution ncbdDist(range_min, range_max, output_file2, x_bar, sigma1, alpha, n, step_size);
    ncbdDist.plotFunction(); // plot the ncbd
    // Read and plot Negative Crystal Ball Distribution data
     vector<double> Crystal = readDataFromFile(filename);
    if (!Crystal.empty()) {
        ncbdDist.plotData(Crystal, 200, true);  // Use 100 bins for histogram-like plotting, setting 'false' for data

    }
    vector<double> Crystalsample = readDataFromFile(sample_filename);
    if (!Crystalsample.empty()) {
        ncbdDist.sample(100000,0.5);
        ncbdDist.plotData(Crystalsample, 200, false);  // Use 100 bins for histogram-like plotting, setting 'false' for data

    }


    std::cout<< "Successful: you can see the plot inside the Output/data directories"<<std::endl;

    return 0; 
}
