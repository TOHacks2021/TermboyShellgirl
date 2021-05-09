#include "headers/levelread.h"
#include <fstream>
#include <string>
#include <vector>
#include "headers/config.h"
#include "headers/entity.h"

const char getDoorDir(std::vector<std::string> lines, int x, int y);
void bindControllerById(ControlEntity* controller, std::vector<Door*> doors, char id);

Level::~Level() {}
Level::Level(std::string filename) {
	this->filename = filename;
	this->red_gems_remaining = 0;
	this->blue_gems_remaining = 0;
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
    const std::string C_L = "ABCDEF";
    const std::string C_U = "GHIJKL";
    const std::string C_R = "MNOPQRS";
    const std::string C_D = "TUVWXYZ";

	const int temp_max_dist_change_later = 4;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            char c = lines.at(j).at(i);
            if (c == tiles.wall || letters.find(c) != std::string::npos) {
                grid[i][j] = tiles.wall;
            }
            else if (C_L.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::C_L, getDoorDir(lines, i, j), temp_max_dist_change_later};
                doors.push_back(door);
            }
            else if (C_U.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::C_U, getDoorDir(lines, i, j), temp_max_dist_change_later};
                doors.push_back(door);
            }
            else if (C_R.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::C_R, getDoorDir(lines, i, j), temp_max_dist_change_later};
                doors.push_back(door);
            }   
            else if (C_D.find(c) != std::string::npos) {
                Door* door = new Door{i, j, c, Door::C_D, getDoorDir(lines, i, j), temp_max_dist_change_later};
                doors.push_back(door);
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
                        Player* red_player = new Player(i, j, ColouredEntity::RED);
                        this->red_player = red_player;
                        break;
                    }

                    case tiles.blue_spawn:
                    {
                        blue_spawn_x = i;
                        blue_spawn_y = j;
                        Player* blue_player = new Player(i, j, ColouredEntity::BLUE);
                        this->blue_player = blue_player;
                        break;
                    }

                    case tiles.red_exit:
                    {
						this->red_exit = new Exit(i, j, ColouredEntity::RED);
                        break;
                    }

                    case tiles.blue_exit:
                    {
                        this->blue_exit = new Exit(i, j, ColouredEntity::BLUE);
                        break;
                    }
					case tiles.pressure_plate:
					{
						char id = lines.at(j+1).at(i);
						PressurePlate* pressurePlate = new PressurePlate{i, j, id};
						controllers.push_back(pressurePlate);
						break;
					}
					case tiles.sw:
					{
						char id = lines.at(j+1).at(i);
						Switch* sw = new Switch{i, j, id};
						controllers.push_back(sw);
						break;
					}
                    case tiles.block:
                    {
                        Block* block = new Block{i, j};
                        blocks.push_back(block);
                        break;
                    }
                }
            }
        }
    }

}


const char
getDoorDir(std::vector<std::string> lines, int x, int y)
{
	if (lines.at(y).at(x+1) == '-') return Door::M_R;
	if (lines.at(y-1).at(x) == '|') return Door::M_U;
	if (lines.at(6).at(x-1) == '-') return Door::M_L;
	if (lines.at(y+1).at(x) == '|') return Door::M_D;
	fprintf(stderr, "u got issues with yo doors bro,\n");
}

void Level::remove_blue_gem() {
    this->blue_gems_remaining--;
}

void Level::remove_red_gem() {
    this->red_gems_remaining--;
}

void
Level::resetSpawn()
{
	this->red_player->setPos(this->red_spawn_x, this->red_spawn_y);
	this->blue_player->setPos(this->blue_spawn_x, this->blue_spawn_y);
}

