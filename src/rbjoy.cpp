#include "rbjoy.h"

#include <Windows.h>
#include <dinput.h>

#include <iostream>

BOOL DIEnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef) {
    auto* devices = (std::vector<rbjoy_device_desc>*)pvRef;
    devices->push_back({
        .product_name = lpddi->tszProductName,
        .instance_name = lpddi->tszInstanceName,
        .guid = lpddi->guidInstance
    });
    return DIENUM_CONTINUE;
}

std::vector<rbjoy_device_desc> rbjoy_enumerate_joysticks() {
    std::vector<rbjoy_device_desc> devices;

    IDirectInput8* di;
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&di, NULL);
    di->EnumDevices(DI8DEVCLASS_GAMECTRL, &DIEnumDevicesCallback, &devices, DIEDFL_ATTACHEDONLY);
    di->Release();
    return devices;
}

rbjoy_device rbjoy_create_device(const rbjoy_device_desc& desc) {
    rbjoy_device device;
    IDirectInput8* di;
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&di, NULL);
    HRESULT hr = di->CreateDevice(desc.guid, (LPDIRECTINPUTDEVICE8A*)&device.device, NULL);
    if (FAILED(hr)) {
        std::cout << "Error creating device for joystick " << desc.instance_name << std::endl;
        return device;
    } else {
        device.device->SetCooperativeLevel(GetConsoleWindow(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
        device.device->SetDataFormat(&c_dfDIJoystick);
        hr = device.device->Acquire();
        if (FAILED(hr)) {
            std::cout << "Could not acquire " << desc.instance_name << std::endl;
        }
    }
    return device;
}

void rbjoy_get_state(rbjoy_device& device, DIJOYSTATE& state) {
    device.device->GetDeviceState(sizeof(DIJOYSTATE), &state);
}
