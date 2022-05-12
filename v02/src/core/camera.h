#ifndef CAMERA_H
#define CAMERA_H

#include "film.h"
#include "ray.h"

class Camera {
    protected:
        Point2f map_to_screen_space(Point2f& point);
    public:
        float l, r, b, t; // TODO: make it protected
        Camera(float l, float r, float b, float t);
        int nx();
        int ny();
        Film film;
        virtual Ray generate_ray(int x, int y) = 0;
};

class PerspectiveCamera : public Camera {
    public:
        float focal_distance = -1.0;
        float aspect_ratio = -1.0;
        float fovy = -1.0;
        PerspectiveCamera(float l, float r, float b, float t);
        PerspectiveCamera(float focal_distance, float aspect_ratio, float fovy);
        void set_lrbt_from_xres_yres_if_needed();
        Ray generate_ray(int x, int y);
};

class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float l, float r, float b, float t);
        Ray generate_ray(int x, int y);
};

#endif
