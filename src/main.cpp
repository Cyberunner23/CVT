/*
Copyright 2014 Alex Frappier Lachapelle

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


std::string outputFilePath   = "Ver.hpp";
std::string progressFilePath = "progress.txt";
std::string templateFilePath = "template.hpp";

int major;
int minor;
int patch;
int build;
bool isMajorIncremented = false;
bool isMinorIncremented = false;
bool isPatchIncremented = false;
bool isBuildIncremented = false;

std::ifstream templateRead;
std::ifstream progressRead;
std::ofstream progressWrite;
std::ofstream verWrite;

std::string templateFileData;

std::string helpText = "CVT - Cyberunner23's Version Tool\n"
                       "\n"
                       "A simple tool to increment version numbers in a file.\n"
                       "\n"
                       "Usage: CVT [option1] [option2] ...\n"
                       "\n"
                       "Options:\n"
                       "\n"
                       "-h --help\n"
                       "    Show this help text.\n"
                       "\n"
                       "-stp --set-template-path [file path]\n"
                       "    Sets the path to the template. Default: ./template.hpp\n"
                       "\n"
                       "-sop --set-output-path [file path]\n"
                       "    Sets the path for the generated file. Default: ./Ver.hpp\n"
                       "\n"
                       "-spp --set-progress-path [file path]\n"
                       "    Sets the path to the progress file. Default: ./progress.txt\n"
                       "\n"
                       "-iM --increment-major\n"
                       "    Increments the Major version and replaces <VER_MAJOR>.\n"
                       "\n"
                       "-im --increment-minor\n"
                       "    Increments the minor version and replaces <VER_MINOR>.\n"
                       "\n"
                       "-ip --increment-patch\n"
                       "    Increments the patch version and replaces <VER_PATCH>.\n"
                       "\n"
                       "-ib --increment-build\n"
                       "    Increments the build version and replaces <VER_BUILD>.\n";


void replaceAll(std::string& str, const std::string& from, const std::string& to);


int main(int argc, char* argv[]){

    if(argc == 1){
        std::cout << "INSUFFICIENT ARGUMENTS" << std::endl;
        std::cout << helpText << std::endl;
        return 0;
    }

    std::cout << "CVT is being called with arguments: " << std::endl << "\t";

    for(int i = 1; i< argc; i++){
        std::cout << argv[i] << " ";
    }

    std::cout << std::endl;

    for(int i = 1; i < argc; i++){

        if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
            std::cout << helpText << std::endl;
            break;        
        }else if(strcmp(argv[i], "--set-template-path") == 0 || strcmp(argv[i], "-stp") == 0){

            if(i + 1 == argc){
                std::cout << "INSUFFICIENT ARGUMENTS FOR -stp" << std::endl;
                std::cout << helpText << std::endl;
                break;
            }

            templateFilePath = argv[i + 1];
            i++;

        }else if(strcmp(argv[i], "--set-output-path") == 0 || strcmp(argv[i], "-sop") == 0){

            if(i + 1 == argc){
                std::cout << "INSUFFICIENT ARGUMENTS FOR -sop" << std::endl;
                std::cout << helpText << std::endl;
                break;
            }

            outputFilePath = argv[i + 1];
            i++;

        }else if(strcmp(argv[i], "--set-progress-path") == 0 || strcmp(argv[i], "-spp") == 0){

            if(i + 1 == argc){
                std::cout << "INSUFFICIENT ARGUMENTS FOR -spp" << std::endl;
                std::cout << helpText << std::endl;
                break;
            }

            progressFilePath = argv[i + 1];
            i++;

        }else if(strcmp(argv[i], "--increment-major") == 0 || strcmp(argv[i], "-iM") == 0){
            isMajorIncremented = true;
        }else if(strcmp(argv[i], "--increment-minor") == 0 || strcmp(argv[i], "-im") == 0){
            isMinorIncremented = true;
        }else if(strcmp(argv[i], "--increment-patch") == 0 || strcmp(argv[i], "-ip") == 0){
            isPatchIncremented = true;
        }else if(strcmp(argv[i], "--increment-build") == 0 || strcmp(argv[i], "-ib") == 0){
            isBuildIncremented = true;
            //std::cout << "buils gets incremented" << std::endl;
        }else{
            std::cout << "INVALIG ARGUMENT: " << argv[i] << std::endl;
            std::cout << helpText << std::endl;
        }
    }


    progressRead.open(progressFilePath);
    if(!progressRead.is_open()){
        std::cout << "Cant't open the progress file!" << std::endl;
        return -1;
    }

    char tmp[32];



    progressRead.getline(tmp, 32);
    major = atoi(tmp);

    progressRead.getline(tmp, 32);
    minor = atoi(tmp);

    progressRead.getline(tmp, 32);
    patch = atoi(tmp);

    progressRead.getline(tmp, 32);
    build = atoi(tmp);

    if(isMajorIncremented){
        major++;
        minor = 0;
        patch = 0;
    }

    if(isMinorIncremented){
        minor++;
        patch = 0;
    }

    if(isPatchIncremented) patch++;

    if(isBuildIncremented) build++;

    progressRead.close();


    templateRead.open(templateFilePath);
    if(!templateRead.is_open()){
        std::cout << "Can't open the template file!!" << std::endl;
        return -2;
    }

    templateFileData.assign((std::istreambuf_iterator<char>(templateRead)), std::istreambuf_iterator<char>());

    templateRead.close();

    replaceAll(templateFileData, "<VER_MAJOR>", std::to_string(major));
    replaceAll(templateFileData, "<VER_MINOR>", std::to_string(minor));
    replaceAll(templateFileData, "<VER_PATCH>", std::to_string(patch));
    replaceAll(templateFileData, "<VER_BUILD>", std::to_string(build));

    verWrite.open(outputFilePath, std::ios::trunc);
    if(!verWrite.is_open()){
        std::cout << "Can't open output file!" << std::endl;
        return -3;
    }

    verWrite << templateFileData << std::flush;

    verWrite.close();


    progressWrite.open(progressFilePath, std::ios::trunc);
    if(!progressWrite.is_open()){
        std::cout << "Can't open the progress file!" << std::endl;
        return -4;
    }

    progressWrite << major << "\n" << minor << "\n" << patch << "\n" << build << std::flush;

    std::cout << "Major is now: " << major << std::endl;
    std::cout << "Minor is now: " << minor << std::endl;
    std::cout << "Patch is now: " << patch << std::endl;
    std::cout << "Build is now: " << build << std::endl;


    return 0;
}


void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}























