#include "Chosung.h"

std::wstring convertUtf8ToWString(const std::string& str)
{
    if (str.empty())
        return L"";

    const int iSize = MultiByteToWideChar(
        CP_UTF8,
        0,
        str.c_str(),
        (int)str.size(),
        nullptr,
        0
    );

    std::wstring wstr(iSize, 0);

    MultiByteToWideChar(
        CP_UTF8,
        0,
        str.c_str(),
        (int)str.size(),
        &wstr[0],
        iSize
    );

    return wstr;
}

std::string convertWStringToUtf8(const std::wstring& wstr)
{
    if (wstr.empty())
        return "";

    const int iSize = WideCharToMultiByte(
        CP_UTF8,
        0,
        wstr.c_str(),
        (int)wstr.size(),
        nullptr,
        0,
        nullptr,
        nullptr
    );

    std::string str(iSize, 0);

    WideCharToMultiByte(
        CP_UTF8,
        0,
        wstr.c_str(),
        (int)wstr.size(),
        &str[0],
        iSize,
        nullptr,
        nullptr
    );

    return str;
}

cConvertConsonant::cConvertConsonant()
{
#pragma region FUNC_SET_CHAR
    auto funcSetChar = [](
        std::unordered_map<wchar_t, std::array<wchar_t, 2>>& umap,
        const wchar_t& wcKey, 
        const wchar_t& wcVal1, 
        const wchar_t& wcVal2
        )
    {
            umap[wcKey] = std::array<wchar_t, 2>{ wcVal1, wcVal2 };
    };
#pragma endregion

    {
        funcSetChar(m_mapCho, 0x1101, 0x1100, 0x1100);      //ㄲ
        funcSetChar(m_mapCho, 0x1104, 0x1103, 0x1103);      //ㄸ
        funcSetChar(m_mapCho, 0x1108, 0x1107, 0x1107);      //ㅃ
        funcSetChar(m_mapCho, 0x110A, 0x1109, 0x1109);      //ㅆ
        funcSetChar(m_mapCho, 0x110D, 0x110C, 0x110C);      //ㅉ
    }

    {
        funcSetChar(m_mapJong, 0x11A8, 0x1100, 0);           // ㄱ
        funcSetChar(m_mapJong, 0x11A9, 0x1100, 0x1100);      // ㄲ
        funcSetChar(m_mapJong, 0x11AA, 0x1100, 0x1109);      // ㄳ
        funcSetChar(m_mapJong, 0x11AB, 0x1102, 0);           // ㄴ
        funcSetChar(m_mapJong, 0x11AC, 0x1102, 0x110C);      // ㄵ
        funcSetChar(m_mapJong, 0x11AD, 0x1102, 0x1112);      // ㄶ
        funcSetChar(m_mapJong, 0x11AE, 0x1103, 0);           // ㄷ
        funcSetChar(m_mapJong, 0x11AF, 0x1105, 0);           // ㄹ
        funcSetChar(m_mapJong, 0x11B0, 0x1105, 0x1100);      // ㄺ
        funcSetChar(m_mapJong, 0x11B1, 0x1105, 0x1106);      // ㄻ
        funcSetChar(m_mapJong, 0x11B2, 0x1105, 0x1107);      // ㄼ
        funcSetChar(m_mapJong, 0x11B3, 0x1105, 0x1109);      // ㄽ
        funcSetChar(m_mapJong, 0x11B4, 0x1105, 0x1110);      // ㄾ
        funcSetChar(m_mapJong, 0x11B5, 0x1105, 0x1111);      // ㄿ
        funcSetChar(m_mapJong, 0x11B6, 0x1105, 0x1112);      // ㅀ
        funcSetChar(m_mapJong, 0x11B7, 0x1106, 0);           // ㅁ
        funcSetChar(m_mapJong, 0x11B8, 0x1107, 0);           // ㅂ
        funcSetChar(m_mapJong, 0x11B9, 0x1107, 0x1109);      // ㅄ
        funcSetChar(m_mapJong, 0x11BA, 0x1109, 0);           // ㅅ
        funcSetChar(m_mapJong, 0x11BB, 0x1109, 0x1109);      // ㅆ
        funcSetChar(m_mapJong, 0x11BC, 0x110B, 0);           // ㅇ
        funcSetChar(m_mapJong, 0x11BD, 0x110C, 0);           // ㅈ
        funcSetChar(m_mapJong, 0x11BE, 0x110E, 0);           // ㅊ
        funcSetChar(m_mapJong, 0x11BF, 0x110F, 0);           // ㅋ
        funcSetChar(m_mapJong, 0x11C0, 0x1110, 0);           // ㅌ
        funcSetChar(m_mapJong, 0x11C1, 0x1111, 0);           // ㅍ
        funcSetChar(m_mapJong, 0x11C2, 0x1112, 0);           // ㅎ
    }

    {
        m_mapJamo = 
        {
            { L'ㄱ', 0x1100 }, { L'ㄲ', 0x1101 }, { L'ㄴ', 0x1102 }, { L'ㄷ', 0x1103 },
            { L'ㄸ', 0x1104 }, { L'ㄹ', 0x1105 }, { L'ㅁ', 0x1106 }, { L'ㅂ', 0x1107 },
            { L'ㅃ', 0x1108 }, { L'ㅅ', 0x1109 }, { L'ㅆ', 0x110A }, { L'ㅇ', 0x110B },
            { L'ㅈ', 0x110C }, { L'ㅉ', 0x110D }, { L'ㅊ', 0x110E }, { L'ㅋ', 0x110F },
            { L'ㅌ', 0x1110 }, { L'ㅍ', 0x1111 }, { L'ㅎ', 0x1112 },
        };
    }
}

cConvertConsonant& cConvertConsonant::getInstance()
{
    static cConvertConsonant s;
    return s;
}

std::array<wchar_t, 2> cConvertConsonant::convertChoToDoubleConsonant(const wchar_t wc)
{
    std::array<wchar_t, 2> arr = {0, 0};

    auto it = std::as_const(m_mapCho).find(wc);

    if (it != m_mapCho.cend())
    {
        arr[0] = it->second[0];
        arr[1] = it->second[1];
    }
    else
    {
        arr[0] = wc;
    }

    return arr;
}

std::array<wchar_t, 2> cConvertConsonant::convertJongToCho(const wchar_t wc)
{
    std::array<wchar_t, 2> arr = {0, 0};

    auto it = std::as_const(m_mapJong).find(wc);

    if (it != m_mapJong.cend())
    {
        arr[0] = it->second[0];
        arr[1] = it->second[1];
    }
    else
    {
        arr[0] = wc;
    }

    return arr;
}

wchar_t cConvertConsonant::ConvertCompatChoToJamo(wchar_t wc)
{
    auto it = std::as_const(m_mapJamo).find(wc);

    if (it != m_mapJamo.cend())
        return it->second;
    
    return wc;
}

std::vector<varCharacter> cCompare::convertSentence(const std::wstring & ws)
{
    std::vector<varCharacter> vecConvert;
    vecConvert.reserve(ws.size());

    for (size_t i = 0; i < ws.size(); ++i)
    {
        if(
        (ws[i] >= 0xAC00 && ws[i] <= 0xD7A3)            // 한글 음절
            || (ws[i] >= 0x3130 && ws[i] <= 0x318F)     // 호환 자모 (ㄱ,ㄴ,ㄷ)
            || (ws[i] >= 0x1100 && ws[i] <= 0x11FF)     // 자모 (ᄀᄂᄃ)
        )
        {
            vecConvert.emplace_back(std::in_place_type<stHangeul>, ws[i]);
        }
        else
        {
            vecConvert.emplace_back(std::in_place_type<stEnglish>, ws[i]);
        }
    }

    return vecConvert;
}

bool cCompare::compareSentence(
    const std::vector<varCharacter>& vecSearch, 
    const std::vector<varCharacter>& vecWord
)
{
    if (vecWord.size() < vecSearch.size())
        return false;

    int iCorrect = 0;

    for (auto& stWord : vecWord)
    {
        if (vecSearch[iCorrect].index() != stWord.index())
        {
            iCorrect = 0;
            continue;
        }

        bool bIsCompare = false;

        if (std::holds_alternative<stHangeul>(vecSearch[iCorrect]))
        {
            bIsCompare = std::get<stHangeul>(vecSearch[iCorrect]).compare(stWord);
        }
        else
        {
            bIsCompare = std::get<stEnglish>(vecSearch[iCorrect]).compare(stWord);
        }

        if (bIsCompare)
        {
            iCorrect++;

            if (iCorrect >= vecSearch.size())
                break;
        }
        else
        {
            iCorrect = 0;
        }
    }

    if (iCorrect < vecSearch.size())
        return false;

    return true;
}

stEnglish::stEnglish(wchar_t wc) : stCharacter()
{
    m_wc = wc;
}

bool stEnglish::compare(const varCharacter &  varInput) const
{
    if (!std::holds_alternative<stEnglish>(varInput))
        return false;

    const stEnglish & stEnglishInput = std::get<stEnglish>(varInput);
 
    return (stEnglishInput.m_wc == m_wc);
}

stHangeul::stHangeul(wchar_t wc) : stCharacter()
{
    if (wc >= 0xAC00
        && wc <= 0xD7A3)
    {
        const wchar_t wcHangeul = wc - 0xAC00;

        const wchar_t wcCho = 0x1100 + (wcHangeul / 588);
        const wchar_t wcJung = 0x1161 + (wcHangeul % 588) / 28;
        const wchar_t wcJong = (wcHangeul % 28 == 0) ? 0 : 0x11A7 + (wcHangeul % 28);
        
        m_arrCho = cConvertConsonant::getInstance().convertChoToDoubleConsonant(wcCho);
        m_wcJung = wcJung;
        m_arrJong = cConvertConsonant::getInstance().convertJongToCho(wcJong);
    }
    else if (wc >= 0x3131 
        && wc <= 0x314E
        )
    {
        const wchar_t wcCho = cConvertConsonant::getInstance().ConvertCompatChoToJamo(wc);
        m_arrCho = cConvertConsonant::getInstance().convertChoToDoubleConsonant(wcCho);
    }
    else if (wc>= 0x314F 
        && wc <= 0x3163
        )
    {
        m_wcJung = 0x1161 + (wc - 0x314F);
    }
}

bool stHangeul::compare(const varCharacter& varInput) const
{
    if (!std::holds_alternative<stHangeul>(varInput))
        return false;

    const stHangeul & stHangeulInput = std::get<stHangeul>(varInput);
    
    {
        for (size_t i = 0; i < m_arrCho.size(); ++i)
        {
            if (m_arrCho[i] == 0)
                continue;

            if (stHangeulInput.m_arrCho[i] == 0)
                return false;

            if (stHangeulInput.m_arrCho[i] != m_arrCho[i])
                return false;
        }
    }

    {
        if (m_wcJung != 0)
        {
            if (stHangeulInput.m_wcJung != m_wcJung)
                return false;
        }
    }

    {
        for (size_t i = 0; i < m_arrJong.size(); ++i)
        {
            if (m_arrJong[i] == 0)
                continue;

            if (stHangeulInput.m_arrJong[i] == 0)
                return false;

            if (stHangeulInput.m_arrJong[i] != m_arrJong[i])
                return false;
        }
    }

    return true;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cCompare _cCompare;

    std::string strSearch;

    std::cin >> strSearch;

    std::wstring wstrSearch = convertUtf8ToWString(strSearch);

    std::vector<std::wstring> words =
    {
        L"Lv1Sword검",
        L"Lv2Shield방패",
        L"Lv3Potion회복",
        L"Lv4Ring반지",
        L"Lv5Helmet투구",

        L"Fire01불꽃구",
        L"Ice02얼음창",
        L"Wind03바람베기",
        L"Earth04대지강타",
        L"Dark05어둠파동",

        L"Stage1숲길",
        L"Stage2사막길",
        L"Stage3빙하길",
        L"Stage4화산길",
        L"Stage5심연길",

        L"Boss01드래곤",
        L"Boss02리치",
        L"Boss03하이드라",
        L"Boss04데몬킹",
        L"Boss05타이탄",

        L"Quest01시작",
        L"Quest02성장",
        L"Quest03시련",
        L"Quest04정복",
        L"Quest05완료",

        L"Item1001강철검",
        L"Item1002은빛창",
        L"Item1003마력봉",
        L"Item1004치유서",
        L"Item1005보호석",

        L"SkillA1화염탄",
        L"SkillB2냉기탄",
        L"SkillC3번개탄",
        L"SkillD4독안개",
        L"SkillE5신성빛",

        L"Map01초원지대",
        L"Map02사막지대",
        L"Map03설산지대",
        L"Map04화산지대",
        L"Map05심해지대",

        L"NPC01상인",
        L"NPC02대장장이",
        L"NPC03마법사",
        L"NPC04치유사",
        L"NPC05경비병",

        L"User01초보자",
        L"User02숙련자",
        L"User03전문가",
        L"User04고수",
        L"User05전설",

        L"Pet01늑대",
        L"Pet02호랑이",
        L"Pet03용",
        L"Pet04불사조",
        L"Pet05정령",

        L"Title01모험가",
        L"Title02개척자",
        L"Title03정복자",
        L"Title04영웅",
        L"Title05전설자",

        L"Buff01공격력증가",
        L"Buff02방어력증가",
        L"Buff03이속증가",
        L"Buff04치명증가",
        L"Buff05회복증가",

        L"Mode01스토리",
        L"Mode02도전",
        L"Mode03무한",
    };

    std::vector<varCharacter> vecSearch = _cCompare.convertSentence(wstrSearch);

    for (auto & word : words)
    {
        std::vector<varCharacter> vecWord = _cCompare.convertSentence(word);

        if (_cCompare.compareSentence(vecSearch, vecWord))
        {
            std::string strWord = convertWStringToUtf8(word);
            std::cout << strWord << std::endl;
        }
    }
}