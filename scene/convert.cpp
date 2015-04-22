#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

float data[512 * 106920];
unsigned header[3];

int main(int argc, char** argv) {
    std::string format = ""; 
/*    
    ifstream i("lsh.bin", ios::binary);
    i.read((char*)header, 12);
    cout << header[0] << " " << header[1] << " " << header[2] << std::endl;
    return 0;*/
    if (argc == 2) {
        format = argv[1];
    }
    freopen("hog.txt", "r", stdin);
    int size = 512 * 106920;
    for (int i = 0; i < size; ++i) {
        scanf("%f", &data[i]);
    }
    cout << "Read everything into memory\n";

    ofstream fs;
    
    if (format == "flann") {
        fs.open("flann.bin", ios::app | ios::out | ios::binary);
        if (fs.is_open())
            printf("DATA\n");
    } else if (format == "lsh") {
        fs.open("lsh.bin", ios::out | ios::binary);
        header[0] = 4;
        header[1] = 106920;
        header[2] = 512;
        fs.write((char*)header, 3 * 4);
    } else {
        fs.open("hog.bin", ios::out | ios::binary);
    }
    fs.write((char*)data, 512 * 106920 * sizeof(float));
    fs.close();

    return 0;
}
