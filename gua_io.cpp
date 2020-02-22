#include "gua_io.h"

#include <iostream>
#include <sstream>

#include "gua_info.h"
#include "gua_representation.h"

namespace predict {

#define HINT_MESSAGE "Please input the condition(2正1反->1; 2反1正->2; 3正->3; 3反->4)"
#define ERROR_INPUT_MESSAGE "Invalid input, try again!"

const static std::vector<std::string> kChangedYaoMessage = {
    "六爻不变: 卦中六个爻都不是变爻, 这叫'静卦', 用本卦的卦辞解卦",
    "一个爻变: 卦中有一个变爻, 就用这个变爻的爻辞解卦",
    "两个爻变: 卦中有两个变爻, 用这两个变爻的爻辞解卦, 以上爻为主",
    "三个爻变: 卦中有三个变爻, 用本卦卦辞和变卦卦辞做综合考虑",
    "四个爻变: 卦中有四个变爻, 用另外两个静爻的爻辞解卦, 并以下爻爻辞为主",
    "五个爻变: 卦中有五个变爻, 用变卦的静爻爻辞解卦",
    "六个爻变: 如果是乾坤两卦就用用九、用六的爻辞解卦, 其他卦则用变卦的卦辞解卦"
};

const static std::vector<std::string> kYaoName = {
    "初爻", "二爻", "三爻", "四爻", "五爻", "上爻"
};

static GuaRepresentation GetGuaRepresentation() {
    GuaRepresentation gua;
    for (int i = 0; i < 6; i++) {
        std::cout << HINT_MESSAGE << std::endl;
        bool input_success = false;
        while (!input_success) {
            int condition = 0;
            std::cin >> condition;

            switch (condition) {
            case 1:
                gua.SetYao(i, true, false);
                input_success = true;
                break;
            case 2:
                gua.SetYao(i, false, false);
                input_success = true;
                break;
            case 3:
                gua.SetYao(i, false, true);
                input_success = true;
                break;
            case 4:
                gua.SetYao(i, true, true);
                input_success = true;
                break;
            default:
                std::cerr << ERROR_INPUT_MESSAGE << std::endl;
                input_success = false;
                break;
            }
        }
    }
    return gua;
}

static std::string ChangedYaoInfoToString(const GuaRepresentation& gua) {
    std::stringstream ss;

    // example: "变爻有 -> 初爻 上爻"
    std::vector<int> changed_yaos = gua.GetChangedYaoVector();
    if (!changed_yaos.empty()) {
        ss << "变爻有 -> ";
        for (int i : changed_yaos) {
            ss << kYaoName[i] << " ";
        }
        ss << "\n";
    }

    // example: 六爻不变 ...
    ss << kChangedYaoMessage[changed_yaos.size()];

    return ss.str();
}

static void OutputGuaInfo(const GuaRepresentation& gua) {
    std::cout << "主卦:" << std::endl;
    const GuaInfo& main = GetGuaInfo(gua.GetSixYao());
    std::cout << GuaInfoToString(main) << std::endl;

    std::cout << std::endl;

    std::cout << "变卦:" << std::endl;
    GuaRepresentation changed_gua = gua.GetChangedGua();
    const GuaInfo& change = GetGuaInfo(changed_gua.GetSixYao());
    std::cout << GuaInfoToString(change) << std::endl;

    std::cout << std::endl;

    std::cout << "关注:" << std::endl;
    std::cout << ChangedYaoInfoToString(gua) << std::endl;
}

void CalculateGua() {
    GuaRepresentation gua = GetGuaRepresentation();
    OutputGuaInfo(gua);
}

}  // namespace predict
