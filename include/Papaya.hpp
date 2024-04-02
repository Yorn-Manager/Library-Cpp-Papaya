/*
** EPITECH PROJECT, 2024
** papaya
** File description:
** library
*/

#ifndef PAPAYA_H_
    #define PAPAYA_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <exception>
#include <algorithm>

class Papaya
{
    public:
        class Error: public std::exception
        {
            public:
                Error(std::string const &message);
                const char *what() const noexcept override;

            private:
                std::string _message;
        };

        Papaya(std::string path, std::string name, std::vector<std::string> keys);
        Papaya(std::string path, std::string name);
        ~Papaya() = default;

        void save() const;
        void add(std::vector<std::string> data);
        void remove(std::string key, std::string value);
        void replace(std::string key, std::string value, std::vector<std::string> data);
        void view() const;

    private:
        std::string _path;
        std::string _name;
        std::vector<std::string> _keys;
        std::vector<std::unordered_map<std::string, std::string>> _datas;
};

#endif /* PAPAYA_H_ */
