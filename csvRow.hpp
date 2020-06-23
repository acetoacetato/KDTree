
#include <iostream>
#include <fstream>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
namespace csv{


    
    class CSVRow
    {
        public:
            float const& operator[](std::size_t index) const
            {
                return m_data[index];
            }
            std::vector<float>* generaVector()
            {
                std::vector<float>* vec = new std::vector<float>();
                for(auto numero : m_data){
                    vec->push_back(numero);
                }
                return vec;
            }
            std::size_t size() const
            {
                return m_data.size();
            }
            void readNextRow(std::istream& str)
            {
                std::string         line;
                std::getline(str, line);

                std::stringstream   lineStream(line);
                std::string         cell;

                m_data.clear();
                while(std::getline(lineStream, cell, ','))
                {   
                    m_data.push_back(stof(cell));
                }
                // This checks for a trailing comma with no data after it.
                if (!lineStream && cell.empty())
                {
                    // If there was a trailing comma then add an empty element.
                    m_data.push_back(0.0);
                }
            }
        private:
            std::vector<float>    m_data;
    };

    std::istream& operator>>(std::istream& str, CSVRow& data)
    {
        data.readNextRow(str);
        return str;
    }   

    std::vector<std::vector<float>*>* cargaNumeros(std::string filename)
    {
        CSVRow row;
        std::ifstream file(filename);
        std::vector<std::vector<float>*>* vec = new std::vector<std::vector<float>*>();
        while(file >> row)
        {
            vec->push_back(row.generaVector());
        }

        return vec;
    }


}

