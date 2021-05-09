#include "headers/levelread.h"
#include <fstream>
#include <string>
#include <vector>
#include "headers/config.h"
#include "headers/entity.h"

Level::~Level() {}
Level::Level(std::string filename) {
    parseFile(filename);
}

void Level::draw() {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}


void Level::parseFile(std::string filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    std::vector<Entity*> entities;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    length = lines.at(0).length();
    height = lines.size();
    grid = new char*[length];

    for (int i = 0; i < length; i++) {
        grid[i] = new char[height];
    }

    const std::string letters = "abcdefghijklmnopqrstuvwxyz";
    const std::string LH = "ABCDEF";
    const std::string RH = "GHIJKL";
    const std::string LV = "MNOPQRS";
    const std::string RV = "TUVWXYZ";

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            if (lines.at(j).at(i) == tiles.wall || letters.find((lines.at(j).at(i)) 
            != std::string::npos)) {
                grid[i][j] = tiles.wall;
            }
            else if (LH.find((lines.at(j).at(i)))) {
                //Door* door = new Door{};
            }
            else if (RH.find((lines.at(j).at(i)))) {

            }
            else if (LV.find((lines.at(j).at(i)))) {

            }
            else if (RV.find((lines.at(j).at(i)))) {

            }
            else {
                grid[i][j] = tiles.empty;
                switch (lines.at(j).at(i))
                {
                    case tiles.red_gem:
                    {
                        red_gems_remaining++;
                        Gem* gem = new Gem{i, j, Gem::RED};
                        entities.push_back(gem);
                        break;
                    }

                    case tiles.blue_gem:
                    {
                        blue_gems_remaining++;
                        Gem* gem = new Gem{i, j, Gem::BLUE};
                        entities.push_back(gem);
                        break;
                    }

                    case tiles.water:
                    {
                        grid[i][j] = tiles.water;
                        break;
                    }

                    case tiles.lava:
                    {
                        grid[i][j] = tiles.lava;
                        break;
                    }

                    case tiles.green_mud:
                    {
                        grid[i][j] = tiles.green_mud;
                        break;
                    }

                    case tiles.red_spawn:
                    {
                        red_spawn_x = i;
                        red_spawn_y = j;
                        break;
                    }

                    case tiles.blue_spawn:
                    {
                        blue_spawn_x = i;
                        blue_spawn_y = j;
                        break;
                    }

                    case tiles.red_exit:
                    {
                        grid[i][j] = tiles.red_exit;
                        break;
                    }

                    case tiles.blue_exit:
                    {
                        grid[i][j] = tiles.blue_exit;
                        break;
                    }

                    case tiles.pressure_plate:
                    {
                        char id = lines.at(j).at(i+1);
                        PressurePlate* pressurePlate = new PressurePlate{i, j, id};
                        entities.push_back(pressurePlate);
                        break;
                    }

                    case tiles.sw:
                    {
                        char id = lines.at(j).at(i+1);
                        Switch* sw = new Switch{i, j, id};
                        entities.push_back(sw);
                        break;
                    }

                    case tiles.block:
                    {
                        Block* block = new Block{i, j};
                        entities.push_back(block);
                        break;
                    }
                }
            }
        }
    }
}
