
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

void cityjson_demo();
void cityjsonfeature_demo();
void jsonfg_demo();
void tu3djson_demo();
void onegeom_demo();
void indoorgml_demo();

int main(int argc, char *argv[])
{
  cityjson_demo();
  cityjsonfeature_demo();
  jsonfg_demo();
  tu3djson_demo();
  onegeom_demo();
  indoorgml_demo();
  return 0;
}


void cityjson_demo() 
{
  std::cout << "\n=== cityjson_demo() ===" << std::endl;
  std::ifstream input("../../data/cityjson/cube.json");
  json j;
  //-- deserialise the file
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  //-- validate it
  try {
    json re = val3dity::validate(j);
    std::cout << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}


void cityjsonfeature_demo() {
  std::cout << "\n=== cityjsonfeature_demo() ===" << std::endl;
  std::string input("/Users/hugo/data/cityjson/v1.1/denhaag/5.jsonl");
  std::ifstream infile(input.c_str(), std::ifstream::in);
  if (!infile)
    return;
  //-- transform
  json jtransform;
  std::string l;
  int linecount = 1;
  while (std::getline(infile, l)) 
  {
    std::istringstream iss(l);
    json j;
    try {
      iss >> j;
    }
    catch (nlohmann::detail::parse_error e) {
      break;
    }
    if (j["type"] == "CityJSON") {
      jtransform = j["transform"];
    }
    if (j["type"] == "CityJSONFeature") {
      try {
        bool re = val3dity::is_valid(j, jtransform);
        std::cout << "Input line #" << linecount << " is " << re << std::endl;
      }
      catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
      }
    }
    linecount++;
  }
}


void jsonfg_demo() 
{
  std::cout << "\n=== jsonfg_demo() ===" << std::endl;
  std::ifstream input("../../data/test_jsonfg/building.fg.json");
  // std::ifstream input("../../data/test_jsonfg/cubes.fg.json");
  json j;
  //-- deserialise the file
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  //-- validate it
  try {
    bool re = val3dity::is_valid(j);
    std::cout << "Input file is " << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}

void tu3djson_demo() 
{
  std::cout << "\n=== tu3djson_demo() ===" << std::endl;
  std::ifstream input("../../data/test_tu3djson/cube3.json");
  json j;
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  json re = val3dity::validate(j);
  std::cout << re << std::endl;
}



void onegeom_demo() 
{
  std::cout << "\n=== onegeom_demo() ===" << std::endl;
  std::ifstream input("../../data/cityjson/cube.json");
  json j;
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  json onegeom = j["CityObjects"]["id-1"]["geometry"][0];
  onegeom["vertices"] = j["vertices"];
  // std::cout << onegeom << std::endl;
  try {
    bool re = val3dity::is_valid(onegeom);
    std::cout << "Input file is " << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}


void indoorgml_demo() 
{
  std::cout << "\n=== indoorgml_demo() ===" << std::endl;
  std::stringstream buffer;
  buffer << std::ifstream("../../data/gml/FZK-Haus_full.gml").rdbuf();
  bool re = val3dity::is_valid(buffer.str().c_str());
   // re = val3dity::validate(buffer.str().c_str());
  std::cout << "Input file is ";
  if (re == true)
    std::cout << "VALID!" << std::endl;
  else
    std::cout << "INVALID :(" << std::endl;
}
