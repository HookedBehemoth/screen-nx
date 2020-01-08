#pragma once
#include "util/host.hpp"
#include "util/theme.hpp"
#include <json.hpp>
#include <vector>
#include <string>

class Settings {
public:
    Settings();
    ~Settings();
    void SetHoster(std::string name);
    void SetTheme(std::string name);
private:
};
