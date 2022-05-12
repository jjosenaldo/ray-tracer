#include <cmath>
#include "camera.h"

#define PI 3.14159265

LookAt::LookAt(Point3f look_from, Vector3f look_at, Vector3f up): look_from(look_from), look_at(look_at), up(up) { }

Camera::Camera(float l, float r, float b, float t, LookAt* look_at_info): l(l), r(r), b(b), t(t), look_at_info(look_at_info) { }

int Camera::nx() {
    return film.width;
}

int Camera::ny() {
    return film.height;
}

Point2f Camera::map_to_screen_space(Point2f& point) {
    float u = l + (r - l)*(point[0] + 0.5)/nx();
    float v = b + (t - b)*(point[1] + 0.5)/ny();

    return {u, v};
}

OrthographicCamera::OrthographicCamera(float l, float r, float b, float t, LookAt* look_at_info): Camera(l, r, b, t, look_at_info) { }

PerspectiveCamera::PerspectiveCamera(float l, float r, float b, float t, LookAt* look_at_info): Camera(l, r, b, t, look_at_info) { }

PerspectiveCamera::PerspectiveCamera(float focal_distance, float aspect_ratio, float fovy, LookAt* look_at_info): Camera(-1.0, -1.0, -1.0, -1.0, look_at_info) {
    this->focal_distance = focal_distance;
    this->aspect_ratio = aspect_ratio;
    this->fovy = fovy;
 }

 void PerspectiveCamera::set_lrbt_from_xres_yres_if_needed() {
     if (fovy < 0.0) return;
     auto actual_aspect_ratio = aspect_ratio > 0 ? aspect_ratio : static_cast<float>(nx()) / ny();
     auto half_fovy_tan = tan((fovy/2)*PI/180);
     auto half_height_screen_space = half_fovy_tan * focal_distance;

     l = -actual_aspect_ratio*half_height_screen_space;
     r = actual_aspect_ratio*half_height_screen_space;
     b = -half_height_screen_space;
     t = half_height_screen_space;
 }

Ray OrthographicCamera::generate_ray(int x, int y) {
    // TODO
    return Ray{{-1.0, -1.0, -1.0},{-1.0, -1.0, -1.0}};
}

Ray PerspectiveCamera::generate_ray(int x, int y) {
    // TODO
    return Ray{{-1.0, -1.0, -1.0},{-1.0, -1.0, -1.0}};
}
