/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * <#Name#>
 * <#Uniqname#>
 *
 * Project 4: Battleship
 *
 * <#description#>
 */

#include <fstream>

#include "Player.h"
void Player::init_grid()
{
    for (int i = 0; i < MAX_GRID_SIZE; i++)
    {
        for (int j = 0; j < MAX_GRID_SIZE; j++)
        {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
}
Player::Player()
{
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val)
{
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

string Player::get_name()
{
    return name;
}

int Player::get_num_ships()
{

    return num_ships;
}

int Player::get_remaining_ships()
{
    return remaining_ships;
}

char Player::get_grid_at(int row, int col)
{
    return grid[row][col];
}

char Player::get_guess_grid_at(int row, int col)
{
    return grid[row][col];
}

void Player::add_ship(Ship ship)
{
    if (num_ships == MAX_NUM_SHIPS)
    {
        return;
    }
    ships[num_ships] = ship;
    num_ships++;
    remaining_ships++;
    for (int i = ship.get_start().get_row(); i <= ship.get_end().get_row(); i++)
    {
        for (int j = ship.get_start().get_col(); j <= ship.get_end().get_col(); j++)
        {
            grid[i][j] = SHIP_LETTER;
        }
    }
}

void Player::attack(Player &opponent, Position pos)
{
    if (opponent.get_grid_at(pos.get_row(), pos.get_col()) == SHIP_LETTER)
    {
        opponent.grid[pos.get_row()][pos.get_col()] == HIT_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] == HIT_LETTER;
        cout << name << " " << pos.get_row() + 1 << "," << (pos.get_col() + 1) + 'A' << " "
             << "Hit\n";

        // Loops through opponent's ships array and checks for hit in the given position
        for (int i = 0; i < sizeof(opponent.ships) / sizeof(Ship); i++)
        {
            Ship s = opponent.ships[i];
            if (s.has_position(pos))
            {
                s.hit();
            }
            if (s.has_sunk())
            {
                opponent.remaining_ships--;
                announce_ship_sunk(s.get_size());
            }
        }
    }
    else if (opponent.get_grid_at(pos.get_row(), pos.get_col()) == EMPTY_LETTER)
    {
        opponent.grid[pos.get_row()][pos.get_col()] == MISS_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] == MISS_LETTER;
        cout << name << " " << pos.get_row() + 1 << "," << (pos.get_col() + 1) + 'A' << " "
             << "Miss\n";
    }
    else
    {
        cout << name << " " << pos.get_row() + 1 << "," << (pos.get_col() + 1) + 'A' << " "
             << "Miss\n";
    }
}

void Player::announce_ship_sunk(int size)
{
    if (size == 2)
    {
        cout << "Congratulations " << name << " You sunk a Destroyer";
    }
    else if (size == 3)
    {
        cout << "Congratulations " << name << " You sunk a Submarine";
    }
    else if (size == 4)
    {
        cout << "Congratulations " << name << " You sunk a Battleship";
    }
    else
    {
        cout << "Congratulations " << name << " You sunk a Carrier";
    }
    return;
}

bool Player::load_grid_file(string filename)
{
    ifstream file_obj(filename);
    if (!file_obj)
    {
        return false;
    }
    string line;
    while (getline(file_obj, line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            // Erase everything other than space, numbers and letters
            if (!(line[i] >= '0' && line[i] <= '9' || line[i] == ' ' || line[i] >= 'A' && line[i] <= 'Z'))
            {
                line.erase(i, 1);
            }
        }
        //In the modifies line, the starting row will be on 0th index and starting colum will be in the 1st index
        //Same applies for ending row and column.
        Position start(line[0], line[1]), end(line[3], line[4]);
        Ship new_ship(start, end);
        add_ship(new_ship);
    }
}

bool Player::destroyed()
{
    if (remaining_ships == 0)
    {
        return true;
    }
    return false;
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid()
{
    ::print_grid(grid);
}

void Player::print_guess_grid()
{
    ::print_grid(guess_grid);
}
