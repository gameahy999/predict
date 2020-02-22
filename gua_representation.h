#pragma once

#include <string>
#include <vector>

namespace predict {

class GuaRepresentation {
public:
    GuaRepresentation();
    GuaRepresentation(const GuaRepresentation& gua) = default;

    GuaRepresentation GetChangedGua() const;
    void SetYao(int position, bool is_yang, bool changed);
    unsigned char GetSixYao() const {return six_yao_;}
    std::string DebugString() const;
    // from 0 to 5
    std::vector<int> GetChangedYaoVector() const;

private:
    unsigned char six_yao_;
    unsigned char changed_yao_;
};

}  // namespace predict
