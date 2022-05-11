#ifndef CAMERA_H
#define CAMERA_H

#include "film.h"
#include "ray.h"

class Camera {
    protected:
        Point2f map_to_screen_space(Point2f& point);
        int l, r, b, t;
    public:
        Camera(int l, int r, int b, int t);
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
        PerspectiveCamera(int l, int r, int b, int t);
        PerspectiveCamera(float focal_distance, float aspect_ratio, float fovy);
        Ray generate_ray(int x, int y);
};

class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(int l, int r, int b, int t);
        Ray generate_ray(int x, int y);
};

#endif
