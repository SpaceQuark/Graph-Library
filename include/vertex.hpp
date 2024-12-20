#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "utils.hpp"
#include <iostream>
#include <array>
#include <string>
#include <functional> // For std::hash

// Forward declaration
class Vertex; 

struct Color {
    enum Value : uint8_t{
        Red,
        Green,
        Blue,
        Yellow,
        Black,
        White
    };

    Value value;
    Color(Value v) : value(v) {}

    inline string to_string() const {
        switch (value) {
            case Red: return "Red";
            case Green: return "Green";
            case Blue: return "Blue";
            case Yellow: return "Yellow";
            case Black: return "Black";
            case White: return "White";
            default: return "Unknown";
        }
    }

    bool operator==(const Color& other) const{
        return value == other.value;
    }

    bool operator==(Value other_value) const{
        return value == other_value;
    }
};


/*
    Vertex structure representing a node with two key properties:

    - id: A unique identifier for the vertex 
    - name: A fixed-size character array to store the vertex name (default value of )
*/
struct Vertex {
    uint64_t id;       
    std::array<char, 50> name; 
    Color color;       

    Vertex(uint64_t id_, const string& name_ = "", Color color_ = Color::Black) : id(id_), color(color_) {
       size_t result = snprintf(name.data(), name.size(), "%.*s", static_cast<int>(std::min(name_.size(), name.size() - 1)), name_.c_str());

        if (result >= name.size()) {
          std::cerr << "Warning: name truncated to fit into 50 characters." << std::endl;
       }
    }
    
    virtual ~Vertex() = default;
    bool operator==(const Vertex& other) const{ return id == other.id; }

    // print function to display vertex information
    friend std::ostream& operator<<(std::ostream& os, const Vertex& v) {
        os << v.id;
        return os;
    }

    virtual void print(){
        std::cout << " Vertex: " << id << ", Name: " << name.data() <<  std::endl;
    }
};

namespace std {
    template <>
    struct hash<Vertex> {
        size_t operator()(const Vertex& v) const {
            size_t h1 = hash<uint64_t>{}(v.id);
            return h1;
        }
    };
}

#endif // VERTEX_HPP