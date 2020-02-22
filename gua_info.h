#pragma once

#include <string>

namespace predict {

struct GuaInfo {
    std::string name;
    std::string desc;
    int page;
};

std::string GuaInfoToString(const GuaInfo& info);
const GuaInfo& GetGuaInfo(unsigned char six_yao);

}  // namespace predict
