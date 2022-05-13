#include <cmath>
#include "camera.h"

#define PI 3.14159265

LookAt::LookAt(Point3f look_from, Vector3f look_at, Vector3f up): look_from(look_from), look_at(look_at), up(up) { }

CameraFrame::CameraFrame(Point3f e, Vector3f u, Vector3f v, Vector3f w): e(e), u(u), v(v), w(w) { }

Camera::Camera(float l, float r, float b, float t, LookAt* look_at_info): l(l), r(r), b(b), t(t), look_at_info(look_at_info) { }

int Camera::nx() {
    return film.width;
}

int Camera::ny() {
    return film.height;
}

void Camera::calculate_frame() {
    auto gaze = look_at_info->look_at - look_at_info->look_from; 
    auto w = normalize_vector3f(gaze);
    auto cross_up_w = cross_vector3f(look_at_info->up, w);
    auto u = normalize_vector3f(cross_up_w);
    auto cross_w_u = cross_vector3f(u, w);
    auto v = normalize_vector3f(cross_w_u);
    frame = new CameraFrame(look_at_info->look_from, u, v, w);
}

Point2f Camera::map_to_screen_space(Point2i& point) {
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
    Point2i input_point = {x, y};
    auto uv = map_to_screen_space(input_point);
    auto u = uv[0];
    auto v = uv[1];
    auto origin = frame->e + u * frame->u + v * frame->v;
    auto direction = frame->w;

    return Ray{origin, direction};
}

Ray PerspectiveCamera::generate_ray(int x, int y) {
    Point2i input_point = {x, y};
    auto uv = map_to_screen_space(input_point);
    auto u = uv[0];
    auto v = uv[1];
    auto origin = frame->e;
    auto direction = focal_distance * frame->w + u * frame->u + v * frame->v;

    return Ray{origin, direction};
}
