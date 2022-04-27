#ifndef API_H
#define API_H

#include <string>
#include "parse.h"
#include "image.h"

class API {
    private:
        /*
        Instancia de Background
        Instancia de Film
        Instancia de Camera
        */
       int x=10; // só pq n lembro se dá pau ter nada dentro do private

    public:

        static RunningOptions run_opt;

        static void init_engine( const RunningOptions& );
        static void run( void );
        static void clean_up( void );

        static void camera( const ParamSet& ps );
        static void film( const ParamSet& ps );
        static void background( const ParamSet& ps );
        static void integrator( const ParamSet& ps );
        static void look_at( const ParamSet& ps );

        static void world_begin( void );
        static void world_end( void );
}
#endif // API_H