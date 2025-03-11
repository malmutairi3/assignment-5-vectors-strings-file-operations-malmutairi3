#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"

using namespace std;

 
void average_colors ( vector<Pixel> &pixel_list) {
    float sum_r = 0.0f, sum_g = 0.0f, sum_b = 0.0f;
    for (size_t i = 0; i < pixel_list.size(); i++) {
        sum_r += pixel_list[i].r;
        sum_g += pixel_list[i].g;
        sum_b += pixel_list[i].b;
    }
    float avg_r = sum_r / pixel_list.size();
    float avg_g = sum_g / pixel_list.size();
    float avg_b = sum_b / pixel_list.size();
    
    cout <<  "Average Colors:" <<  endl;
    cout << "R: " << avg_r << ", G: " <<  avg_g << ", B: " << avg_b << endl ;
}

 
void flip_vertically(vector<Pixel> &pixel_list) {
    int height = 256;  
    for ( int i = 0; i < pixel_list.size(); i++ ) {
        pixel_list[i].y =  height - 1 -  pixel_list[i].y;
        }
}

int main (int argc, char *argv[]) {
     
    if (argc < 2) {
        cout << "Incorrect Arguments !!" << endl;
        return 1;
    }
    
    string filename = argv[1];
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return 1;
    }
    
     
    vector <Pixel> pixel_list;
    string line;
    
     
    while (getline(infile, line)) {
        if(line.empty())
            continue;
        
        Pixel p;
        size_t pos = 0;
        size_t pos2 = line.find(',');
        
         
        string xStr = line.substr(0, pos2);
        p.x = stoi(xStr);
        
        pos = pos2 + 1;
        pos2 = line.find(',', pos);
        
        string yStr = line.substr(pos, pos2 - pos);
        p.y = stoi(yStr);
        
        pos = pos2 + 1;
        pos2 = line.find(',', pos);
         
        string rStr = line.substr(pos, pos2 - pos);
        p.r = stof(rStr);
        
        pos = pos2 + 1;
        pos2 = line.find(',', pos);
         
        string gStr = line.substr(pos, pos2 - pos);
        p.g = stof(gStr);
        
        pos = pos2 + 1;
         
        string bStr = line.substr(pos);
        p.b = stof(bStr);
        
         
        pixel_list.push_back(p);
    }
    infile.close();
    
     
    average_colors(pixel_list);
    flip_vertically(pixel_list);
    
    
    ofstream outfile("flipped.dat");
    if (!outfile) {
        cout << "Error creating output file: flipped.dat" << endl;
        return  1;
    }
    
      for (size_t i = 0; i < pixel_list.size(); i++) {
        outfile << pixel_list[i].x << ","
                << pixel_list[i].y << ","
                << pixel_list[i].r << ","
                << pixel_list[i].g << ","
                << pixel_list[i].b << "\n";
    }
    outfile.close();
    
    cout << "Flipped image saved to flipped.dat" << endl;
    return 0;
}
