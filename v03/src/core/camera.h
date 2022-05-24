#ifndef CAMERA_H
#define CAMERA_H

#include "film.h"
#include "ray.h"

class CameraFrame {
    public:
        Point3f e;
        Vector3f u;
        Vector3f v;
        Vector3f w;

        CameraFrame(Point3f e, Vector3f u, Vector3f v, Vector3f w);
	virtual ~CameraFrame() = default;
};

class LookAt {
    public:
        Point3f look_from;
        Vector3f look_at;
        Vector3f up;

        LookAt(Point3f look_from, Vector3f look_at, Vector3f up);
	virtual ~LookAt() = default;
};

class Camera {
    protected:
        float l, r, b, t;
        LookAt* look_at_info;

    public:
        CameraFrame* frame; // may be protected
        Film film;
	
        Camera(float l, float r, float b, float t, LookAt* look_at_info);
	virtual ~Camera() = default;
        Point2f map_to_screen_space(Point2i& point); // may be protected
        void calculate_frame();
        int nx();
        int ny();
        virtual Ray generate_ray(int x, int y) = 0;
};

class PerspectiveCamera : public Camera {
    public:
        float focal_distance = -1.0;
        float aspect_ratio = -1.0;
        float fovy = -1.0;

        PerspectiveCamera(float l, float r, float b, float t, LookAt* look_at_info);
        PerspectiveCamera(float focal_distance, float aspect_ratio, float fovy, LookAt* look_at_info);
        void set_lrbt_from_xres_yres_if_needed();
        Ray generate_ray(int x, int y);
};

class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float l, float r, float b, float t, LookAt* look_at_info);
        Ray generate_ray(int x, int y);
};

#endif
