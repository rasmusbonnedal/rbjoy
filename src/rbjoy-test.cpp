#include <iostream>
#include <stdio.h>

#include "rbjoy.h"

int main(char, char**) {

    auto devices = rbjoy_enumerate_joysticks();

    for (auto& device_desc : devices) {
        std::cout << device_desc.product_name << std::endl;
        rbjoy_device device = rbjoy_create_device(device_desc);
        while (true) {
            DIJOYSTATE state;
            rbjoy_get_state(device, state);
            printf("%05d %05d %05d %05d\n", state.lRx, state.lX, state.lY, state.lZ);

        }
    }

    return 0;
}
