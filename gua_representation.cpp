#include "gua_representation.h"

namespace predict {

GuaRepresentation::GuaRepresentation() : six_yao_(0), changed_yao_(0) {}

GuaRepresentation GuaRepresentation::GetChangedGua() const {
    GuaRepresentation gua;
    gua.six_yao_ = (this->six_yao_ ^ this->changed_yao_) & 0x3F;
    gua.changed_yao_ = this->changed_yao_;
    return gua;
}

void GuaRepresentation::SetYao(int position, bool is_yang, bool changed) {
    if (is_yang) {
        six_yao_ |= (1 << position);
    }
    if (changed) {
        changed_yao_ |= (1 << position);
    }
}

std::string GuaRepresentation::DebugString() const {
    // TODO(ahy)
    return "";
}

std::vector<int> GuaRepresentation::GetChangedYaoVector() const {
    std::vector<int> changed_yaos;
    for (int i = 0; i < 6; i++) {
        if (((six_yao_ >> i) & 1) == 1) {
            changed_yaos.push_back(i);
        }
    }
    return changed_yaos;
}

}  // namespace predict
