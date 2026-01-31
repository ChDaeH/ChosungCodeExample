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

//type-safe union 글자 공용체 타입 재지정
using varCharacter = std::variant<stHangeul, stEnglish>;

////////////////////////////////////////////////////////////////////////////////
//UTF8 <--> WINDDOWS 유니코드 문자열 변환

std::wstring convertUtf8ToWString(const std::string& str);
std::string convertWStringToUtf8(const std::wstring& wstr);

////////////////////////////////////////////////////////////////////////////////
//Singleton - 완성형 한글의 초성/종성 자음을 단일 자음(자모)으로 분해하는 변환기
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

    //쌍자음을 2개의 단일 자음으로 변환한다
    std::array<wchar_t, 2> convertChoToDoubleConsonant(const wchar_t wc);
    //종성 글자를 단일 자음으로 변환한다
    std::array<wchar_t, 2> convertJongToCho(const wchar_t wc);
    //입력 단일 자음을 단일 자음으로 변환한다
    wchar_t convertCompatChoToJamo(wchar_t wc);

private:
    // 쌍자음(ㄲ→ㄱㄱ), 종성(ㅄ→ㄹㅅ)을 단일 자음 배열로 반환
    std::unordered_map<wchar_t, std::array<wchar_t, 2>> m_mapCho;
    // 종성 자모를 초성 자모로 변환 (ㅄ→ㄹㅅ, ㄳ→ㄱㅅ 등)
    std::unordered_map<wchar_t, std::array<wchar_t, 2>> m_mapJong;
    //입력 자음 정보
    std::unordered_map<wchar_t, wchar_t> m_mapJamo;
};

////////////////////////////////////////////////////////////////////////////////
//글자 타입 정의
struct stCharacter
{
    virtual ~stCharacter() = default;
    
    //동일한지 비교한다
    virtual bool isCompare(const varCharacter & varInput) const = 0;
};

////////////////////////////////////////////////////////////////////////////////
//영어(+숫자) 타입
struct stEnglish : public stCharacter
{
public:
    stEnglish(wchar_t wc);
    virtual bool isCompare(const varCharacter &  varInput) const override;
    wchar_t m_wc = 0;
};

////////////////////////////////////////////////////////////////////////////////
//한글 타입
struct stHangeul : public stCharacter
{
public:
    stHangeul(wchar_t wc);
    virtual bool isCompare(const varCharacter & varInput) const override;

    std::array<wchar_t, 2> m_arrCho = {};   //초성
    wchar_t m_wcJung = 0;                   //중성
    std::array<wchar_t, 2> m_arrJong = {};  //종성
};

////////////////////////////////////////////////////////////////////////////////
//문장 비교 클래스
class cCompare
{
public:
    cCompare() = default;

    //WINDOWS 유니코드 문자열을 varCharacter로 변환한다
    std::vector<varCharacter> convertSentence(const std::wstring & ws);

    //두 varCharacter 문장을 비교한다 
    bool isCompareSentence(
        const std::vector<varCharacter> & vecSearch, 
        const std::vector<varCharacter> & vecSentence
    );
};

int main();