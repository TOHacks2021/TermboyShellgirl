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
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            std::cout << grid[j][i];
        }
        std::cout << std::endl;
    }
}

char**
Level::getGrid() const
{
	return this->grid;
}

int
Level::getLength() const
{
	return this->length;
}

int
Level::getHeight() const
{
	return this->height;
}


void Level::parseFile(std::string filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

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
            char c = lines.at(j).at(i);
            if (c == tiles.wall || letters.find(c) != std::string::npos) {
                grid[i][j] = tiles.wall;
            }
            else if (LH.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::LH};
                entities.push_back(door);
            }
            else if (RH.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::RH};
                entities.push_back(door);
            }
            else if (LV.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::LV};
                entities.push_back(door);
            }   
            else if (RV.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::RV};
                entities.push_back(door);
            }
            else {
                grid[i][j] = tiles.empty;
                
                switch (c)
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
                
                        entities.push_back(new Exit{i, j, ColouredEntity::RED});
                        break;
                    }

                    case tiles.blue_exit:
                    {
                 
                        entities.push_back(new Exit{i, j, ColouredEntity::BLUE});
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
