#ifndef API_H
#define API_H

#include <string>
#include "parser.h"
#include "../utils/image.h"
#include "vec3.h"
#include "paramset.h"
#include "camera.h"
#include "background.h"
#include "object_manager.h"
#include "rt3.h"

class API {
    private:
       static Camera* m_camera;
       static Background m_background;
       static LookAt* lookat_info;
       static ObjectManager obj_manager;

       static void render( void );

    public:
        static RunningOptions run_opt;

        static void init_engine( const RunningOptions& );
        static void run( void );
        static void clean_up( void );
		static void reset_engine( void );

        static void camera( const ParamSet& ps );
        static void film( const ParamSet& ps );
        static void background( const ParamSet& ps );
        static void integrator( const ParamSet& ps );
        static void look_at( const ParamSet& ps );
        static void material( const ParamSet& ps );
        static void object( const ParamSet& ps );

        static void world_begin( void );
        static void world_end( void );
};
#endif // API_H
