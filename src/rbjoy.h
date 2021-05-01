#pragma once

#include <dinput.h>

#include <string>
#include <vector>

struct rbjoy_device_desc {
    std::string product_name;
    std::string instance_name;
    GUID guid;
};

struct rbjoy_device {
    IDirectInputDevice8* device;
};

std::vector<rbjoy_device_desc> rbjoy_enumerate_joysticks();

rbjoy_device rbjoy_create_device(const rbjoy_device_desc& desc);

void rbjoy_get_state(rbjoy_device& device, DIJOYSTATE& state);
