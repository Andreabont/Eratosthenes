#ifndef ERATLIB_H
#define ERATLIB_H

#include <vector>
#include <fstream>
#include <boost/dynamic_bitset.hpp>

unsigned long int load_from_file(std::vector<unsigned long int>& primes, std::ifstream& file);

class Chunk {
    
private:
    
    Chunk(const Chunk&) = delete;
    Chunk& operator=(Chunk const&) = delete;
    
    boost::dynamic_bitset<>* chunk_table;
    unsigned long int chunk_offset;
    int chunk_size;
    
    void set_multiple(unsigned long int n);
    
public:
    
    Chunk(int size, unsigned long int offset) {
        this->chunk_offset = offset;
        this->chunk_size = size;
        this->chunk_table = new boost::dynamic_bitset<>(size, 0ul);
    }
    
    ~Chunk() {
        delete this->chunk_table;
    }
    
    void forward() {
        this->chunk_offset += this->chunk_size;
    }
    
    std::vector<unsigned long int> process(const std::vector<unsigned long int>& primes);
    
};

#endif //ERATLIB_H
