#include <iostream>
#include <boost/program_options.hpp>
#include "eratlib.h"

const int CHUNK_SIZE = 100000;
const int CHUNK_NUMBER = 1;

int main(int argc, char *argv[]) {
    
    boost::program_options::options_description po ("Sieve of Eratosthenes");

    po.add_options()
        ("help,h", "Help")
        ("chunk-size,s", boost::program_options::value<int>()->default_value(CHUNK_SIZE), "Chunk size")
        ("chunk-number,n", boost::program_options::value<int>()->default_value(CHUNK_NUMBER), "Number of chunk processed in one run")
        ("load,l", boost::program_options::value<std::string>(), "Load file")
    ;

    boost::program_options::variables_map vm;
    
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, po), vm);
        boost::program_options::notify(vm);
    } catch (boost::program_options::unknown_option ex1) {
        std::cerr << ">> " << ex1.what() << "" << std::endl;
        std::cerr << ">> Try '" << argv[0] << " --help' for more information." << std::endl;
        return EXIT_FAILURE;
    } catch (boost::program_options::invalid_command_line_syntax ex2) {
        std::cerr << ">> " << ex2.what() << "" << std::endl;
        std::cerr << ">> Try '" << argv[0] << " --help' for more information." << std::endl;
        return EXIT_FAILURE;
    }

    if (vm.count("help")) {
        std::cout << po << std::endl;
        return 0;
    }
    
    std::vector<unsigned long int> primes;
    unsigned long int chunk_offset = 2;
    
    if(vm.count("load")) {
        std::ifstream myfile;
        myfile.open(vm["load"].as<std::string>());
        chunk_offset = load_from_file(primes, myfile);
        myfile.close();
    }
    
    Chunk mychunk(vm["chunk-size"].as<int>(), chunk_offset);
    
    for(int counter = 0; counter < vm["chunk-number"].as<int>(); counter++) {
        
        auto new_primes = mychunk.process(primes);
        
        primes.insert(std::end(primes), std::begin(new_primes), std::end(new_primes));
        
        mychunk.forward();
        
    }
    
    for(auto i : primes) {
        std::cout << i << "\n";
    }
    
    return EXIT_SUCCESS;
    
}
