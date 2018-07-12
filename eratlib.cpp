#include <cmath>
#include "eratlib.h"

unsigned long int load_from_file(std::vector<unsigned long>& primes, std::ifstream& file) {
    unsigned long read;
    while (file >> read) {
        primes.push_back(read);
    }
    return read;
}

void Chunk::set_multiple(unsigned long n) {

    int range_min = std::ceil((double)this->chunk_offset / n);
    int range_max = std::floor((double)(this->chunk_offset + this->chunk_size - 1) / n);

    for(int i = range_min; i <= range_max; i++) {
        this->chunk_table->set((n * i) - this->chunk_offset);
    }
        
}

std::vector<unsigned long> Chunk::process(const std::vector<unsigned long>& primes) {
    
    this->chunk_table->reset();
    
    for(auto i : primes) {
        this->set_multiple(i);
    }
    
    std::vector<unsigned long> new_primes;
    
    for(int i = 0; i < this->chunk_size; i++) {
        if(!this->chunk_table->test(i)) {
            unsigned long new_prime = i + this->chunk_offset;
            new_primes.push_back(new_prime);
            this->set_multiple(new_prime);
        }
    }
    
    return new_primes;
    
}
