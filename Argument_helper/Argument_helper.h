/*
*
* Argument Helper
*
* Daniel Russel drussel@alumni.princeton.edu
* Stanford University
*
*
* This software is not subject to copyright protection and is in the
* public domain. Neither Stanford nor the author assume any
* responsibility whatsoever for its use by other parties, and makes no
* guarantees, expressed or implied, about its quality, reliability, or
* any other characteristic.
*
*/

#ifndef _DSR_ARGS_H_
#define _DSR_ARGS_H_
#include <vector>
#include <map>
#include <list>
#include <string>


namespace dsr{
  extern bool verbose, VERBOSE;


  class Argument_helper{
  private:
    class Argument_target;

 
    class FlagTarget;
    class DoubleTarget;
    class IntTarget;
    class UIntTarget;
    class StringTarget;
    class CharTarget;
    class StringVectorTarget;

  public:
    Argument_helper();
    void new_flag(char key, const char *long_name, const char *description,bool &dest);

    void new_string( const char *arg_description, const char *description, std::string &dest);
    void new_named_string(char key, const char *long_name,
                          const char *arg_description,
                          const char *description,  std::string &dest);
    void new_optional_string( const char *arg_description, const char *description, std::string &dest);

    void new_int( const char *arg_description, const char *description, int &dest);
    void new_named_int(char key, const char *long_name,const char *value_name,
                       const char *description,
                       int &dest);
    void new_optional_int(const char *value_name,
                          const char *description,
                          int &dest);

    void new_double(const char *value_name,
                    const char *description,
                    double &dest);

    void new_named_double(char key, const char *long_name,const char *value_name,
                          const char *description,
                          double &dest);
    void new_optional_double(const char *value_name,
                             const char *description,
                             double &dest);

    void new_char(const char *value_name,
                                const char *description,
                                char &dest);
    void new_named_char(char key, const char *long_name,const char *value_name,
                           const char *description,
                           char &dest);
    void new_optional_char(const char *value_name,
                           const char *description,
                           char &dest);

    void new_unsigned_int(const char *value_name, const char *description,
                          unsigned int &dest);
    void new_optional_unsigned_int(const char *value_name, const char *description,
                                unsigned int &dest);
    void new_named_unsigned_int(char key, const char *long_name,
                                   const char *value_name, const char *description,
                                   unsigned int &dest);



    void new_named_string_vector(char key, const char *long_name,
                                 const char *value_name, const char *description,
                                 std::vector<std::string> &dest);


    void set_string_vector(const char *arg_description, const char *description, std::vector<std::string> &dest);

    void set_author(const char *author);

    void set_description(const char *descr);

    void set_version(float v);
    void set_version(const char *str);

    void set_name(const char *name);

    void set_build_date(const char *date);


    void process(int argc, const char **argv);
    void process(int argc, char **argv){
      process(argc, const_cast<const char **>(argv));
    }
    void write_usage(std::ostream &out) const;
    void write_values(std::ostream &out) const;
    
    ~Argument_helper();
  protected:
    typedef std::map<char, Argument_target*> SMap;
    typedef std::map<std::string, Argument_target*> LMap;
    typedef std::vector<Argument_target*> UVect;
    // A map from short names to arguments.
    SMap short_names_;
    // A map from long names to arguments.
    LMap long_names_;
    std::string author_;
    std::string name_;
    std::string description_;
    std::string date_;
    float version_;
    bool seen_end_named_;
    // List of unnamed arguments
    std::vector<Argument_target*> unnamed_arguments_;
    std::vector<Argument_target*> optional_unnamed_arguments_;
    std::vector<Argument_target*> all_arguments_;
    std::string extra_arguments_descr_;
    std::string extra_arguments_arg_descr_;
    std::vector<std::string> *extra_arguments_;
    std::vector<Argument_target*>::iterator current_unnamed_;
    std::vector<Argument_target*>::iterator current_optional_unnamed_;
    void new_argument_target(Argument_target*);
    void handle_error() const;
  private:
    Argument_helper(const Argument_helper &){};
    const Argument_helper& operator=(const Argument_helper &){return *this;}
  };
  
}

#define ARGUMENT_HELPER_BASICS(ah) ah.set_author("Daniel Russel, drussel@stanford.edu");\
ah.set_version(VERSION);\
ah.set_build_date(__DATE__);

#endif