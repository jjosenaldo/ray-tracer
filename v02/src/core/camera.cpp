#include "camera.h"

Camera::Camera(int l, int r, int b, int t): l(l), r(r), b(b), t(t) { }

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

OrthographicCamera::OrthographicCamera(int l, int r, int b, int t): Camera(l, r, b, t) { }

PerspectiveCamera::PerspectiveCamera(int l, int r, int b, int t): Camera(l, r, b, t) { }

PerspectiveCamera::PerspectiveCamera(float focal_distance, float aspect_ratio, float fovy) {
    this->focal_distance = focal_distance;
    this->aspect_ratio = aspect_ratio;
    this->fovy = fovy;
 }

Ray OrthographicCamera::generate_ray(int x, int y) {
    // TODO
    return Ray{{-1.0, -1.0, -1.0},{-1.0, -1.0, -1.0}};
}

Ray PerspectiveCamera::generate_ray(int x, int y) {
    // TODO
    return Ray{{-1.0, -1.0, -1.0},{-1.0, -1.0, -1.0}};
}
