#pragma once

#include <array>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <windows.h>
#include <variant>

struct stHangeul;
struct stEnglish;

using varCharacter = std::variant<stHangeul, stEnglish>;

std::wstring convertUtf8ToWString(const std::string& str);
std::string convertWStringToUtf8(const std::wstring& wstr);

class cConvertConsonant
{
private:
    cConvertConsonant();
    cConvertConsonant(const cConvertConsonant& ref) = delete;
    cConvertConsonant(const cConvertConsonant&& ref) = delete;
    cConvertConsonant& operator=(const cConvertConsonant& ref) = delete;
    ~cConvertConsonant() {}

public:
    static cConvertConsonant& getInstance();
    std::array<wchar_t, 2> convertChoToDoubleConsonant(const wchar_t wc);
    std::array<wchar_t, 2> convertJongToCho(const wchar_t wc);
    wchar_t ConvertCompatChoToJamo(wchar_t wc);

private:
    std::unordered_map<wchar_t, std::array<wchar_t, 2>> m_mapCho;
    std::unordered_map<wchar_t, std::array<wchar_t, 2>> m_mapJong;
    std::unordered_map<wchar_t, wchar_t> m_mapJamo;
};

struct stCharacter
{
    virtual ~stCharacter() = default;
    virtual bool compare(const varCharacter & pIput) const = 0;
};

struct stEnglish : public stCharacter
{
public:
    stEnglish(wchar_t wc);
    virtual bool compare(const varCharacter &  varInput) const override;
    wchar_t m_wc = 0;
};

struct stHangeul : public stCharacter
{
public:
    stHangeul(wchar_t wc);
    virtual bool compare(const varCharacter & pInput) const override;

    std::array<wchar_t, 2> m_arrCho = {};
    wchar_t m_wcJung = 0;
    std::array<wchar_t, 2> m_arrJong = {};
};

class cCompare
{
public:
    cCompare() = default;
    std::vector<varCharacter> convertSentence(const std::wstring & ws);
    bool compareSentence(
        const std::vector<varCharacter> & vecSearch, 
        const std::vector<varCharacter> & vecSentence
    );
};

int main();
