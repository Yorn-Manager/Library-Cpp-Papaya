/*
** EPITECH PROJECT, 2024
** papaya
** File description:
** library
*/

#include "Papaya.hpp"

Papaya::Error::Error(std::string const &message)
{
    this->_message = message;
}

const char *Papaya::Error::what() const noexcept
{
    return this->_message.c_str();
}


Papaya::Papaya(std::string path, std::string name, std::vector<std::string> keys)
{
    this->_path = path;
    this->_name = name;
    this->_keys = keys;
}

Papaya::Papaya(std::string path, std::string name)
{
    std::ifstream file(path + name + ".papaya");
    if (file.is_open()) {
        std::string line;
        std::string token;
        std::getline(file, line);
        std::stringstream ss(line);
        while (std::getline(ss, token, ';')) {
            _keys.push_back(token);
        }
    } else {
        throw Error("Papaya \"" + path + name + ".papaya\" not found");
    }
}

void Papaya::save() const
{
    std::ofstream file(this->_path + this->_name + ".papaya");
    if (file.is_open()) {
        for (const auto &key : this->_keys) {
            file << key;
            if (key != this->_keys.back())
                file << ";";
            else
                file << std::endl;
        }
        for (const auto &data : this->_datas) {
            for (const auto &key : this->_keys) {
                file << data.at(key);
                if (key != this->_keys.back())
                    file << ";";
                else
                    file << std::endl;
            }
        }
        file.close();
    } else {
        throw Error("Cannot open file");
    }
}

void Papaya::add(std::vector<std::string> data)
{
    if (data.size() != this->_keys.size())
        throw Error("Data size does not match keys size");
    std::unordered_map<std::string, std::string> map;
    for (size_t i = 0; i < this->_keys.size(); i++)
        map[this->_keys[i]] = data[i];
    _datas.push_back(map);
}

void Papaya::remove(std::string key, std::string value)
{
    if (std::find(this->_keys.begin(), this->_keys.end(), key) == this->_keys.end())
        throw Error("Key not found");
    for (size_t i = 0; i < this->_datas.size(); i++) {
        if (this->_datas[i].at(key) == value) {
            this->_datas.erase(this->_datas.begin() + i);
            return;
        }
    }
    throw Error("Data not found");
}

void Papaya::replace(std::string key, std::string value, std::vector<std::string> data)
{
    if (data.size() != this->_keys.size())
        throw Error("Data size does not match keys size");
    if (std::find(this->_keys.begin(), this->_keys.end(), key) == this->_keys.end())
        throw Error("Key not found");
    remove(key, value);
    add(data);
}

void Papaya::view() const
{
    for (const auto &key : this->_keys) {
        std::cout << key;
        if (key != this->_keys.back())
            std::cout << " | ";
        else
            std::cout << std::endl;
    }
    for (const auto &data : this->_datas) {
        for (const auto &key : this->_keys) {
            std::cout << data.at(key);
            if (key != this->_keys.back())
                std::cout << " | ";
            else
                std::cout << std::endl;
        }
    }
}